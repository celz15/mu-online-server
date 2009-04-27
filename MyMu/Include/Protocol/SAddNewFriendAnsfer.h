#ifndef SADDNEWFRIENDANSFER_H_
#define SADDNEWFRIENDANSFER_H_
#include "Protocol/SBPacket.h"

//clasa : SAddNewFriendAnsfe
//h    -paczka budowana
class SAddNewFriendAnsfer : public CSPacket
{
std::string  _name;		//nazwa dodawanego
unsigned char _serv;//flaga dodawania
bool _succes;
public:
	SAddNewFriendAnsfer(std::string name ,bool succes,unsigned char serv=0xff ):CSPacket()
	{
	_name=name;
	_serv=serv;
	_succes=succes;
		MyName="C1 friend add ansfer";
	};
	 ~SAddNewFriendAnsfer(){};
	HexBuff * build()
	{
		if (_succes){
		unsigned char t[]={
			//                  ?    n    n      n     n      n     n     n     n     n      n   flag
			0xc1 ,0x0f ,0xc1 ,0x01 ,0x6d ,0x69 ,0x6b ,0x69  ,0x00 ,0x77 ,0x00 ,0x08 ,0x00 ,0x00 ,0x00
		};
		(*h)[0].writeAC(t,0x0f); 
		(*h)[4].writeS(_name);
		(*h)[14].writeC(_serv);
		
		} else
		{
			unsigned char t[]={
			
			0xC1,0x05,0xC1,0x00,0x00,0x01
			};
			(*h)[0].writeAC(t,0x05);
		};
	
	return h;
	};
	
};

#endif /*SADDNEWFRIENDANSFER_H_*/
