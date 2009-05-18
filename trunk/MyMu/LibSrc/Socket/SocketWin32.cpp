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

#if defined(__WIN__) || defined (__MINGW32__)
#include "Socket/SocketWin32.h"
#include <iostream>

#include "Encryption/encryption.h"

//#include "HexUtils/hexutils.h"

using std::cout;

SocketWin32::SocketWin32(SOCKET s)
{

sock =s;
Error=false;
}

SocketWin32::~SocketWin32()
{


}
void SocketWin32::Recv(HexBuff &h)
{
   int ret;
   char t[1024];
  
   ret= recv(sock,t,1024,0);
   if (ret<=0){Error=true;return;} // jesli blad to go ustawiamy
   h[0].writeAC(t,ret);
switch (h[0].readC()){
       case 0xc1:
       case 0xc3:h.DecryptMe(3);break;
       case 0xc2:
       case 0xc4:h.DecryptMe(4);break;
	 
};
 //  cout << "ret:" << ret <<"\n";
cout<< "(Cx.K->S):" <<h.buff2str("") << "\n";  
};


void SocketWin32::Send(HexBuff &h)
{
//cout << "przed wyslaniem\n";
//cout<< "(Cx.S->K):" <<h.buff2str("") << "\n";
//switch (h[0].readC()){
//      case 0xc1:
//       case 0xc3:break;//h.CryptMe(3);break;
//       case 0xc2:
//       case 0xc4:break;//h.CryptMe(4);break;

//};
h.AddEnd00();       
send(sock, (const char *)h.getAsSChar() , h.Size(), 0); 
//cout << "po wyslaniu\n";        
         
};                   
#endif
