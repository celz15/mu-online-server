#ifndef SNPCMITING_H_
#define SNPCMITING_H_
#include "Protocol/SBPacket.h"
#include "MuObiects/MuNpcInstance.h"
#include "BaseStruct.h"
//clasa : SNpcMiting
//h    -paczka budowana

struct NPCMittingSub{
  unsigned char m_uIndexHi;
  unsigned char m_uIndexLo;
  unsigned char m_uClassHi;
  unsigned char m_uClassLo;
  unsigned char m_uUnk1;
  unsigned char m_uUnk2;
  unsigned char m_uPosX;
  unsigned char m_uPosY;
  unsigned char m_uDestX;
  unsigned char m_uDestY;
  unsigned char m_uLookDirection;
  unsigned char m_uPath;
  void set(unsigned short index, unsigned short _class , unsigned char posx , unsigned char posy , 
			unsigned char posdx,unsigned char posdy,unsigned char ld,unsigned char path)
  {
	m_uIndexHi=HIBYTE(index);
	m_uIndexLo=LOBYTE(index);
	m_uClassHi=HIBYTE(_class);
	m_uClassLo=LOBYTE(_class);
	m_uUnk1=0x00;
	m_uUnk2=0x00;
	m_uPosX=posx;
	m_uPosY=posy;
	m_uDestX=posdx;
	m_uDestY=posdy;
	m_uLookDirection=ld;
	m_uPath=path;
  };
};

struct NPCMitting{
  PMSG_HEADB m_Head;
  unsigned char m_uCount;
  NPCMittingSub m_Npc[75];
};

class SNpcMiting : public CSPacket
{
  vector<unsigned short > newList;
  int off;
 public:
 SNpcMiting():CSPacket()
    {
       MyName="13	NPC Mitting";
    };
  ~SNpcMiting(){};
  void addToPack(unsigned short id)
  {
    newList.push_back(id);
  } 

 HexBuff * build()
  {
    int size = 5+newList.size()*sizeof(NPCMittingSub);

    NPCMitting package;

    package.m_Head.set(0xc2,size,0x13);
    HeadSetB(&package.m_Head,0xc2,size,0x13);
    printf("create Package NPC MITTING\n");
    for(int i = 0 ; i <newList.size();i++)
      {
	MuNpcInstance *npc= static_cast<MuNpcInstance *> (ObiectPool::getInstance()->getObject(newList[i]));
	if(npc!=NULL)
							 
	{
	  package.m_Npc[i].set(npc->getIndex(),npc->getObjId(),npc->getPosX(),npc->getPosY(),npc->getPosOldX(),npc->getPosOldY(),10,0);
	  printf ("add[%d]: id(%d)[%d,%d] , class(%d)[%d,%d],pos[%d,%d]->[%d,%d]\n",i,npc->getIndex(),LOBYTE(npc->getIndex()),HIBYTE(npc->getIndex()),
		  npc->getObjId(),LOBYTE(npc->getObjId()),HIBYTE(npc->getObjId()),
		  npc->getPosX(),npc->getPosY(),npc->getPosOldX(),npc->getPosOldY());
	}
      };
    printf("done Create Package NPCMITTING\n");
    package.m_uCount=newList.size();
    //cast structure to unsigned char pointer:>
    unsigned char * pacbuf;
    pacbuf=reinterpret_cast<unsigned char*>(&package);
    (*h)[0].writeAC(pacbuf,size);
    return h;
  };
};


#endif /*SNPCMITING_H_*/
