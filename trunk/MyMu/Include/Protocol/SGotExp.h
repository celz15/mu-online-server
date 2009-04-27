#ifndef SGOTEXP_H_
#define SGOTEXP_H_
#include "Protocol/SBPacket.h"

//clasa : SGotExp
//h    -paczka budowana
class SGotExp : public CSPacket
{
int _from;		//id od ktorego dostaje exp
int _ile;		//ile expa
public:
	SGotExp(int from,int ile):CSPacket()
	{
		_ile=ile;
		_from=from;
		MyName="16 Got Experance fro id";
	};
	 ~SGotExp(){};
	HexBuff * build()
	{
	unsigned char t[]={
		//0xC1,0x09,0x16,0x03,0xFE,0x00,0x1E,0x00,0x0A,0x00,0x00};
		//c3,0x08,0x16,0x03,0x6e,0x13,0x88,0x01,0xe9};               
		0xc3,0x08,0x16,0x00,0x00,0x00,0x02,0x00,0x00};	
	(*h)[0].writeAC(t,8);
	 //(*h)[3].writeI(_from,false);
	 //(*h)[6].writeI(_ile,false);
	return h;
	};
	
};
//TODO (test)
#endif /*SGOTEXP_H_*/
