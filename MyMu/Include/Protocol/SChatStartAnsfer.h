#ifndef SChatStartAnsfer_H_
#define SChatStartAnsfer_H_
#include "Protocol/SBPacket.h"

//clasa : SC1A0Unknown
//h    -paczka budowana
class SChatStartAnsfer : public CSPacket
{
std::string  _name;		//nazwa dodawanego
public:
	SChatStartAnsfer(std::string name ):CSPacket()
	{
	_name=name;
		MyName="ca chat start request ansfer";
	};
	 ~SChatStartAnsfer(){};
	HexBuff * build()
	{
	unsigned char t[]={0xC1,0x10,0xCc,0x00,0x00,
    0x01,   //flaga ?
    't','e','s','t',0x00,0x00,0x00,0x00,0x00,  //nick ?
    
    0x10,0x67};  //wiadomosc
	
	(*h)[0].writeAC(t,0x10);
	//(*h)[6].writeS(_name);
	return h;
	};
	
};

#endif /*SC1A0UNKNOWN_H_*/
