#ifndef SA0UNKOWNREP_H_
#define SA0UNKOWNREP_H_
#include "Protocol/SBPacket.h"

//clasa : SA0UnkownRep
//h    -paczka budowana
class SA0UnkownRep : public CSPacket
{

public:
	SA0UnkownRep():CSPacket()
	{
	
		MyName="A0 unkown replay";
	};
	 ~SA0UnkownRep(){};
	HexBuff * build()
	{
	unsigned char t[]={0xc1 ,0x05 ,0xa0 ,0x01 ,0xaa};
	(*h)[0].writeAC(t,0x05);
	return h;
	};
	
};

#endif /*SA0UNKOWNREP_H_*/
