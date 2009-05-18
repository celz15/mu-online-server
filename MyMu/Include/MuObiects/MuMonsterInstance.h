#ifndef MUMONSTERINSTANCE_H_
#define MUMONSTERINSTANCE_H_
#include "MuNpcTemplate.h"
#include "MuObjectsPool.h"
#include "MuAtackableInstance.h"
#include "MuMap.h"
#include "MuItemInstance.h"
#include "Protocol/SForgetId.h"
#include "Protocol/SIdDie.h"
#include "Protocol/SIdAtackId.h"
#include "Task/Task.h"
#include "IdFactory.h"


class MuMonsterInstance:public MuAtackableInstance
{
  friend class ObiectPool;
  int GObjAttackType;
  int GObjMoveRange;
  int GObjItemDropRate;
  int GObjMaxItemDropLvl;
  int GObjMonyDropRate;

 
  bool movable;						//czy sie rusza
 
 
 
 
  
  long gexp;							//ile dostanie expa jak ktos mnie zabije
public:
  void setAttackData(int attackType,int attackRange)
  {
 
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
  MuMonsterInstance(MuNpcTemplate t, int posx,int posy, unsigned char map_code,unsigned short id)
  {
    setIndex(id);
    setObjId(t.n_Class);
    setName(t.n_Name);
    setType(O_Mob);
    setPosMapNb(map_code);
    setPosXY(posx,posy);
    setPosHead(1);
    setPosNewXY(posx,posy);
    setPortView(new MuViewPortSet(id,t.n_ViewRange));
    gexp = 1500;		
    setStatMaxHpMpSt(t.n_StatMaxHp,t.n_StatMaxMp,0);
    setStatDHpMpSt(t.n_StatMaxHp/t.n_RegerenTime,t.n_StatMaxMp/t.n_RegerenTime,0);
    PrintMe();
    setStatsCurToMax();
    PrintStat();
  };
  
public:
  long getExp(){return gexp;};
  ~MuMonsterInstance(){}

};
//klasy taska

#endif /*MUMONSTERINSTANCE_H_*/
