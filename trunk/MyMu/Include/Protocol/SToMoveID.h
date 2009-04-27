#ifndef STOMOVEID_H_
#define STOMOVEID_H_

#include "Protocol/SBPacket.h"

class SToMoveID : public CSPacket
{
	int Id;
	unsigned char x;
	unsigned char y;
	unsigned char f;
public:
	SToMoveID(int id,unsigned char pos_x,unsigned char pos_y,unsigned char flag):
							CSPacket(),Id(id),x(pos_x),y(pos_y),f(flag){};
	virtual ~SToMoveID();
	HexBuff* build();
};

#endif /*STOMOVEID_H_*/
