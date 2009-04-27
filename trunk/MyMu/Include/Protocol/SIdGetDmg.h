#ifndef SIDGETDMG_H_
#define SIDGETDMG_H_

#include "Protocol/SBPacket.h"

class SIdGetDmg : public CSPacket
{
	int id;
	int dmg; // le dostal
	unsigned char flag; // flaga
	
public:
	SIdGetDmg(int _id,int _dmg,unsigned char f):CSPacket(),id(_id),dmg(_dmg),flag(f)
	{
	MyName="D9 Id Got DMG";
	};
	virtual ~SIdGetDmg();
	HexBuff * build();
};

#endif /*SIDGETDMG_H_*/
