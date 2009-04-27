#ifndef SINCRASESTATANSFER_H_
#define SINCRASESTATANSFER_H_
#include "Protocol/SBPacket.h"

//clasa : SIncraseStatAnsfer
//h    -paczka budowana
class SIncraseStatAnsfer : public CSPacket
{
int _manaU;		//mana upd
int _stamU;		//stam upd
bool _f; 		//flaga
int _st;		//statystyka

public:
	SIncraseStatAnsfer(bool f,int s,int manau,int stamu):CSPacket()
	{
	_manaU=manau;
	_stamU=stamu;
	_f=f;
	_st=s;
		MyName="F306 stat incrase ansfer";
	};
	 ~SIncraseStatAnsfer(){};
	HexBuff * build()
	{
	unsigned char t[]={0xC1,0x0A,0xF3,0x06,0x13,0x00,0x44,0x00,0x18,0x00,0x00,0x00};
	unsigned char b=0x00;
	b=_st;
	unsigned char f;
	if (_f)f=0x10;
	b=b|f;
	(*h)[0].writeAC(t,0x0a+1);
	(*h)[4].writeC(b);			//co i czy sied udalo 
	(*h)[6].writeI(_manaU,false);
	(*h)[8].writeI(_stamU,false);
	return h;
	};
	
};

#endif /*SINCRASESTATANSFER_H_*/
