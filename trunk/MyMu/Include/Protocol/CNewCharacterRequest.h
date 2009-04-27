#ifndef CNEWCHARACTERREQUEST_
#define CNEWCHARACTERREQUEST_


#include "Protocol/CBPacket.h"
#include "Protocol/SNewCharacterAnsfer.h"
#include "MuObiects/MuCharacterBase.h"


class CNewCharacterRequest:public CBPacket {
	std::string _name;
	int			_class;
public:
CNewCharacterRequest(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
	virtual ~CNewCharacterRequest(){};
	void debuild()
	{
	_name=(*buff)[4].readS(10);
	_class=(*buff)[14].readC();
	//dane donowego
	int n=_cl->getMyCharacterList()->getCharacterCount(); // kolejna postac
	MuCharacterBase * _char=new MuCharacterBase(_name,_class);
	_cl->getMyCharacterList()->addNewCharacter(_char); // doajemy delikwenta
	_cl->Send(new SNewCharacterAnsfer(_char,1,n)); // twozymy kazdego

	//todo dodac aktualizowanie DB!!!!

	std::cout << "New char: Name: " << _name << " Class: " << _class << "\n";
	}
};


#endif /*CNEWCHARACTERREQUEST_*/



