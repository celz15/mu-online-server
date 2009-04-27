#ifndef SUPDATEMAXBASELIVE_H_
#define SUPDATEMAXBASELIVE_H_
#include "Protocol/SBPacket.h"

//clasa : SUpdateMaxBaseLive
//h    -paczka budowana
class SUpdateMaxBaseLive : public CSPacket
{
int  _live;		//max live
public:
	SUpdateMaxBaseLive(int  live):CSPacket()
	{
	_live=live;
		MyName="FE00	Update max live";
	};
	 ~SUpdateMaxBaseLive(){};
	HexBuff * build()
	{
	unsigned char t[]={0xC1  ,0x07  ,0x26  ,0xFE  ,0x00  ,0x3F  ,0x00,0x00,0x00};
	(*h)[0].writeAC(t,0x08);
	(*h)[4].writeI(_live,false);
	return h;
	};
	
};

#endif /*SUPDATEMAXBASELIVE_H_*/
