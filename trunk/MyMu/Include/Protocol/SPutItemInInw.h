#ifndef SPUTITEMININW_H_
#define SPUTITEMININW_H_
#include "Protocol/SBPacket.h"

//clasa : SPutItemInInwetory
//h    -paczka budowana
class SPutItemInInwetory : public CSPacket
{
MuItemInInwentory *_item;		//item do dodania
public:
	SPutItemInInwetory(MuItemInInwentory *item):CSPacket()
	{
	_item=item;
		MyName="22 Put Item In inw";
	};
	 ~SPutItemInInwetory(){};
	HexBuff * build()
	{    //                               g    i    t   e     m    m
	unsigned char t[]={
	//0xC3,0x09,0x22,0c 0x0F,0xC4,0x00,0x03,0x80,0x00,   0x00 // ?? wersja nei znana  
	0xc3,0x08,0x22,0x00,0x21,0x00,0x14,0x00,0x00 // wersja 99b+
	};
	(*h)[0].writeAC(t,0x08);
	(*h)[3].writeC(_item->getSlot());
	_item->InsertInBuff(h,4);
	return h;
	};
	
};

#endif /*SPUTITEMININW_H_*/
