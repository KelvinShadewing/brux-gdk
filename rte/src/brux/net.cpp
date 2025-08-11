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

#define CURL_STATICLIB
#include <curl/curl.h>

#include <git2.h>

/////////////////
// WEB SOCKETS //
/////////////////

std::vector<NetSocket *> vcSockets;

bool xyInitSocket(int wsid, std::string socketMode)
{
	// Guarding clauses
	if (wsid < 0 || vcSockets.size() <= wsid)
		return false;
	NetSocket *sock = vcSockets[wsid];
	if (!sock)
		return false;

	sock->tcp = nullptr;
	sock->udp = nullptr;
	sock->connected = false;
	while (!sock->messageQueue.empty())
	{
		sock->messageQueue.pop();
	}

	sock->t = socketMode;
	return true;
}

int xyNewSocket(std::string socketMode = "")
{
	std::transform(socketMode.begin(), socketMode.end(), socketMode.begin(),
				   [](unsigned char c)
				   { return std::tolower(c); });
	if (socketMode != "tcp" && socketMode != "udp")
	{
		xyPrint("Invalid socket mode: %s", socketMode.c_str());
		return -1;
	}

	NetSocket *nsock = new NetSocket;

	nsock->set = SDLNet_AllocSocketSet(1);
	if (!nsock->set)
	{
		fprintf(stderr, "SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		delete nsock;
		return -1;
	}

	// Fill blank list
	if (vcSockets.size() == 0)
	{
		vcSockets.push_back(nsock);
		nsock->id = 0;
		xyInitSocket(nsock->id, socketMode);
		return 0;
	}

	// Search for empty slot
	for (int i = 0; i < vcSockets.size(); i++)
	{
		if (vcSockets[i] == 0)
		{
			vcSockets[i] = nsock;
			nsock->id = i;
			xyInitSocket(nsock->id, socketMode);
			return i;
		}
	}

	vcSockets.push_back(nsock);
	nsock->id = vcSockets.size() - 1;
	xyInitSocket(nsock->id, socketMode);
	return vcSockets.size() - 1;
}

void xyCloseSocket(int wsid)
{
	// Guarding clauses
	if (vcSockets.size() <= wsid)
		return;
	NetSocket *sock = vcSockets[wsid];
	if (!sock)
		return;

	if (sock->tcp)
	{
		SDLNet_TCP_Close(sock->tcp);
		sock->tcp = nullptr;
	}

	if (sock->udp)
	{
		SDLNet_UDP_Close(sock->udp);
		sock->udp = nullptr;
	}

	sock->connected = false;
	while (!sock->messageQueue.empty())
	{
		sock->messageQueue.pop();
	}
}

void xyDeleteSocket(int wsid)
{
	// Guarding clauses
	if (vcSockets.size() <= wsid)
		return;
	NetSocket *sock = vcSockets[wsid];
	if (!sock)
		return;

	xyCloseSocket(wsid);
	if (sock->set)
	{
		SDLNet_FreeSocketSet(sock->set);
	}
	delete vcSockets[wsid];
	vcSockets[wsid] = 0;
}

void xyFlushSockets()
{
	if (vcSockets.size() == 0)
		return;

	for (int i = 0; i < vcSockets.size(); i++)
	{
		xyDeleteSocket(i);
	}

	vcSockets.clear();
	vcSockets.shrink_to_fit();
}

bool xyConnectSocket(int wsid, const std::string &host, int port)
{
	// Guarding clauses
	if (vcSockets.size() <= wsid)
		return false;
	NetSocket *sock = vcSockets[wsid];
	if (!sock)
		return false;

	sock->host = host;
	sock->port = port;

	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, host.c_str(), port) == -1)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		return false;
	}

	if (sock->t == "tcp")
	{
		sock->tcp = SDLNet_TCP_Open(&ip);
		if (!sock->tcp)
		{
			fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
			return false;
		}

		// Set socket to non-blocking mode
		if (SDLNet_TCP_AddSocket(sock->set, sock->tcp) == -1)
		{
			fprintf(stderr, "SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
			SDLNet_TCP_Close(sock->tcp);
			sock->tcp = nullptr;
			return false;
		}
	}

	if (sock->t == "udp")
	{
		sock->udp = SDLNet_UDP_Open(port);
		if (!sock->udp)
		{
			fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
			return false;
		}

		if (SDLNet_UDP_AddSocket(sock->set, sock->udp) == -1)
		{
			fprintf(stderr, "SDLNet_UDP_AddSocket: %s\n", SDLNet_GetError());
			SDLNet_UDP_Close(sock->udp);
			sock->udp = nullptr;
			return false;
		}

		sock->ip = ip; // Store the resolved IP address
	}

	sock->connected = true;
	return true;
}

bool xySendSocket(int wsid, const std::string &message)
{
	// Guarding clauses
	if (vcSockets.size() <= wsid)
		return false;
	NetSocket *sock = vcSockets[wsid];
	if (!sock || !sock->connected || !sock->tcp)
		return false;

	int len = message.length();
	int sent = 0;

	if (sock->t == "tcp")
	{
		sent = SDLNet_TCP_Send(sock->tcp, message.c_str(), len);
	}

	if (sock->t == "udp")
	{
		// Prepare the UDP packet
		UDPpacket *packet = SDLNet_AllocPacket(len);
		if (!packet)
		{
			fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
			return false;
		}

		packet->address = sock->ip; // Use the stored IP address
		packet->len = len;
		std::memcpy(packet->data, message.c_str(), len);

		sent = SDLNet_UDP_Send(sock->udp, -1, packet);
		SDLNet_FreePacket(packet); // Free the packet after sending

		if (sent == 0)
		{
			fprintf(stderr, "SDLNet_UDP_Send: %s\n", SDLNet_GetError());
			return false;
		}

		return true;
	}

	if (sent < len)
	{
		fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		return false;
	}

	return true;
}

