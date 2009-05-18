#ifndef SIDDIE_H_
#define SIDDIE_H_

#include "Protocol/SBPacket.h"
#include "Protocol/BaseStruct.h"

struct IdDie{
  PMSG_HEADA _head;
  unsigned char indexHi;
  unsigned char indexLo;
  void set(unsigned short id)
  {
    unsigned char size = sizeof (IdDie);
    _head.set(0xc1,size,0x17); // 0xc1,size,0x19
    indexHi=(HIBYTE(id))^0x80;
    indexLo=LOBYTE(id);
  }; 
};

class SIdDie : public CSPacket
{
	unsigned short id;
public:
	SIdDie(unsigned short _id):CSPacket(),id(_id)
	{
	  MyName = "0x17 ID GONE DIED ";
	};
	~SIdDie(){};
	HexBuff* build()
	{
	  IdDie pack;
	  pack.set(id);
	  unsigned char * buff = reinterpret_cast<unsigned char *> (&pack);
	  (*h)[0].writeAC(buff,pack._head.m_uLen);
	  return h;
	}  
};

#endif /*SIDDIE_H_*/
