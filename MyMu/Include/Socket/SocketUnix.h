#ifndef SOCKETUNIX_H_
#define SOCKETUNIX_H_
#if   defined(__WIN__) || defined (__MINGW32__)
//nothing
#elif defined (__LINUX__)
#include "Socket.h"
#include <sys/socket.h>
#include "Protocol/SBPacket.h"

class SocketUnix :public Socket
{
 private:
  int sock;
 public:
  SocketUnix(int s);
  virtual ~SocketUnix();
  void Send(HexBuff &h);
  void Send(SBPacket *h)
  {
  h->printDesc();
  HexBuff *he=h->build();
  Send(*he);
  
  };
  void Recv(HexBuff &h);
  
};


#endif //af unix
#endif /*SOCKETUNIX_H_*/
