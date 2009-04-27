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
#ifndef SOCKET_H_
#define SOCKET_H_
#include "HexBuffer/HexBuffer.h"
#include "Protocol/SBPacket.h"
class Socket
{
 protected:
  HexBuff * _multiSend;	//paczka multi senda
  bool Error;
 public:
  Socket();
  virtual ~Socket();
  void multiAdd(SBPacket *p)
    {
      std::cout << "MSAdd: " ;
      p->printDesc();
      //std::cout << "         ";
		
      if(_multiSend==NULL)
	{
	  std::cout << "inicjuje nowy buffor\n";
	  _multiSend=new HexBuff();   //jesli nie zainicjowany
	}
      HexBuff * pac=p->build();
      std::cout << pac->buff2str("")<<"\n";
      //std::cout << _multiSend->Size() <<"s\n";
      (*_multiSend)[_multiSend->Size()].writeHB((*pac),-1); //dodajemy na koncu buffora
      std::cout << _multiSend->buff2str("")<<"\n" ;
      std::cout << "OK.. \n";
    };
  
  void multiSend() 
    {
      Send(*_multiSend);
      delete _multiSend;
      _multiSend=NULL;
    }
  
  virtual void Send(HexBuff &h){};
  virtual void Send(SBPacket *p){};
  virtual void Recv(HexBuff &h){};
  friend Socket & operator<<(Socket &s , HexBuff &h);
  friend Socket & operator>>(Socket &s , HexBuff &h);
  bool EnyError();
  void SetError();
};

#endif /*SOCKET_H_*/

//c3 33 f3 03 aa 7f 00 00 f4 01 00 00 e8 03 00 00 05 00 0a 00 0a 00 0a 00 0a 00 0d f0 0a 00 0a 00 f5 f8 0a 00 1e 00 0f 0f 0a 00 00 00 03 02 00 00 0f 00 0f ff 00
//c3 f0 ad ba 0d f0 ad ba 0d f0 ad ba 0d f0 ad ba 0d f0 ad ba 0d f0 ad ba 0d f0 ad ba 0d f0 ad ba 0d f0 ad ba 0d f0 ad ba 0d f0 ad ba 0d f0 ad ba 0d f0 ad ba 0d
