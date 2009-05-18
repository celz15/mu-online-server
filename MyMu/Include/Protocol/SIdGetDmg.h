#ifndef SIDGETDMG_H_
#define SIDGETDMG_H_

#include "Protocol/SBPacket.h"
#include "Protocol/BaseStruct.h"

struct IdGetDmg
{
  PMSG_HEADA _head;
  unsigned char m_uIndexHi;
  unsigned char m_uIndexLo;
  unsigned char m_uDmgHi;
  unsigned char m_uDmgLo;
  unsigned char m_uDmgFlag;
	
  void set(unsigned short id , unsigned short dmg, unsigned char flag)
  {
    _head.set(0xc1,sizeof(IdGetDmg),0xd9);
    m_uIndexHi=HIBYTE(id);
    m_uIndexLo=LOBYTE(id);
    m_uDmgHi=HIBYTE(dmg);
    m_uDmgLo=LOBYTE(dmg);
    m_uDmgFlag=flag;
  };
};
	

class SIdGetDmg : public CSPacket
{
  unsigned short id;
  unsigned short dmg; // le dostal
  unsigned char flag; // flaga
	
public:
  SIdGetDmg(unsigned short _id,unsigned short _dmg,unsigned char f):CSPacket(),id(_id),dmg(_dmg),flag(f)
  {
    MyName="D9 Id Got DMG";
  };
  ~SIdGetDmg(){}
  HexBuff * build(){
    IdGetDmg pack;
    pack.set(id,dmg,flag);
    unsigned char * tdata=reinterpret_cast<unsigned char*>(&pack);
    (*h)[0].writeAC(tdata,pack._head.m_uLen);
    return h;
  }
};

#endif /*SIDGETDMG_H_*/
