//  Brux - Network
//  Copyright (C) 2016 KelvinShadewing
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

/*============*\
|NETWORK SOURCE|
\*============*/

#include "brux/net.hpp"
#include "brux/global.hpp"

#include <cstring>
#include <cstdio>
#include <queue>

std::vector<NetSocket*> vcSockets;

bool xyInitTCP(int wsid) {
	//Guarding clauses
	if(wsid < 0 || vcSockets.size() <= wsid)
		return false;
	NetSocket* sock = vcSockets[wsid];
	if (!sock) 
		return false;
	
	sock->socket = nullptr;
	sock->connected = false;
	while (!sock->messageQueue.empty()) {
		sock->messageQueue.pop();
	}
	return true;
}

int xyNewTCP() {
	NetSocket* nsock = new NetSocket;
	nsock->set = SDLNet_AllocSocketSet(1);
	if (!nsock->set) {
		fprintf(stderr, "SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		delete nsock;
		return -1;
	}

	//Fill blank list
	if(vcSockets.size() == 0) {
		vcSockets.push_back(nsock);
		nsock->id = 0;
		return 0;
	}

	//Search for empty slot
	for(int i = 0; i < vcSockets.size(); i++) {
		if(vcSockets[i] == 0) {
			vcSockets[i] = nsock;
			nsock->id = i;
			return i;
		}
	}

	vcSockets.push_back(nsock);
	nsock->id = vcSockets.size() - 1;
	return vcSockets.size() - 1;
}

void xyCloseTCP(int wsid) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return;
	NetSocket* sock = vcSockets[wsid];
	if (!sock)
		return;
	
	if (sock->connected) {
		xyDisconnectTCP(wsid);
	}
	while (!sock->messageQueue.empty()) {
		sock->messageQueue.pop();
	}
}

void xyDeleteTCP(int wsid) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return;
	NetSocket* sock = vcSockets[wsid];
	if (!sock)
		return;

	xyCloseTCP(wsid);
	if (sock->set) {
		SDLNet_FreeSocketSet(sock->set);
	}
	delete vcSockets[wsid];
	vcSockets[wsid] = 0;
}

void xyFlushSockets() {
	if(vcSockets.size() == 0)
		return;

	for(int i = 0; i < vcSockets.size(); i++) {
		xyDeleteTCP(i);
	}

	vcSockets.clear();
	vcSockets.shrink_to_fit();
}

// Internal implementation using std::string
bool xyConnectTCPImpl(int wsid, const std::string& host, int port) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return false;
	NetSocket* sock = vcSockets[wsid];
	if (!sock)
		return false;
	
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, host.c_str(), port) == -1) {
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		return false;
	}

	sock->socket = SDLNet_TCP_Open(&ip);
	if (!sock->socket) {
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		return false;
	}

	//Set socket to non-blocking mode
	if (SDLNet_TCP_AddSocket(sock->set, sock->socket) == -1) {
		fprintf(stderr, "SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
		SDLNet_TCP_Close(sock->socket);
		sock->socket = nullptr;
		return false;
	}

	sock->connected = true;
	return true;
}

//Public interface for Squirrel bindings
bool xyConnectTCP(int wsid, const char* host, int port) {
	return xyConnectTCPImpl(wsid, host ? std::string(host) : std::string(), port);
}

bool xyDisconnectTCP(int wsid) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return false;
	NetSocket* sock = vcSockets[wsid];
	if (!sock || !sock->connected)
		return false;
	
	if (sock->socket) {
		SDLNet_TCP_Close(sock->socket);
		sock->socket = nullptr;
	}
	
	sock->connected = false;
	while (!sock->messageQueue.empty()) {
		sock->messageQueue.pop();
	}
	return true;
}

// Internal implementation using std::string
bool xySendTCPImpl(int wsid, const std::string& message) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return false;
	NetSocket* sock = vcSockets[wsid];
	if (!sock || !sock->connected || !sock->socket) return false;

	int len = message.length();
	int sent = SDLNet_TCP_Send(sock->socket, message.c_str(), len);
	
	if (sent < len) {
		fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		return false;
	}
	
	return true;
}

// Public interface for Squirrel bindings
bool xySendTCP(int wsid, const char* message) {
	if (!message) return false;
	return xySendTCPImpl(wsid, std::string(message));
}

bool xyReceiveTCP(int wsid) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return false;
	NetSocket* sock = vcSockets[wsid];
	if (!sock || !sock->connected || !sock->socket) return false;

	//Check if there's data ready to be read
	int numReady = SDLNet_CheckSockets(sock->set, 0);  // 0 timeout = don't wait
	if (numReady <= 0) {
		return true; //No data available, not an error
	}

	//Only try to receive if this socket is ready
	if (!SDLNet_SocketReady(sock->socket)) {
		return true; //This socket isn't ready, not an error
	}

	char buffer[1024];
	int received = SDLNet_TCP_Recv(sock->socket, buffer, sizeof(buffer) - 1);
	
	if (received <= 0) {
		if (received < 0) {
			fprintf(stderr, "SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
		}
		return false;
	}
	
	buffer[received] = '\0';

	// Check for non-empty, non-whitespace message
	std::string msg(buffer);
	// Trim from start (in place)
	msg.erase(msg.begin(), std::find_if(msg.begin(), msg.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
	// Trim from end (in place)
	msg.erase(std::find_if(msg.rbegin(), msg.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base(), msg.end());
	
	// Store message in queue, removing oldest if full
	if(!msg.empty()) {
		if (sock->messageQueue.size() >= NetSocket::MAX_QUEUE_SIZE) {
			sock->messageQueue.pop();
		}
		sock->messageQueue.push(buffer);
		
		return true;
	};

	return false;
}

bool xyQueuedTCP(int wsid) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return false;
	NetSocket* sock = vcSockets[wsid];
	if (!sock)
		return false;

	return sock && !sock->messageQueue.empty();
}

std::string xyGetTCPImpl(int wsid) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return "";
	NetSocket* sock = vcSockets[wsid];
	if (!sock)
		return "";

	if (!xyQueuedTCP(wsid)) return "";
	std::string message = sock->messageQueue.front();
	sock->messageQueue.pop();
	return message;
}

void xyClearTCP(int wsid) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return;
	NetSocket* sock = vcSockets[wsid];
	if (!sock) return;
	while (!sock->messageQueue.empty()) {
		sock->messageQueue.pop();
	}
}

void xyRegisterNetworkAPI(ssq::VM& vm) {
	//TCP functions
	vm.addFunc("tcpNewSocket", xyNewTCP);
	vm.addFunc("tcpInit", xyInitTCP);
	vm.addFunc("tcpClose", xyCloseTCP);
	vm.addFunc("tcpConnect", [](int wsid, const std::string& host, int port) {
		return xyConnectTCPImpl(wsid, host, port);
	});
	vm.addFunc("tcpSend", [](int wsid, const std::string& message) {
		return xySendTCPImpl(wsid, message);
	});
	vm.addFunc("tcpReceive", xyReceiveTCP);
	vm.addFunc("tcpQueued", xyQueuedTCP);
	vm.addFunc("tcpGet", [](int wsid) {
		return xyGetTCPImpl(wsid);
	});
	vm.addFunc("tcpClear", xyClearTCP);

	//UDP functions

	//Misc functions
	vm.addFunc("netFlush", xyFlushSockets);
};