bool xyReceiveSocket(int wsid)
{
	// Guarding clauses
	if (vcSockets.size() <= wsid)
		return false;
	NetSocket *sock = vcSockets[wsid];
	if (!sock || !sock->connected || !sock->tcp)
		return false;
	char buffer[1024];
	int received = 0;

	if (sock->t == "tcp")
	{
		// Check if there's data ready to be read
		int numReady = SDLNet_CheckSockets(sock->set, 0); // 0 timeout = don't wait
		if (numReady <= 0)
		{
			return true; // No data available, not an error
		}

		// Only try to receive if this socket is ready
		if (!SDLNet_SocketReady(sock->tcp))
		{
			return true; // This socket isn't ready, not an error
		}

		received = SDLNet_TCP_Recv(sock->tcp, buffer, sizeof(buffer) - 1);

		if (received <= 0)
		{
			if (received < 0)
			{
				fprintf(stderr, "SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
			}
			return false;
		}
	}

	if (sock->t == "udp")
	{
		// Prepare to receive a UDP packet
		UDPpacket *packet = SDLNet_AllocPacket(1024);
		if (!packet)
		{
			fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
			return false;
		}

		received = SDLNet_UDP_Recv(sock->udp, packet);
		if (received == 0)
		{
			SDLNet_FreePacket(packet);
			return true; // No data available, not an error
		}
		else if (received < 0)
		{
			fprintf(stderr, "SDLNet_UDP_Recv: %s\n", SDLNet_GetError());
			SDLNet_FreePacket(packet);
			return false;
		}

		std::memcpy(buffer, packet->data, packet->len);
		buffer[packet->len] = '\0'; // Null-terminate the string
		SDLNet_FreePacket(packet);
	}

	buffer[received] = '\0';

	// Check for non-empty, non-whitespace message
	std::string msg(buffer);
	// Trim from start (in place)
	msg.erase(msg.begin(), std::find_if(msg.begin(), msg.end(), [](unsigned char ch)
										{ return !std::isspace(ch); }));
	// Trim from end (in place)
	msg.erase(std::find_if(msg.rbegin(), msg.rend(), [](unsigned char ch)
						   { return !std::isspace(ch); })
				  .base(),
			  msg.end());

	// Store message in queue, removing oldest if full
	if (!msg.empty())
	{
		if (sock->messageQueue.size() >= NetSocket::MAX_QUEUE_SIZE)
		{
			sock->messageQueue.pop();
		}
		sock->messageQueue.push(buffer);

		return true;
	};

	return false;
}

bool xyQueuedSocket(int wsid)
{
	// Guarding clauses
	if (vcSockets.size() <= wsid)
		return false;
	NetSocket *sock = vcSockets[wsid];
	if (!sock)
		return false;

	return sock && !sock->messageQueue.empty();
}

std::string xyGetSocket(int wsid)
{
	// Guarding clauses
	if (vcSockets.size() <= wsid)
		return "";
	NetSocket *sock = vcSockets[wsid];
	if (!sock)
		return "";

	if (!xyQueuedSocket(wsid))
		return "";
	std::string message = sock->messageQueue.front();
	sock->messageQueue.pop();
	return message;
}

void xyClearSocket(int wsid)
{
	// Guarding clauses
	if (vcSockets.size() <= wsid)
		return;
	NetSocket *sock = vcSockets[wsid];
	if (!sock)
		return;
	while (!sock->messageQueue.empty())
	{
		sock->messageQueue.pop();
	}
}

/////////
// GIT //
/////////

//////////
// CURL //
//////////

CURL *curlHandle = nullptr;

bool xyInitCurl()
{
	curlHandle = curl_easy_init();
	if (!curlHandle)
	{
		fprintf(stderr, "Failed to initialize cURL\n");
		return false;
	}
	return true;
}

void xyCleanupCurl()
{
	if (curlHandle)
	{
		curl_easy_cleanup(curlHandle);
		curlHandle = nullptr;
	}
}

void xyCurlOpt(int opt, int value) {
	if (!curlHandle)
	{
		fprintf(stderr, "cURL handle is not initialized\n");
		return;
	}

	curl_easy_setopt(curlHandle, (CURLoption)opt, value);
}

void xyCurlOpt(int opt, const std::string &value) {
	if (!curlHandle)
	{
		fprintf(stderr, "cURL handle is not initialized\n");
		return;
	}

	curl_easy_setopt(curlHandle, (CURLoption)opt, value.c_str());
}

void xyCurlReset() {
	if (!curlHandle)
	{
		fprintf(stderr, "cURL handle is not initialized\n");
		return;
	}

	curl_easy_reset(curlHandle);
}

void xyRegisterNetworkAPI(ssq::VM &vm)
{
	vm.addFunc("newNetSocket", xyNewSocket);   // Doc'd
	vm.addFunc("netClose", xyCloseSocket);	   // Doc'd
	vm.addFunc("netOpen", xyConnectSocket);	   // Doc'd
	vm.addFunc("netDelete", xyDeleteSocket);   // Doc'd
	vm.addFunc("netSend", xySendSocket);	   // Doc'd
	vm.addFunc("netReceive", xyReceiveSocket); // Doc'd
	vm.addFunc("netQueued", xyQueuedSocket);   // Doc'd
	vm.addFunc("netGet", xyGetSocket);		   // Doc'd
	vm.addFunc("netClear", xyClearSocket);	   // Doc'd
	vm.addFunc("netFlush", xyFlushSockets);	   // Doc'd
};