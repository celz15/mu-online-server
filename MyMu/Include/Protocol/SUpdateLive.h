#ifndef SUPDATELIVE_H_
#define SUPDATELIVE_H_
#include "Protocol/SBPacket.h"
#include "BaseStruct.h"
//clasa : SUpdateLive
//h    -paczka budowana
class SUpdateLive : public CSPacket
{
  int _newLive;		//nowe zycie
 public:
  SUpdateLive(int newLive):CSPacket()
    {
      _newLive=newLive;
      MyName="26FE update live";
    };
  ~SUpdateLive(){};
  HexBuff * build()
    {
      unsigned char t[]={0xC1,0x07,0x26,0xFE,0x00,0x3F,0x00,0x00};
      (*h)[0].writeAC(t,7);
      (*h)[4].writeI(_newLive,false);
      return h;
    };
	
};

#endif /*SUPDATELIVE_H_*/
