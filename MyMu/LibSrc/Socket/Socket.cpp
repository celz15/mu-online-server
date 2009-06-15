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
#include "../../Include/Socket/Socket.h"

Socket::Socket()
{
	Error = false;
	_multiSend = NULL;
}

Socket::~Socket()
{
}

Socket & operator <<(Socket &s, HexBuff &h)
{
	s.Send(h);
	return s;
}
Socket & operator >>(Socket &s, HexBuff &h)
{
	s.Recv(h);
	return s;
}
bool Socket::EnyError()
{
	return Error;
}
void Socket::SetError()
{
	Error = true;
}
