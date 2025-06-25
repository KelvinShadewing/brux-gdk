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
	TCPsocket tcp;
	UDPsocket udp;
	std::string t;
	bool connected;
	std::queue<std::string> messageQueue;
	SDLNet_SocketSet set;
	static const size_t MAX_QUEUE_SIZE = 100;
	std::string host;
	int port;
	IPaddress ip;
} NetSocket;

extern std::vector<NetSocket*> vcSockets;

// Basic socket functions
bool xyInitSocket(int wsid, std::string socketMode);
void xyCloseSocket(int wsid);
bool xyConnectSocket(int wsid, const std::string& host, int port);
bool xyDisconnectSocket(int wsid);
void xyDeleteSocket(int wsid);
int xyNewSocket(std::string socketMode);
bool xySendSocket(int wsid, const std::string& message);
bool xyReceiveSocket(int wsid);
bool xyQueuedSocket(int wsid);
std::string xyGetSocket(int wsid);
void xyClearSocket(int wsid);
void xyFlushSockets();
void xyRegisterNetworkAPI(ssq::VM& vm);

#endif // BRUX_NET_HPP