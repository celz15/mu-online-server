#ifndef CPUBLICMSG_H_
#define CPUBLICMSG_H_
#include "Protocol/CBPacket.h"
#include "Protocol/SPublicMsg.h"
#include "Protocol/SItemList.h"
#include "Protocol/SGotExp.h"
#include "Protocol/SPutItemInInw.h"

//clasa: CPublicMsg
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

class CPublicMsg:public CBPacket {
	std::string msg; // wiadomsc
	std::string who;
public:
CPublicMsg(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
	virtual ~CPublicMsg(){};
	void debuild()
	{
		int msglen=(*buff)[1].readC()-14;
		who=(*buff)[3].readS(10);
		msg=(*buff)[13].readS(msglen);
	    std::cout << "Public msg: od" <<who << "["<< msg<<"]\n";
	    //jesli to komenda to wykonujemy i jesl nie jest to komenda wtedy wysylamy komunikat ?
	   if(msg.c_str()[0]=='\\')
	   switch (msg.c_str()[1])
	   {
	   	case '1': _cl->Send(new SItemList());break;
	   	case '2': _cl->Send(new SGotExp(1,1));break;
	   	case '3': 
	   	{
	   		unsigned char t[]={0x21,0x00,0x14,0x00,0x00};
	   		MuItemInInwentory * i=new MuItemInInwentory();
	   		i->setHexItem(t);
	   		_cl->Send(new SPutItemInInwetory(i));break;
	   	};
	   };
	    //		_cl->getCommands()->ParseComandLine(msg); 
	    
	    _cl->Send(new SPublicMsg(who,msg));
	}
};
#endif /*CPUBLICMSG_H_*/
