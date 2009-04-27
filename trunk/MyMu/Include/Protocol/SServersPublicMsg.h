#ifndef SSERVERSPUBLICMSG_H_
#define SSERVERSPUBLICMSG_H_
#include "Protocol/SBPacket.h"
typedef enum EMsg{
	Mjelow=0x00,                
	Mblue=0x01,					
	Mguild=0x02,
	Mscrol=0x0A
}EMsg;
//clasa : SServersPublicMsg
//h    -paczka budowana
class SServersPublicMsg : public CSPacket
{
EMsg typ;				//typ wiadomosci	
std::string _msg;		//wiadomosc
public:
	SServersPublicMsg(std::string msg,EMsg ms=Mblue):CSPacket()
	{
	typ=ms;
	_msg=msg;
		MyName="0D widomosci serwerowe";
	};
	 ~SServersPublicMsg(){};
	HexBuff * build()
	{
	int s=13+_msg.length();
	unsigned char t[]={
		0xC1 ,0x3B ,0x0D ,0x01 ,
		0x00 ,0x00 ,0x00 ,0x00 ,
		0x00 ,0x00 ,0x00 ,0x00 ,0x00,0x00
		};
		(*h)[0].writeAC(t,13);
		mC1Header(0x0D,typ,s);
		(*h)[13].writeS(_msg);
		(*h)[s].writeC(0x00);
		(*h)[s+1].writeC(0x00);
	
	
	return h;
	};
	
};


#endif /*SSERVERSPUBLICMSG_H_*/
