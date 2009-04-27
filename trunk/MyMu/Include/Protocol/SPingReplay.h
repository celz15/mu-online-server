#ifndef SPINGREPLAY_H_
#define SPINGREPLAY_H_
#include "Protocol/SBPacket.h"

//clasa : SPingReplay
//h    -paczka budowana
class SPingReplay : public CSPacket
{
unsigned char _ping;		//niemam pojecia
public:
	SPingReplay(unsigned char ping):CSPacket()
	{
	_ping=ping;
		MyName="0F Ping Replay";
	};
	 ~SPingReplay(){};
	HexBuff * build()
	{
	unsigned char t[]={0xc1, 0x04, 0x0f, _ping};
	(*h)[0].writeAC(t,0x04);
	return h;
	};
	
};

#endif /*SPINGREPLAY_H_*/
