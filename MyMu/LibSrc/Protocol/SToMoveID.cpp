#include "Protocol/SToMoveID.h"

HexBuff* SToMoveID::build()
{
	mC1Header(0xd7,0x08);
	(*h)[3].writeI(Id,false);
	(*h)[5].writeC(x);
	(*h)[6].writeC(y);
	(*h)[7].writeC(f);
	(*h)[8].writeC(0);
	return h;
}; 

SToMoveID::~SToMoveID()
{
}
