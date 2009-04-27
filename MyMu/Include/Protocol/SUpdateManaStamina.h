#ifndef SUPDATEMANASTAMINA_H_
#define SUPDATEMANASTAMINA_H_
#include "Protocol/SBPacket.h"

//clasa : SUpdateManaStamina
//h    -paczka budowana
class SUpdateManaStamina : public CSPacket
{
int _mana;		//new mp
int _stam;		//new sp
public:
	SUpdateManaStamina(int mana,int st):CSPacket()
	{
	_stam=st;	
	_mana=mana;
		MyName="27FF update mana stamina";
	};
	 ~SUpdateManaStamina(){};
	HexBuff * build()
	{
		unsigned char t[]={0xC1,0x08,0x27,0xFF,0x00,0x42,0x00,0x17,0x00};
		(*h)[0].writeAC(t,8);
		(*h)[4].writeI(_mana,false);// moze byc odwrotni hilo sprawdzic
		(*h)[6].writeI(_stam,false);//-|-
	return h;
	};
	
};

#endif /*SUPDATEMANASTAMINA_H_*/
