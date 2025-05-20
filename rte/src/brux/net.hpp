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
|NETWORK HEADER|
\*============*/

#ifndef BRUX_NET_HPP
#define BRUX_NET_HPP

#include <SDL2/SDL_net.h>
#include <string>
#include <queue>

// Socket connection handle
typedef struct NetSocket {
	TCPsocket socket;
	bool connected;
	std::queue<std::string> messageQueue;
	static const size_t MAX_QUEUE_SIZE = 100;
} NetSocket;

// Basic socket functions
bool xyInitSocket(NetSocket* sock);
void xyCloseSocket(NetSocket* sock);
bool xyConnectSocket(NetSocket* sock, const char* host, int port);
bool xyDisconnectSocket(NetSocket* sock);
bool xySendSocketMessage(NetSocket* sock, const char* message);
bool xyReceiveSocketMessages(NetSocket* sock);
bool xyHasSocketMessage(NetSocket* sock);
const char* xyGetNextSocketMessage(NetSocket* sock);
void xyClearSocketMessages(NetSocket* sock);

#endif // BRUX_NET_HPP