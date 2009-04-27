#ifndef CCHARACTERLISTREQUEST_H_
#define CCHARACTERLISTREQUEST_H_

#include "CBPacket.h"
#include "Protocol/SCharacterListAnsfer.h"
#include "DB/BDUsers.h"

class CCharacterListRequest : public CBPacket
{
	BDUsers * bd;
public:
	CCharacterListRequest(HexBuff *b, MuClientTheard *t):CBPacket(b,t)
	{
	std::cout << "Character list request cons\n";
	int dbId=t->getUser()->getDBID();
	std::cout<< "po poborze dbid\n";
	BDBase* baza=t->getDB();
	std::cout<<"po ustawienu dbbase\n";
		bd=new BDUsers(dbId,baza);			//tworzymy klaswe do zarzadzaniema dbcharters
	std::cout << "po kons \n";
	/*TODO test */
	};
	virtual ~CCharacterListRequest()
	{
	delete bd;	
	}

	void debuild()
	{
	std::cout << "przed getuser\n";
	std::cout<<"SYSTEM>>>  Laduje postacie usera: " <<_cl->getUser()->getUser() << "\n"; 
	for (int c=1;c<=_cl->getUser()->getCharCount();c++)
	{
		_listCharacter ci=bd->GetCharacter(c);
		cout<<"->CHAR["<<c-1<<"]  Nick: "<<ci.Nick << " LvL: " << ci.lvl << " Class: " <<ci.klasa << "\n"; 
		//poniewaz to nie sa nowe postacie ustawiamy flage nchar na false
		_cl->getMyCharacterList()->addNewCharacter(new MuCharacterBase(ci.Nick,ci.klasa,ci.lvl,false));
	}
	SCharacterListAnsfer *t=new SCharacterListAnsfer(_cl->getMyCharacterList());
	_cl->Send(t);
	delete t;

	};
};

#endif /*CCHARACTERLISTREQUEST_H_*/
