#ifndef SIDDIE_H_
#define SIDDIE_H_

#include "Protocol/SBPacket.h"

class SIdDie : public CSPacket
{
	int id;
public:
	SIdDie(int _id):CSPacket(),id(_id){};
	virtual ~SIdDie();
	HexBuff* build();
};

#endif /*SIDDIE_H_*/
