#ifndef SREGISTERNEWSKILL_H_
#define SREGISTERNEWSKILL_H_
#include "Protocol/SBPacket.h"

//clasa : SRegisterNewSkill
//h    -paczka budowana
class SRegisterNewSkill : public CSPacket
{
MuSkill* _Skill;		//skill do regniecia w klijecie
int l;					//ktory to skill
public:
	SRegisterNewSkill(MuSkill* Skill):CSPacket()
	{
	_Skill=Skill;
		MyName="F3 11 FE Register Skll";
	};	
	 ~SRegisterNewSkill(){};
	HexBuff * build()
	{                     
	//unsigned char t[]={0xC1,0x09,0xF3,0x11,0xFE,0x00,0x13,0x4C,    0x00};
	
	
	unsigned char t[]={0xc1 ,0x08 ,0xf3 ,0x11 ,0x01 ,0x00 ,0x11 ,0x01};
	//0xc1,0x09,0xf3,0x11,0x01,0x00,0x00,0x11,0x01,0x00};
	
	(*h)[0].writeAC(t,8);
	return h;
	};
	
};

#endif /*SREGISTERNEWSKILL_H_*/
