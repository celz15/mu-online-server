#ifndef CATACKID_H_
#define CATACKID_H_
#include "Protocol/CBPacket.h"
#include "MuObiects/MuMonsterInstance.h"
#include "MuObiects/MuObjectsPool.h"
#include "Protocol/BaseStruct.h"
//c1 07 d9 00 02 78 05
struct UserAttackId
{
PMSG_HEADA _head;
  unsigned char attackOnIdHi;
  unsigned char attackOnIdLo;
  unsigned char unk;
  unsigned char direction;
};

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
    unsigned short idWhoAttack = _cl->getConnectID();
    long exp=0;
    unsigned char * cbuff= buff->getPointer();
    UserAttackId *p=(UserAttackId*)cbuff;
    unsigned char fixIdHi = p->attackOnIdHi|0x80;
    id=MAKEWORD(p->attackOnIdLo,fixIdHi);
    d=p->direction;
    printf ("ATTACK ON ID [%d] from direction [%d]\n",id,d);
    MuObiect * o = ObiectPool::getInstance()->getObject(id);
    if (o== NULL)
      {
	printf("ERROR Obiect [%d] Not exist\n",id);
      }
    else if(o->getType()==O_Mob)
      {
	MuMonsterInstance *c=static_cast<MuMonsterInstance*> (o);
	int dmg=_cl->getActiveCharacter()->getRealDmg();
	c->orbinateDmg(idWhoAttack,dmg);
      };
  };
};
#endif /*CATACKID_H_*/
