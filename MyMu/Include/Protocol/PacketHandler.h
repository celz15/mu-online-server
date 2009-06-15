#ifndef PACKETHANDLER_H_
#define PACKETHANDLER_H_
#include "SHello.h"
#include "CBPacket.h"
#include <iostream>

class MuClientTheard;
class PacketHandler
{
 MuClientTheard *_client; // wskaznik do Clienta
 public:
  PacketHandler( MuClientTheard* t);
  virtual ~PacketHandler();

  void handlePacket(HexBuff *p);

};

#endif /*PACKETHANDLER_H_*/
