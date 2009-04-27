#ifndef CENTERSELECTEDCHARACTERREQUEST_H_
#define CENTERSELECTEDCHARACTERREQUEST_H_

#include "CBPacket.h"
#include "Protocol/SPingReplay.h"
#include "Protocol/SC103Unknown.h"
#include "Protocol/SC1A0Unknown.h"
#include "Protocol/SSelectedCharacterStats.h"
#include "Protocol/SRegisterNewSkill.h"
#include "Protocol/SFriendList.h"
#include "Protocol/SClientSettings.h"
#include "Protocol/SInwentoryList.h"
#include "MuObiects/MuPcInstance.h"
#include "MuObiects/MuObjectsPool.h"

class CEnterSelectedCharacterRequest : public CBPacket
{
  std::string nick; 				//nick postaci do zaladowania na mape
public:
  CEnterSelectedCharacterRequest(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
  virtual ~CEnterSelectedCharacterRequest(){};
  void debuild()
  {
    nick= (*buff)[4].readS(10);
    cout << "Wybrany Nick: " << nick <<"\n";
		
		
    //montujemy aktualnego chara
    
    MuPcInstance *pc=ObiectPool::getInstance()->newMuPcInstance();
		 
    pc->Set(_cl->getMyCharacterList()->getCharacter(nick)); // pobieramy informacje z MucharacterBase
		
    pc->setM(MuMaps::getInstance()->getMap(0));					//pobieramy mape
    pc->setOId(_cl->getConnectID());
    pc->setX(170); 
    pc->setY(127);
    pc->setStats(10,10,10,10,10);
    pc->setMType(1);										//zaznaczam sie jako gracz
    pc->setF(0x00);											//ustawiamy flage
    pc->setExp(500,5);	
    pc->setConnected(_cl->getConnected());					//ustawiamy polaczenie
		
    pc->getM()->addVisibleObject(pc);
    //		pc->getM()->NewObiect(pc);				//dodajemy sie na mape
    pc->updateNLvlExp();						//ustawiamy lvlup exp
    pc->UpdateMaxims();							//usatwiamy hp,mp,sp
	
			
    _cl->setActiveCharacter(pc);
    std::cout << "po ustawieniu usera\n";
		
		
    SSelectedharacterStats *t=	new SSelectedharacterStats(
							   pc->getX(),pc->getY(),pc->getM()->getCode(), //pos
							   pc->getExp(),1000,pc->getLp(),//exp
							   pc->getStr(),pc->getAgl(),pc->getVit(),pc->getEnr(), //stat agl..
							   pc->getCurentHP(),pc->getMaxBaseHP(),pc->getCurentMP(),pc->getMaxBaseMP(),pc->getCurentSP(),pc->getMaxBaseSP(),//zycie mana,st
							   10, // zen
							   100,100 // spare
							   );
    std::cout << "po zbudowaniu paczki postaci\n";
    //_cl->ASend(new SPingReplay(0x20));
    //_cl->ASend(new SC103Unknown());
    _cl->ASend(t);
    _cl->ASend(new SInwenoryList());
    _cl->ASend(new SRegisterNewSkill(NULL));
    //_cl->ASend(new SC1A0Unknown());
    //_cl->ASend(new SClientSettings());
    //_cl->ASend(new SFriedList());
    _cl->MSend();
    //Send(t);
		
    //_cl->Send(
    //_cl->ASend(new SRegisterNewSkill(NULL));
    //_cl->Send(new SFriedList());
    //pc->MyItemList();
    //std::cout << "po send.\n";
			
    delete t;
    HexBuff *buff=new HexBuff;					//alokuje miejsce na paczke przychozaca	
    _cl->getConnected()->Recv(*buff);
    //pc->CheckStatusPC(); 
    //pc->MyItemList();
    //sprawdzamy status [testowe]
  };
};

#endif /*CENTERSELECTEDCHARACTERREQUEST_H_*/
