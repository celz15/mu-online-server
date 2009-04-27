#ifndef CCHARACTERMOVE_
#define CCHARACTERMOVE_
#include "Protocol/CBPacket.h"
#include "Protocol/SNpcMiting.h"
#include "Protocol/SForgetId.h"
#include "Protocol/SCharacterMiting.h"
#include "Protocol/SItemsMiting.h"
#include "Protocol/ProtocolCore.h"
//clasa: CCaracterMove
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

class CCharacterMove:public CBPacket {
	int step_count;
	int newx;
	int newy;
	
public:
CCharacterMove(HexBuff *b,MuClientTheard *t):CBPacket(b,t){};
	virtual ~CCharacterMove(){};
	void debuild()
	{
		//TODO napisac wkonc odczytywanie AKTUALNYCH wsp z paczki
  		newx=(*buff)[3].readC(); // get last x
  		newy=(*buff)[4].readC(); // get last y
//  		std::cout << "--------------------character movr-----------------\n";
  		MuPcInstance* activeChar = _cl->getActiveCharacter();
//		cout <<"poieram aktywna postac\n";
		if(!activeChar)cout <<"nie mam aktywnego chara\n";
  		activeChar->MoveTo(newx,newy);
//		cout <<"utawiam nowe wsp\n";
  		//teraz powinnysmy je wyslac do odpowiedniego miejsca
  		//wyslac spreparowaa paczke do klijentow widzacych mnie
	  	std::vector<MuObiect*> known=_cl->getActiveCharacter()->getKnowsObiects();
	  	std::vector<MuObiect*> toDelte;
//		cout << "pobieram postacie na okolo wdystansie 20kr\n";
	  	int toe=0;
	  	int toa=0;
//	  	std::cout <<"		ZNANYCH   :" <<known.size()  << "\n";
	  	if(!known.empty())
	  	for (int i = 0; i < known.size(); i++)
	  	{
	  		MuObiect* obj=known[i];
//	  		std::cout << "O:" << obj->getOId() << "-D> "<<distance(obj,activeChar)<<"\n";
	  		if(distance(obj,activeChar)>100)
	  		{
	  			toe++;
	  			toDelte.push_back(obj);
	  		}
	  	};
	  
	  	if(!toDelte.empty())
	  	for (int i = 0; i < toDelte.size(); i++)
		{
			activeChar->removeKnownObiect(toDelte[i]);
			toDelte[i]->removeKnownObiect(activeChar);
			activeChar->Send(new SForgetId(toDelte[i]->getOId()));
		};
//			std::cout <<"		USUNIETYCH:" << toe << "\n";
		//teraz sprawdzamy kto wszedl nowy w widocznuy teren
		std::vector<MuObiect*> visible = 
		_cl->getActiveCharacter()->getM()->getVisibleObjects(activeChar, 10);
		
		if(!visible.empty())
		{
			vector<MuObiect *> newNPC;
			vector<MuObiect *> newPC;
			vector<MuObiect *> newItem;
		for (int i = 0; i < visible.size(); i++)
		{
			if (! activeChar->searchID(visible[i]->getOId()))
			{
			toa++;
			switch(visible[i]->getMType())
			{
				case 1:newPC.push_back(visible[i]);break;
				case 4:newNPC.push_back(visible[i]);break;
				case 5:newItem.push_back(visible[i]);break;
				default:std::cout << "Nieznany miting";break;
			};
			activeChar->addKnownObiect(visible[i]);
			visible[i]->addKnownObiect(activeChar);
			}
		}
		if(!newNPC.empty())
		{
		SNpcMiting * npc=new SNpcMiting(newNPC); // twoze paczke z nowymi Npc
		activeChar->Send(npc);
		delete npc;
		};
		if(!newPC.empty())
		{
		SCharacterMiting * pc=new SCharacterMiting(newPC); // twoze paczke z nowymi Npc
		activeChar->Send(pc);
		delete pc;
		};
		if(!newItem.empty())
		{
			//std::cout << newItem.size();
		SItemMiting * it=new SItemMiting(newItem); // twoze paczke z nowymi Npc
		activeChar->Send(it);
		delete it;
		};
		};
//			std::cout <<"		DODANYCH   :" << toa << "\n";
	  		
	  	};
	
	
	int distance(MuObiect *a, MuObiect *b)
	{
		int dX = a->getX() - b->getX();
		int dY = a->getY() - b->getY();
		return ( dX*dX + dY*dY );
	}
 };

#endif /*CCHARACTERMOVE_*/
