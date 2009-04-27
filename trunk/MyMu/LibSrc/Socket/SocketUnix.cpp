#include "Socket/SocketUnix.h"

#include <iostream>

using std::cout;
#if defined (__WIN__)
#else

SocketUnix::SocketUnix(int s)
{ 
  sock=s;
}

SocketUnix::~SocketUnix()
{
}

void SocketUnix::Send(HexBuff &h)
{
cout << "przed wyslaniem\n";
cout<< "(Cx.S->K):" <<h.buff2str("") <<"\n";  
switch (h[0].readC()){
       case 0xc1:
       case 0xc3:break;//h.CryptMe(3);break;
       case 0xc2:
       case 0xc4:h.CryptMe(4);break;
};

  send(sock,h.getAsSChar(),h.Size(),0);	
};

void SocketUnix::Recv(HexBuff &h)
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
   //cout << "ret:" << ret <<"\n";
  
};
#endif

