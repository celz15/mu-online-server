#ifndef MUMONSTERINSTANCE_H_
#define MUMONSTERINSTANCE_H_
#include "MuObjectsPool.h"
#include "MuAtackableInstance.h"
#include "MuMap.h"
#include "MuItemInstance.h"
#include "Protocol/SForgetId.h"
#include "Protocol/SIdDie.h"
#include "Protocol/SIdAtackId.h"
#include "Task/Task.h"
#include "IdFactory.h"

class MuMonsterInstance;

class MobRespown:public Job
{
  MuMonsterInstance * me;
  int _x;
  int _y;
public:
  MobRespown(MuMonsterInstance* m)
  {
    opis="mob respown";
    me=m;
  };
  ~MobRespown(){}
  void Run();
  void setXY(int x,int y){
    _x=x;
    _y=y;
  }
	
};

class MobMove :public Job
{
  MuMonsterInstance * me;
  MuSpot* MySpot;
public:
  MobMove(MuMonsterInstance* m,MuSpot *ms)
  {
    opis="SIMOB: poruszanie";
    me=m;
    MySpot=ms;
  }
  ~MobMove()
  {
    std::cout << "mob move dies\n";
  }
  void Run();
};


class MobSI : public Job{
  MuMonsterInstance * me;
  MuSpot* MySpot;
  int myStatus; //status : 0 nic nie robie i sie lecze ,1 skanuje szukajac przeciwnika,2 chodze , 3 atakuje , 4 respownuje sie, 5 uciekam ?
public:
  MobSI(MuMonsterInstance *  m,MuSpot *ms)
  {
    opis="SIMOB: all";
    MySpot=ms;
    myStatus=1; // scan
    me=m;
  }

  ~MobSI(){}
  void Run();
  int RunScan(int r);
  int RunMove(int x,int y);
  int RunAutoMove();
  int RunHeal(int st);
  int RunRespown(int x,int y);
  int RunAtack(int idcalu);
};
class ObiectPool;


class MuMonsterInstance:public MuAtackableInstance
{
  friend class ObiectPool;
  int GObjAttackType;
  int GObjMoveRange;
  int GObjItemDropRate;
  int GObjMaxItemDropLvl;
  int GObjMonyDropRate;

 
  bool movable;						//czy sie rusza
  bool atRespown;						//czy podczas respownu
  MobMove * _moveInst;				//task ruszania
  MobRespown *_resp;					//task respownu
  MobSI		*_si;					//inteligencja :P
  
  long gexp;							//ile dostanie expa jak ktos mnie zabije
public:
  void setAttackData(int attackType,int attackRange)
  {
    setAttackType(attackType);
    setAttackRange(attackRange);
  }
  int getAttackType()
  {
    return GObjAttackType;
  };
  void setAttackType(int AttackType)
  {
    GObjAttackType=AttackType;
  }
  int getMoveRange()
  {
    return GObjMoveRange;
  }
  void setMoveRange(int MoveRange)
  {
    GObjMoveRange=MoveRange;
  }
  int getItemDropRate()
  {
    return GObjItemDropRate;
  }
  void setItemDropRate(int ItemDropRate)
  {
    GObjItemDropRate=ItemDropRate;
  }
  int getMaxItemDropLvl()
  {
    return GObjMaxItemDropLvl;
  }

  void setDropRates(int MonyDropRate,int ItemDropRate,int ItemMaxDropLvl)
  {
    setMonyDropRate(MonyDropRate);
    setItemDropRate(ItemDropRate);
    setMaxItemDropLvl(ItemMaxDropLvl);
  }
  void setMaxItemDropLvl(int MaxItemDropLvl)
  {
    GObjMaxItemDropLvl=MaxItemDropLvl;
  }
  int getMonyDropRate()
  {
    return GObjMonyDropRate;
  }

  void setMonyDropRate(int MonyDropRate)
  {
    GObjMonyDropRate=MonyDropRate;
  }

protected:
  MuMonsterInstance(int x,int y,int r,MuMap *m,int nrsp)
  {
    gexp=1500;
    atRespown=false;
    //    setOId(IdFactory());

    setMaxBaseHP(20);
    setCurentHP(20);
    setX(x);
    setY(y);
    setNX(x);
    setNY(y);
    setMType(4);//monster
    setId(r);
    setM(m);
      
    movable=true;
    _moveInst = new MobMove(this,m->getSpot(nrsp));
    _resp=new MobRespown(this);
    //_si =new MobSI(this,m->getSpot(nrsp));    
    setMType(4);			//monster
  };
  
public:
  void orbinateDmg(int i)
  {
    if(isDead())
      {
	std::cout << "i die\n";
	IDie();//jesli jestem martwy wtedy wysylam ze niezyje
	setMovable(false);

	//MuItemInstance * ite1=	ObjPool->GetInstance()->newMuItemInstance();
	//ite1->setX(getX());
	//ite1->setY(getY());
	//ite1->setDur(10);
	//ite1->mItem(1,1,10,1,1);
	//getM()->storeNewObiect(ite1);
	if(!atRespown)
	  {
	    RunMobRespown();
	    atRespown=true;
	  };
      }
    else
      {
	_dmg(i); // dostalem dmg
	IGetDmg(i,1);
      };
  };
  
  long getExp(){return gexp;};
  void RunMobRespown()
  {
    movable=false;
    _resp->setXY(getX(),getY());
    //usatwiamy ws
    setX(0xff);
    setY(0xff);
    setNX(0xff);
    setNY(0xff);
    Task::Instance()->AddJobA(_resp,30); // resp po 30 sec
	
    //broadcastPacket(new SIdDie(getOId()));
    //broadcastPacket(new SForgetId(getOId()));
  }
  
  void RunMoveInst();
  void setAtRespown(bool t){atRespown=t;};
  ~MuMonsterInstance(){}
  
  void setMovable(bool t){
    movable=t;	
  };
  
  void Si(int t=10)
  {
    Task::Instance()->AddJobA(_si,t);
  };
  
  void IAtackU()
  {
    std::cout << "ATAKUJE ID: " << getTarget()->getOId() << "\n";
    IAtackId(getTarget()->getOId());
      
  };
  void IAtackId(int id)
  {
    IGetDmg(id,2);
  };
  


};
//klasy taska

#endif /*MUMONSTERINSTANCE_H_*/
