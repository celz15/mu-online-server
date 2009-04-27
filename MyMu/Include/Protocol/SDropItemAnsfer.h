#ifndef SDROPITEMANSFER_H_
#define SDROPITEMANSFER_H_
#include "Protocol/SBPacket.h"

//clasa : SDropItemAnsfer
//h    -paczka budowana
class SDropItemAnsfer : public CSPacket
{
bool _succes;		//is drop ?
int  _slot;			//slot from drop item
public:
	SDropItemAnsfer(bool succes,int slot):CSPacket()
	{
	_succes=succes;
	_slot=slot;
		MyName=" 23 Drop item ansfer";
	};
	 ~SDropItemAnsfer(){};
	HexBuff * build()
	{
	unsigned char t[]={0xc1 ,0x05 ,0x23 ,0x01 ,0x0e};
	(*h)[0].writeAC(t,0x05);
	(*h)[3].writeB(_succes);
	(*h)[4].writeC(_slot);
	return h;
	};
	
};

#endif /*SDROPITEMANSFER_H_*/
