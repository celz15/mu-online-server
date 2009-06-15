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
    //_cl->ReadCharacter(nick);
		
    //montujemy aktualnego chara
    
    //MuPcInstance *pc=ObiectPool::getInstance()->newMuPcInstance(_cl->getConnectID());
		 
    //  pc->SetFromCharacterBase(_cl->getMyCharacterList()->getCharacter(nick)); // pobieramy informacje z MucharacterBase
    
    // pc->setPosMapNb(MuMaps::getInstance()->getMap(0)->getCode());		
    
    // pc->setIndex(_cl->getConnectID());
    //pc->setPortView(new MuViewPortSet(_cl->getConnectID(),10));
    //pc->setPosXY(170,127);
    //pc->setPosNewXY(170,127);
    //pc->setStats(10,10,10,10,10);
    //pc->setType(O_Player);										//zaznaczam sie jako gracz
    //pc->setPosStatus(0x00);											//ustawiamy flage
    //pc->setCurExp(500,5);	
    //pc->setConnected(_cl->getConnected());					//ustawiamy polaczenie
		
    //MuMaps::getInstance()->getMap(pc->getPosMapNb())->storeNewObiect(pc);
    
    
    //pc->updateNLvlExp();						//ustawiamy lvlup exp
    //pc->UpdateMaxims();							//usatwiamy hp,mp,sp
	
    _cl->ReadCharacter(nick);
   MuPcInstance * pc= _cl->getActiveCharacter();
    std::cout << "po ustawieniu usera\n";
		
		
    SSelectedharacterStats *t=	new SSelectedharacterStats();
    t->setPos(pc->getPosX(),pc->getPosY(),pc->getPosMapNb(), pc->getPosHead());
    t->setExp(pc->getCurExp(),pc->getNextExp(),pc->getCurLp());
    t->setStats(pc->getStr(),pc->getAgl(),pc->getVit(),pc->getEnr());
    t->setMaxHpMpSt(pc->getStatCurHp(),pc->getStatMaxHp(),
		    pc->getStatCurMp(),pc->getStatMaxMp(),
		    pc->getStatCurSt(),pc->getStatMaxSt());
    t->setZen(pc->getInwZen());
    t->setPkLvl( 0,0x02); // zen
    t->setAddPoints(100,100);
    std::cout << "po zbudowaniu paczki postaci\n";
    //_cl->ASend(new SPingReplay(0x20));
    //_cl->ASend(new SC103Unknown());
    _cl->Send(t);
    //_cl->ASend(new SRegisterNewSkill(NULL));
    //_cl->ASend(new SC1A0Unknown());
    //_cl->ASend(new SClientSettings());
    //_cl->ASend(new SFriedList());
    //_cl->MSend();
    
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
    pc->Send(new SItemList(_cl->getCharactersInwentory()->getAsVector()));
    pc->MoveTo(pc->getPosX(),pc->getPosY());
    ObiectPool::getInstance()->printUsages();
  };
};

#endif /*CENTERSELECTEDCHARACTERREQUEST_H_*/
