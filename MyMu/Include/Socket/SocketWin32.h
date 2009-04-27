/*
 * OpenMuServe
 *
 * Copyright (C) 2006 Michal Kinasiewicz alians MiKiOnE
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */  
#ifndef SOCKETWIN32_H_
#define SOCKETWIN32_H_
#if defined(__WIN__)
#include "Socket/Socket.h"
#include "Protocol/SBPacket.h"

#include <winsock2.h>
#include <iostream>
class SocketWin32:public Socket
{
private:


SOCKET sock;
public:
	SocketWin32(SOCKET s);
	virtual ~SocketWin32();
  void Recv(HexBuff &h);
  void Send(HexBuff &h);
  void Send(SBPacket *h)
  {
  HexBuff *he=h->build();
  std::cout << "<PACKAGE>";
  h->printDesc();
  Send(*he);
  };


};
#endif //defined _WIN_
#endif /*SOCKETWIN32_H_*/
