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

namespace ssq {
	class VM;
}

// Socket connection handle
typedef struct NetSocket {
	int id;
	TCPsocket socket;
	bool connected;
	std::queue<std::string> messageQueue;
	SDLNet_SocketSet set;
	static const size_t MAX_QUEUE_SIZE = 100;
} NetSocket;

extern std::vector<NetSocket*> vcSockets;

// Basic socket functions
bool xyInitTCP(int wsid);
void xyCloseTCP(int wsid);
bool xyConnectTCP(int wsid, const std::string& host, int port);
bool xyDisconnectTCP(int wsid);
void xyDeleteTCP(int wsid);
int xyNewTCP();
bool xySendTCP(int wsid, const std::string& message);
bool xyReceiveTCP(int wsid);
bool xyQueuedTCP(int wsid);
const char* xyGetTCP(int wsid);
void xyClearTCP(int wsid);
void xyRegisterNetworkAPI(ssq::VM& vm);

#endif // BRUX_NET_HPP