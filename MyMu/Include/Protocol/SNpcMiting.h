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
};

struct NPCMitting{
  PMSG_HEADB m_Head;
  unsigned char m_uCount;
  NPCMittingSub m_Npc[75];
};

class SNpcMiting : public CSPacket
{
  vector<MuObiect *> newList;
  int off;
 public:
  SNpcMiting(vector<MuObiect *> l):CSPacket()
    {
      newList=l;
      MyName="13	NPC Mitting";
    };
  ~SNpcMiting(){};
  HexBuff * build()
    {
      int size = 5+newList.size()*sizeof(NPCMittingSub);

      NPCMitting package;

      package.m_Head.set(0xc2,size,0x13);
      HeadSetB(&package.m_Head,0xc2,size,0x13);

      for(int i = 0 ; i <newList.size();i++)
	{
	  MuNpcInstance *npc= static_cast<MuNpcInstance *> (newList[i]); 
	  {
	  package.m_Npc[i].m_uIndexHi=HIBYTE(npc->getId());
	  package.m_Npc[i].m_uIndexLo=LOBYTE(npc->getId());
	  package.m_Npc[i].m_uClassHi=HIBYTE(npc->getOId());
	  package.m_Npc[i].m_uUnk1=0;
	  package.m_Npc[i].m_uUnk2=0;
	  package.m_Npc[1].m_uClassLo=LOBYTE(npc->getOId());
	  package.m_Npc[i].m_uPosX=npc->getNewX();
	  package.m_Npc[i].m_uPosY=npc->getNewY();
	  package.m_Npc[i].m_uDestX=npc->getX();
	  package.m_Npc[i].m_uDestY=npc->getY();
	  package.m_Npc[i].m_uLookDirection=10; //TODO !!!
	  package.m_Npc[i].m_uPath=0;//TODO!!
	  }
	};
      package.m_uCount=newList.size();
      //cast structure to unsigned char pointer:>
      unsigned char * pacbuf;
      pacbuf=reinterpret_cast<unsigned char*>(&package);
      (*h)[0].writeAC(pacbuf,size);
      return h;
    };
};


#endif /*SNPCMITING_H_*/
