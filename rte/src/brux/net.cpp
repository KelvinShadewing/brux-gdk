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

bool xyInitSocket(int wsid) {
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

int xyNewSocket() {
	NetSocket* nsock = new NetSocket;

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

void xyCloseSocket(int wsid) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return;
	NetSocket* sock = vcSockets[wsid];
	if (!sock)
		return;
	
	if (sock->connected) {
		xyDisconnectSocket(wsid);
	}
	while (!sock->messageQueue.empty()) {
		sock->messageQueue.pop();
	}
}

void xyDeleteSocket(int wsid) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return;
	NetSocket* sock = vcSockets[wsid];
	if (!sock)
		return;

	xyCloseSocket(wsid);
	delete vcSockets[wsid];
	vcSockets[wsid] = 0;
}

void xyFlushSockets() {
	if(vcSockets.size() == 0)
		return;

	for(int i = 0; i < vcSockets.size(); i++) {
		xyDeleteSocket(i);
	}

	vcSockets.clear();
	vcSockets.shrink_to_fit();
}

// Internal implementation using std::string
bool xyConnectSocketImpl(int wsid, const std::string& host, int port) {
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
	
	sock->connected = true;
	return true;
}

// Public interface for Squirrel bindings
bool xyConnectSocket(int wsid, const char* host, int port) {
	return xyConnectSocketImpl(wsid, host ? std::string(host) : std::string(), port);
}

bool xyDisconnectSocket(int wsid) {
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
bool xySendSocketMessageImpl(int wsid, const std::string& message) {
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
bool xySendSocketMessage(int wsid, const char* message) {
	if (!message) return false;
	return xySendSocketMessageImpl(wsid, std::string(message));
}

bool xyReceiveSocketMessages(int wsid) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return false;
	NetSocket* sock = vcSockets[wsid];
	if (!sock || !sock->connected || !sock->socket) return false;

	char buffer[1024];
	int received = SDLNet_TCP_Recv(sock->socket, buffer, sizeof(buffer) - 1);
	
	if (received <= 0) {
		if (received < 0) {
			fprintf(stderr, "SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
		}
		return false;
	}
	
	buffer[received] = '\0';
	
	// Store message in queue, removing oldest if full
	if (sock->messageQueue.size() >= NetSocket::MAX_QUEUE_SIZE) {
		sock->messageQueue.pop();
	}
	sock->messageQueue.push(buffer);
	
	return true;
}

bool xyHasSocketMessage(int wsid) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return false;
	NetSocket* sock = vcSockets[wsid];
	if (!sock)
		return false;

	return sock && !sock->messageQueue.empty();
}

std::string xyGetNextSocketMessageImpl(int wsid) {
	//Guarding clauses
	if(vcSockets.size() <= wsid)
		return "";
	NetSocket* sock = vcSockets[wsid];
	if (!sock)
		return "";

	if (!xyHasSocketMessage(wsid)) return "";
	std::string message = sock->messageQueue.front();
	sock->messageQueue.pop();
	return message;
}

void xyClearSocketMessages(int wsid) {
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
	vm.addFunc("newSocket", xyNewSocket);
	vm.addFunc("initSocket", xyInitSocket);
	vm.addFunc("closeSocket", xyCloseSocket);
	vm.addFunc("connectSocket", [](int wsid, const std::string& host, int port) {
		return xyConnectSocketImpl(wsid, host, port);
	});
	vm.addFunc("sendSocketMessage", [](int wsid, const std::string& message) {
		return xySendSocketMessageImpl(wsid, message);
	});
	vm.addFunc("receiveSocketMessage", xyReceiveSocketMessages);
	vm.addFunc("socketHasMessage", xyHasSocketMessage);
	vm.addFunc("getSocketMessage", [](int wsid) {
		return xyGetNextSocketMessageImpl(wsid);
	});
	vm.addFunc("clearSocket", xyClearSocketMessages);
	vm.addFunc("flushSockets", xyFlushSockets);
};