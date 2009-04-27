#ifndef SLVLUP_H_
#define SLVLUP_H_
#include "Protocol/SBPacket.h"

//clasa : SLvlUp
//C1  12  F3  05  05  00  05  00  42  00  48  00  18  00  00  00  02  00
//h    -paczka budowana
class SLvlUp : public CSPacket
{
int _lvl;		//new lvl
int _lp;		// lvl points
int _nhp;		//new hp
int _nmp;		//mp
int _nsp;		//stamina
public:
	SLvlUp(int lvl,int lp,int nhp,int nmp,int nsp):CSPacket()
	{
	_lvl=lvl;
	_lp=lp;
	_nhp=nhp;
	_nmp=nmp;
	_nsp=nsp;
		MyName="f305 LvL uP!!";
	};
	 ~SLvlUp(){};
	HexBuff * build()
	{
	unsigned char t[]={0xC1  ,0x12  ,0xF3  ,0x05  ,0x05  ,0x00  ,0x05  ,0x00  ,0x42  ,0x00  ,0x48  ,0x00  ,0x18  ,0x00  ,0x00  ,0x00  ,0x02  ,0x00,0x00,0x00};
	(*h)[0].writeAC(t,0x12+1);
	(*h)[4].writeI(_lvl,true);
	(*h)[6].writeI(_lp,true);
	(*h)[8].writeI(_nhp,true);
	(*h)[10].writeI(_nmp,true);
	(*h)[12].writeI(_nsp,true);
	return h;
	};
	
};

#endif /*SLVLUP_H_*/
