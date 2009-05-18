#ifndef CCHARACTERMOVE_
#define CCHARACTERMOVE_
#include "Protocol/CBPacket.h"
#include "Protocol/SNpcMiting.h"
#include "Protocol/SForgetId.h"
#include "Protocol/SCharacterMiting.h"
#include "Protocol/SItemsMiting.h"
#include "Protocol/ProtocolCore.h"
#include "Protocol/BaseStruct.h"
//clasa: CCaracterMove
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

struct MovePack
{
  PMSG_HEADA _head;
  unsigned char PosX;
  unsigned char PosY;
  unsigned char MovePath[8];
};

char const stepDirections[16] = {-1, -1, 0, -1, 1, -1, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0};

class CCharacterMove:public CBPacket {
  int step_count;
  int newx;
  int newy;
	
public:
  CCharacterMove(HexBuff *b,MuClientTheard *t):CBPacket(b,t){};
  virtual ~CCharacterMove(){};
  void debuild()
  {

    MuPcInstance* activeChar = _cl->getActiveCharacter();

    unsigned char *cbuff= buff->getPointer();
    MovePack *p = (MovePack*)cbuff;
    unsigned char stepCount = p->MovePath[0] & 0x0F;
    if(stepCount <=15)
      {
	unsigned char dPosX = p->PosX;
	unsigned char dPosY= p->PosY;
	unsigned char HDirection = p->MovePath[0] >>4;
	short dStepDirection =0;
	if(stepCount >0)
	  {
	    stepCount++;
	  };
	for (int i =1 ; i < stepCount; i++)
	  {
	    if ((i & 1) == 1 )
	      {
		dStepDirection = p->MovePath[(i+1)>>1]>>4;
	      }
	    else
	      {
		dStepDirection = p->MovePath[(i+1)>>1] & 0x0F;
	      };
	    dPosX += stepDirections[dStepDirection <<1];
	    dPosY += stepDirections[(dStepDirection << 1)+1];
	  };
	activeChar->setPosXY(p->PosX,p->PosY);
	activeChar->MoveTo(dPosX,dPosY);
      } else
      {
	std::cout << "Wrong Number of steps !!! \n" ;
      };

    //TODO napisac wkonc odczytywanie AKTUALNYCH wsp z paczki
    //newx=
    //newy=
     


    //  		std::cout << "--------------------character movr-----------------\n";
   
    //		cout <<"poieram aktywna postac\n";
    if(!activeChar)cout <<"nie mam aktywnego chara\n";
    unsigned char mapCode = activeChar->getPosMapNb();
    //MuMaps::getInstance()->getMap(mapCode)->updatePortView(activeChar->getViewPort());
    activeChar->getViewPort()->printMe();
    //    activeChar->StatsCurentHpMpSt();
    
    //		cout <<"utawiam nowe wsp\n";
    //teraz powinnysmy je wyslac do odpowiedniego miejsca
    //wyslac spreparowaa paczke do klijentow widzacych mnie
    // std::vector<MuObiect*> known=_cl->getActiveCharacter()->getKnowsObiects();
    //std::vector<MuObiect*> toDelte;
    //		cout << "pobieram postacie na okolo wdystansie 20kr\n";
    //int toe=0;
    //int toa=0;
    //	  	std::cout <<"		ZNANYCH   :" <<known.size()  << "\n";
    //if(!known.empty())
    //  for (int i = 0; i < known.size(); i++)
    //	{
    //	  MuObiect* obj=known[i];
	  //	  		std::cout << "O:" << obj->getOId() << "-D> "<<distance(obj,activeChar)<<"\n";
    //	  if(distance(obj,activeChar)>100)
    //    {
    //      toe++;
    //	      toDelte.push_back(obj);
    //	    }
    //	};
	  
    //if(!toDelte.empty())
    // for (int i = 0; i < toDelte.size(); i++)
    //	{
    //	  activeChar->removeKnownObiect(toDelte[i]);
    //	  toDelte[i]->removeKnownObiect(activeChar);
    //	  activeChar->Send(
    //	};
    //			std::cout <<"		USUNIETYCH:" << toe << "\n";
    //teraz sprawdzamy kto wszedl nowy w widocznuy teren
    //std::vector<MuObiect*> visible = 
    // _cl->getActiveCharacter()->getM()->getVisibleObjects(activeChar, 10);
		
    //if(!visible.empty())
    // {
    //	vector<MuObiect *> newNPC;
    //	vector<MuObiect *> newPC;
    //	vector<MuObiect *> newItem;
    //	for (int i = 0; i < visible.size(); i++)
    //	  {
    //	    if (! activeChar->searchID(visible[i]->getOId()))
    //	      {
    //		toa++;
    //		switch(visible[i]->getMType())
    //		  {
    //		  case 1:newPC.push_back(visible[i]);break;
    //		  case 4:newNPC.push_back(visible[i]);break;
    //		  case 5:newItem.push_back(visible[i]);break;
    //		  default:std::cout << "Nieznany miting";break;
    //		  };
    //		activeChar->addKnownObiect(visible[i]);
    //		visible[i]->addKnownObiect(activeChar);
    //	      }
    //	  }
    //	if(!newNPC.empty())
    //	  {
	//    SNpcMiting * npc=new SNpcMiting(newNPC); // twoze paczke z nowymi Npc
    //	    activeChar->Send(npc);
    //	    delete npc;
    //	  };
    //	if(!newPC.empty())
    //	  {
    //	    SCharacterMiting * pc=new SCharacterMiting(newPC); // twoze paczke z nowymi Npc
    //	    activeChar->Send(pc);
    //	    delete pc;
    //	  };
    //	if(!newItem.empty())
	//  {
    //	    //std::cout << newItem.size();
    //	    SItemMiting * it=new SItemMiting(newItem); // twoze paczke z nowymi Npc
    //	    activeChar->Send(it);
    //	    delete it;
    //	  };
    //     };
    //			std::cout <<"		DODANYCH   :" << toa << "\n";
	  		
  };
	
	
  int distance(MuObiect *a, MuObiect *b)
  {
    int dX = a->getPosX() - b->getPosX();
    int dY = a->getPosY() - b->getPosY();
    return ( dX*dX + dY*dY );
  }
};

#endif /*CCHARACTERMOVE_*/
