#ifndef SFORGETID_H_
#define SFORGETID_H_
#include "Protocol/SBPacket.h"

//clasa : SForgetId
//h    -paczka budowana
class SForgetId : public CSPacket
{
int _Id;		//id do zapomnienia
public:
	SForgetId(int Id):CSPacket()
	{
	_Id=Id;
		MyName="14 forget ebout id";
	};
	virtual ~SForgetId(){};
	HexBuff * build()
	{
	unsigned char t[]={
		0xC1 ,0x06 ,0x14 ,0x01 ,0x03 ,0x62,0x00,0x00
	};
	(*h)[0].writeAC(t,7);
	(*h)[4].writeI(_Id,false);
	return h;
	};
	
};

#endif /*SFORGETID_H_*/
