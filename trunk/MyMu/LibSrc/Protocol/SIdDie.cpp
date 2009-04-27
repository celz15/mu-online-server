#include "Protocol/SIdDie.h"

HexBuff* SIdDie::build()
{
	unsigned char t[]={0xc1,0x05,0x17,0xff,0xff,0x00,0};
	(*h)[0].writeAC(t,6);
	(*h)[3].writeI(id,false);
	return h;
};

SIdDie::~SIdDie()
{
}
