#ifndef SC1A0UNKNOWN_H_
#define SC1A0UNKNOWN_H_
#include "Protocol/SBPacket.h"

//clasa : SC1A0Unknown
//h    -paczka budowana
class SC1A0Unknown : public CSPacket
{
 //_;		//
public:
	SC1A0Unknown( ):CSPacket()
	{
	//_=;
		MyName="A0 unknown request";
	};
	 ~SC1A0Unknown(){};
	HexBuff * build()
	{
	unsigned char t[]={0xc1, 0x05, 0xa0, 0x03, 0xff};
	(*h)[0].writeAC(t,0x05);
	return h;
	};
	
};

#endif /*SC1A0UNKNOWN_H_*/
