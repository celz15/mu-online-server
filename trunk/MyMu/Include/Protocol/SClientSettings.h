#ifndef CCLIENTSETTINGS_H_
#define CCLIENTSETTINGS_H_
#include "Protocol/SBPacket.h"

//clasa : SClientSettings
//h    -paczka budowana
class SClientSettings : public CSPacket
{
//paraTyp _paraName;		//opis
public:
	SClientSettings():CSPacket()
	{
	//_paraName=paraName;
		MyName="F330 Client Settings";
	};
	 ~SClientSettings(){};
	HexBuff * build()
	{
		unsigned char t[]={
		0xc1, 0x13, 0xf3, 0x30, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 
		0x04, 0x08, 0x14
		};
		(*h)[0].writeAC(t,0x13);
	return h;
	};
	
};

#endif /*CCLIENTSETTINGS_H_*/
