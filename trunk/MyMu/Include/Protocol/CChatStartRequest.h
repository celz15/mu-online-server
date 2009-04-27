#ifndef CChatStartRequest_H_
#define CChatStartRequest_H_
#include "Protocol/CBPacket.h"
#include "Protocol/SChatStartAnsfer.h"

//clasa: CAddNewUserRequest
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

class CChatStartRequest:public CBPacket {
	std::string _name;		//imie postaci do dodania jako friend
public:
CChatStartRequest(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
	virtual ~CChatStartRequest(){};
	void debuild()
	{
	
	_name=(*buff)[3].readS(10);
	std::cout << "chat reqyuest with : "<<_name << "  \n";
	_cl->Send(new SChatStartAnsfer(_name));//_name,true,00)); // dodany pomyslnie
	}
	//c1 0d ca 68 79 6a 75 75 75 00 00 00 00 odp klijenta po kliknieciu na chat 
	//          n  n  n  n  n  n  n  n  n  n   
}; 
#endif /*CCChatStartRequest_H_*/
