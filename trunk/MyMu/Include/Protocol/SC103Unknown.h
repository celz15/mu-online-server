#ifndef SC103UNKNOWN_H_
#define SC103UNKNOWN_H_
#include "Protocol/SBPacket.h"

//clasa : SC103Unknown
//h    -paczka budowana
class SC103Unknown : public CSPacket
{

public:
	SC103Unknown( ):CSPacket()
	{
	
		MyName="03 unknown";
	};
	 ~SC103Unknown(){};
	HexBuff * build()
	{
		unsigned char t[]={
	0xc1, 0x06, 0x03, 0x20, 0xd6, 0xc5};
	(*h)[0].writeAC(t,0x06); 
	return h;
	};
};

#endif /*SC103UNKNOWN_H_*/
