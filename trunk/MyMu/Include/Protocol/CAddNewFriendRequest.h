#ifndef CADDNEWFRIENDREQUEST_H_
#define CADDNEWFRIENDREQUEST_H_
#include "Protocol/CBPacket.h"
#include "Protocol/SAddNewFriendAnsfer.h"

//clasa: CAddNewUserRequest
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

class CAddNewUserRequest:public CBPacket {
	std::string _name;		//imie postaci do dodania jako friend
public:
CAddNewUserRequest(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
	virtual ~CAddNewUserRequest(){};
	void debuild()
	{
	
	_name=(*buff)[3].readS(10);
	std::cout << "Add Friend : "<<_name << " request \n";
	_cl->Send(new SAddNewFriendAnsfer(_name,true,00)); // dodany pomyslnie
	}
	//c1 0d ca 68 79 6a 75 75 75 00 00 00 00 odp klijenta po kliknieciu na chat 
	//          n  n  n  n  n  n  n  n  n  n   
}; 
#endif /*CADDNEWFRIENDREQUEST_H_*/
