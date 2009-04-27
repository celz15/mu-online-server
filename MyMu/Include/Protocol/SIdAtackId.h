#ifndef SIDATACKID_H_
#define SIDATACKID_H_
#include "Protocol/SBPacket.h"

//clasa : SIdAtackId
//h    -paczka budowana
class SIdAtackId : public CSPacket
{
int _ida;		//id atakowanego
int _id;		//id atakujacego

public:
	SIdAtackId(int id,int ida):CSPacket()
	{
		_ida=ida;
		_id=id;
		MyName="ID ATACK ID";
	};
	 ~SIdAtackId(){};
	HexBuff * build()
	{
		
		//C107181FFA0078 1ffa atakujacego id
		unsigned char t[]={0xC1,0x08 ,0x19,0x44,0x00,0x00,0x00,0x00,0x00,0x00};
		(*h)[0].writeAC(t,9);
		(*h)[4].writeI(_id,false);
		(*h)[6].writeI(_ida,false);
				
	
	return h;
	};
	
};

#endif /*SIDATACKID_H_*/
