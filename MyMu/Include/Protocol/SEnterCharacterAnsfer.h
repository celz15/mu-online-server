#ifndef SENTERCHARACTERANSFER_H_
#define SENTERCHARACTERANSFER_H_
#include "Protocol/SBPacket.h"

//clasa : SEnterCharacterAnsfer
//h    -paczka budowana
class SEnterCharacterAnsfer : public CSPacket
{

public:
	SEnterCharacterAnsfer( ):CSPacket()
	{

		MyName="F303 - logowanie na mapie";
	};
	 ~SEnterCharacterAnsfer(){};
	HexBuff * build()
	{
	unsigned char t[]={
		   0xc3 ,0x33 ,0xF3 ,0x03 ,0x8E ,0x88 ,0x00 ,0x00 ,0x00 ,0x00 ,
           0x00 ,0x00 ,0x64 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x1C ,0x00 ,
           0x14 ,0x00 ,0x19 ,0x00 ,0x0A ,0x00 ,0x6E ,0x00 ,0x6E ,0x00 ,
           0x14 ,0x00 ,0x14, 0x00 ,0x0C ,0x00 ,0x19 ,0x00 ,0x12 ,0x00 ,
           0x00 ,0x00 ,0x00 ,0x00 ,0x03 ,0x00 ,0x00 ,0x00 ,0x02 ,0x00 ,
           0x0F ,0x27 ,0x00};
           //todo napisac ustawiana statow
	(*h)[0].writeAC(t,53);
	
	return h;
	};
	
};

#endif /*SENTERCHARACTERANSFER_H_*/