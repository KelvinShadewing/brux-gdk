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

bool xyInitSocket(NetSocket* sock) {
	if (!sock) return false;
	
	sock->socket = nullptr;
	sock->connected = false;
	while (!sock->messageQueue.empty()) {
		sock->messageQueue.pop();
	}
	return true;
}

void xyCloseSocket(NetSocket* sock) {
	if (!sock) return;
	
	if (sock->connected) {
		xyDisconnectSocket(sock);
	}
	while (!sock->messageQueue.empty()) {
		sock->messageQueue.pop();
	}
}

bool xyConnectSocket(NetSocket* sock, const char* host, int port) {
	if (!sock || !host) return false;
	
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, host, port) == -1) {
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

bool xyDisconnectSocket(NetSocket* sock) {
	if (!sock || !sock->connected) return false;
	
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

bool xySendSocketMessage(NetSocket* sock, const char* message) {
	if (!sock || !sock->connected || !sock->socket || !message) return false;

	int len = strlen(message);
	int sent = SDLNet_TCP_Send(sock->socket, message, len);
	
	if (sent < len) {
		fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		return false;
	}
	
	return true;
}

bool xyReceiveSocketMessages(NetSocket* sock) {
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

bool xyHasSocketMessage(NetSocket* sock) {
	return sock && !sock->messageQueue.empty();
}

const char* xyGetNextSocketMessage(NetSocket* sock) {
	if (!xyHasSocketMessage(sock)) return nullptr;
	
	static std::string message;  // Static to ensure the string persists after return
	message = sock->messageQueue.front();
	sock->messageQueue.pop();
	return message.c_str();
}

void xyClearSocketMessages(NetSocket* sock) {
	if (!sock) return;
	while (!sock->messageQueue.empty()) {
		sock->messageQueue.pop();
	}
}

void xyRegisterNetworkAPI(ssq::VM& vm) {

};