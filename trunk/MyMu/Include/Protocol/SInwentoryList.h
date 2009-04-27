#ifndef SINWENTORYLIST_H_
#define SINWENTORYLIST_H_
#include "Protocol/SBPacket.h"
#include "MuObiects/MuHandInwentory.h"

//clasa : SInwenoryList
//h    -paczka budowana
class SInwenoryList : public CSPacket
{
MuHandInwentory* _inw;		//inw
public:
	SInwenoryList():CSPacket()
	{
	//_inw=inw;
		MyName="F310 Inwentory list";
	};
	 ~SInwenoryList(){};
	HexBuff * build()
	{
unsigned  char t[]={

//0xc4 ,0x00,0x05 ,0xf3 ,0x10 
0xc4 ,0x00 ,0x0b ,0xf3 ,0x10 ,0x01 ,0x0c ,0xe3 ,0x00 ,0x00 ,0x80 ,0x00,00};



	(*h)[0].writeAC(t,0x0c);
	//h->CryptMe(4);
	return h;
	};
	
};

#endif /*SINWENTORYLIST_H_*/
