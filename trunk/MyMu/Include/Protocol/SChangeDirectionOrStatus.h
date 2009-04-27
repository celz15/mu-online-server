#ifndef SCHANGEDIRECTIONORSTATUS_H_
#define SCHANGEDIRECTIONORSTATUS_H_
#include "Protocol/SBPacket.h"

//clasa : SChangeDirectionOrStatus
//h    -paczka budowana
class SChangeDirectionOrStatus : public CSPacket
{
unsigned char _status;		//status postaci
unsigned char _direct;		//kierunek patrzenia 
public:
	SChangeDirectionOrStatus(unsigned char status,unsigned char direction):CSPacket()
	{
	_status=status;
	_direct=direction;
		MyName="18 Czange direction or status";
	};
	 ~SChangeDirectionOrStatus(){};
	HexBuff * build()
	{
	unsigned char t[]={0xC1,0x05,0x18,_direct,_status ,0x00};
	(*h)[0].writeAC(t,0x05); 
	return h;
	};
	
};

#endif /*SCHANGEDIRECTIONORSTATUS_H_*/
