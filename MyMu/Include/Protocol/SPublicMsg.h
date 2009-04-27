#ifndef SPUBLICMSG_H_
#define SPUBLICMSG_H_
#include <string>
#include "Protocol/SBPacket.h"

//clasa : SPublicMsg
//h    -paczka budowana
class SPublicMsg : public CSPacket
{
std::string _nick;		//nick postaci
std::string _msg;		//nick postaci
public:
	SPublicMsg(std::string nick,std::string msg):CSPacket()
	{
	_nick=nick;
	_msg=msg;
		MyName="00 Public msg";
	};
	 ~SPublicMsg(){};
	HexBuff * build()
	{
		int len=calculateLen();
	unsigned char t[]={0xC1,len,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	(*h)[0].writeAC(t,13);
	
	(*h)[3].writeS(_nick);
	(*h)[13].writeS(_msg);
	(*h)[len].writeC(0x00);
	(*h)[len+1].writeC(0x00);
	return h;
	};
	int calculateLen(){
		return 14+_msg.length();};
};

#endif /*SPUBLICMSG_H_*/
