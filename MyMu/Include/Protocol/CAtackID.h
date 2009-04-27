#ifndef CATACKID_H_
#define CATACKID_H_
#include "Protocol/CBPacket.h"
#include "MuObiects/MuMonsterInstance.h"


//clasa: CAtackID
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

class CAtackID:public CBPacket {
	int id;			//kogo atakujemy
	int d;			//z ktorej strony postaci jest
	
public:
CAtackID(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
	virtual ~CAtackID(){};
	void debuild()
	{
	long exp=0;
	id=(*buff)[3].readI();
	d=(*buff)[6].readC();
	std::cout << "Atack na id: " <<id << "w kierunku " << d<<".\n";
	if((_cl->getActiveCharacter()->getM()->getId(id)->getMType())==4)
	{
		MuMonsterInstance *c=static_cast<MuMonsterInstance*> (_cl->getActiveCharacter()->getM()->getId(id));
		int dmg=_cl->getActiveCharacter()->getRealDmg();
		
		
		c->orbinateDmg(dmg);
		if(c->isDead())
		{
			_cl->getActiveCharacter()->IGotExp(id,9999);
			_cl->getActiveCharacter()->getExp(c->getExp());
		};
		 
	};
	};
};
#endif /*CATACKID_H_*/
