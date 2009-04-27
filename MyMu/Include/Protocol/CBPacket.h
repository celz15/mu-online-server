#ifndef CBPACKET_H_
#define CBPACKET_H_
#include "HexBuffer/HexBuffer.h"
#include "Protocol/BaseStruct.h"

//predefinicje klas
class MuClientTheard;
//todo napisa cos
class CBPacket 
{
protected:
HexBuff *buff;
MuClientTheard* _cl;
	
public:
	CBPacket(HexBuff*b,MuClientTheard*t){buff=b;_cl=t;};
	virtual ~CBPacket();
	    HexBuff *AsHexBuff();
	virtual void debuild(){};		
};

#endif /*CBPACKET_H_*/
