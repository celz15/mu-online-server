#ifndef MUCHARACTER_H_
#define MUCHARACTER_H_
#include <string>
#include "MuObiects/MuObiect.h"
#include "MuObiects/MuCharacterBase.h"
#include "Task/Task.h"
#include "Protocol/SBPacket.h"
#include "Protocol/SIdDie.h"
#include "Protocol/SToMoveID.h"
#include "Protocol/SIdGetDmg.h"
#include "Protocol/SChangeDirectionOrStatus.h"

class MuCharacter;			//dla senda'package

class TaskHeal:public Job{
  MuCharacter * me;
public:
  TaskHeal(MuCharacter * m)
  {
    opis="Uzupelnianie zycia";
    me=m;
  };
  virtual ~TaskHeal(){}
  virtual void Run();
};


class MuCharacter : public MuObiect , public MuCharacterBase
{
  TaskHeal *_HealT;  		//uzupelnianie zycia
  
  //informacje podstawowe
  int _new_x;					//nowe wsp; // podczas poruszcania
  int _new_y;
  
  //zycie i inne
  int _maxBaseHP;
  int _curentHP;
  int _hpStep;				//krok uzupelniania zycia:co ile
  bool _hpTaskRun;			//czy jest uruchomiony hpTask
  //GObj data
  short GObjLvl;
  int GObjMaxLive;
  int GObjMaxMana;
  int GObjMaxStam;
  int GObjMagicDevense;
  int GObjAttackSuccesRate;
  int GObjDevenseSuccesRate;
  int GObjAttackRange;
  int GObjMoveSpeed;
  int GObjWindResist;
  int GObjPoisonResist;
  int GObjIceResist;
  int GObjElectricResist;
  int GObjFireResist;
 
  MuObiect * _target;
  
  
 public:
  void _dmg(int i)			//dotalem dmg prywatna poniewaz tu tulko odejmuje hp
    {
      std::cout << "id: "<< getOId()<<" orb dmg :"<<i<<" curhp="<<_curentHP<<".\n";
      _curentHP-=i;
    };
protected:
  MuCharacter(){
    _HealT=new TaskHeal(this);
    _new_x=getX();
    _new_y=getY();
    _curentHP=_maxBaseHP;	//uleczony
    _hpStep=1;				//uzupelnianie zycia
  };
  public:
  short getLvl()
    {
      return GObjLvl;
    }
  int getMaxLive()
    {
      return GObjMaxLive;
    }
  int GetMaxMana()
    {
      return GObjMaxMana;
    }
  int getMaxStamin()
    {
      return GObjMaxStam;
    }
  int GetMagicDevense()
    {
      return GObjMagicDevense;
    }
  int getAttackSuccesRate()
    {
      return GObjAttackSuccesRate;
    }
  int getDevenseSuccesRate()
    {
      return GObjDevenseSuccesRate;
    }
  int getAttackRange()
    {
      return GObjAttackRange;
    }
  int getMoveSpeed()
    {
      return GObjMoveSpeed;
    }
  int getWindResist()
    {
      return GObjWindResist;
    }
  int getPoisonResist()    {      return GObjPoisonResist;    }
  int getIceResist()    {      return GObjIceResist;    }
  int getElectricResist()    {      return GObjElectricResist;    }
  int getFireResist()    {      return GObjFireResist;    }
  void setLvl(short lvl)    {      GObjLvl=lvl;    }
  void setMaxLive(int maxLive)    {      GObjMaxLive=maxLive;    }
  void setMaxMana(int maxMana)    {      GObjMaxMana=maxMana;    }
  void setMaxStamin(int maxStamin){GObjMaxStam=maxStamin;}
  void SetMaxBodyStats(int maxLive,int maxMana, int maxStamin)
    {
      setMaxLive(maxLive);
      setMaxMana(maxMana);
      setMaxStamin(maxStamin);
    }
  void setAttackSuccesRate(int attackSuccesRate){GObjAttackSuccesRate=attackSuccesRate;}
  void setAttackRange(int attackrange){GObjAttackRange=attackrange;}
  void setMoveSpeed(int moveSpeed){GObjMoveSpeed=moveSpeed;}
  void setWindResist(int windResist){GObjWindResist=windResist;}
  void setPoisonResist(int poisonResist){GObjPoisonResist=poisonResist;}
  void setIceResist(int iceResist){GObjIceResist=iceResist;}
  void setElectrictResist(int electrictResist){GObjElectricResist=electrictResist;}
  void setFireResist(int fireResist){GObjFireResist=fireResist;}  
  //resists all togethjer
virtual ~MuCharacter(){};
  
  
  int getMaxBaseHP()
    {return _maxBaseHP;};
  int getCurentHP(){return _curentHP;};
  void setMaxBaseHP(int hp)
    {_maxBaseHP=hp;};
  void setCurentHP(int c){_curentHP=c;};
  
  void broadcastPacket(SBPacket *p);
  
  void MoveTo(int x,int y)
    {
      std::cout 	<< "przesuwam :["
			<< getOId()<<"] z ["
			<< (int)getX()<<","
			<<(int)getY() <<"] na ["
			<<x<<","<<y<<"]\n";
      this->setX(_new_x);		//stare staja sie aktualnymi
      this->setY(_new_y);		//-||-
      _new_x=x;				//ustawiamy nowe
      _new_y=y;				//-||-
      
      
      IMove();				//posylamy do wsysykich ktoeych znamy ze sie ruszany
    }
  
  MuObiect* getTarget()
    {return _target;};
  void setTarget(MuObiect* t)
    {_target=t;};
  bool isTarget()
    {return (_target!=NULL);};
  bool isDead()
    {return (_curentHP<=0);};
  void setNX(int x){_new_x=x;};
  void setNY(int y){_new_y=y;};
  //dmg
  //	 virtual void orbinateDmg(int i)
  //	{
  //		_dmg(i); // dostalem dmg
  //		IGetDmg(i,1);
  //		if(isDead())IDie();//jesli jestem martwy wtedy wysylam ze niezyje
  //	};
  
  //protokul
  void IDie()
    {
      SIdDie * pack=new SIdDie(getOId());
      broadcastPacket(pack);
      //removeKnownObiect(this);
      delete pack;	
      
    };
  void IMove()
    {
      SToMoveID *pack=new SToMoveID(getOId(),_new_x,_new_y,0);
      broadcastPacket(pack);
      delete pack;
    }
  
  void IGetDmg(int h,int f)
    {
      SIdGetDmg * pack=new SIdGetDmg(getOId(),h,f);
      broadcastPacket(pack);
      delete pack;		
    };	
  
  void IChangeMyStatusOrDirection()
    {
      SChangeDirectionOrStatus * n=new SChangeDirectionOrStatus(getF(),getD());
      broadcastPacket(n);	
      delete n;
    };
  
  //heal
  bool HealReq()
    {
      _hpTaskRun=(_curentHP<_maxBaseHP);
      return _hpTaskRun;};
  
  
  void RestartHP(){_curentHP=_maxBaseHP;};
  
  void HpReg()
    {
      if(HealReq()) // jesli wymagamy leczenia 
	{
	  _curentHP+=_hpStep; // dodajemy
	  if(_curentHP>_maxBaseHP)_curentHP=_maxBaseHP; // jesli przekracamy max usatwaimy max
	  
	};
    };
  
  int getNewX(){return _new_x;};
  int getNewY(){return _new_y;};
  
  void _bTask()
    {
      if(HealReq()) 
	Task::Instance()->AddJobA(_HealT,10); 	
    }
  
  virtual void CheckStatus()
    {
      //sprawdzamy zycie:
      if(HealReq())_bTask();	//todo zmienic nazwe na bardzie pasujaca
    };	
};

#endif /*MUCHARACTER_H_*/
