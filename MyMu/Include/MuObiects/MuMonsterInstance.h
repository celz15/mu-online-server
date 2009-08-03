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
class MuMonsterAiData
{
public:
	enum
	{
		AiNothing = 0,
		//move
		AiGoto = 1,
		AiTurn = 2,
		//respown
		AiRespown = 3
	};
	//move data
	unsigned char _Pos_destX;
	unsigned char _Pos_destY;
	unsigned char _Pos_destH;
	//skills
	unsigned char _Skill_id; //run skill id on pos or id
	//target
	unsigned short _Target_id; // target
	//Ai task
	unsigned char _aiTask;
	unsigned long _time; // time when use data to make AiJob


	unsigned long getTime()
	{
		return _time;
	}
	void runInNextXMSec(unsigned long sec)
	{
		_time = time(0) + sec;
	}
	bool runTime()
	{
		if (time(0) >= _time)
			return true;
		else
			return false;
	}

};

class MuMonsterInstance: public MuAtackableInstance
{
	friend class ObiectPool;
	MuMonsterAiData * _actualIaData; //if null then not set yet
	int GObjAttackType;
	unsigned char GobjAttackRange;
	int GObjMoveRange;
	int GObjItemDropRate;
	int GObjMaxItemDropLvl;
	int GObjMonyDropRate;
	unsigned long ai_Time;

	bool movable; //czy sie rusza


	long gexp; //ile dostanie expa jak ktos mnie zabije
public:
	void setAttackData(int attackType, int attackRange)
	{

	}
	int getAttackType()
	{
		return GObjAttackType;
	}

	void setAttackType(int AttackType)
	{
		GObjAttackType = AttackType;
	}
	int getMoveRange()
	{
		return GObjMoveRange;
	}
	void setMoveRange(int MoveRange)
	{
		GObjMoveRange = MoveRange;
	}
	int getItemDropRate()
	{
		return GObjItemDropRate;
	}
	void setItemDropRate(int ItemDropRate)
	{
		GObjItemDropRate = ItemDropRate;
	}
	int getMaxItemDropLvl()
	{
		return GObjMaxItemDropLvl;
	}

	void setDropRates(int MonyDropRate, int ItemDropRate, int ItemMaxDropLvl)
	{
		setMonyDropRate(MonyDropRate);
		setItemDropRate(ItemDropRate);
		setMaxItemDropLvl(ItemMaxDropLvl);
	}
	void setMaxItemDropLvl(int MaxItemDropLvl)
	{
		GObjMaxItemDropLvl = MaxItemDropLvl;
	}
	int getMonyDropRate()
	{
		return GObjMonyDropRate;
	}

	void setMonyDropRate(int MonyDropRate)
	{
		GObjMonyDropRate = MonyDropRate;
	}

protected:
	MuMonsterInstance(MuNpcTemplate t, int posx, int posy,
			unsigned char map_code, unsigned short id)
	{
		setIndex(id);
		setObjId(t.n_Class);
		setName(t.n_Name);
		setPosMapNb(map_code);
		setPosXY(posx, posy);
		setPosHead(1);
		setPosNewXY(posx, posy);
		setPortView(new MuViewPortSet(id, t.n_ViewRange));
		gexp = 1500;
		setStatMaxHpMpSt(t.n_StatMaxHp, t.n_StatMaxMp, 0);
		setStatDHpMpSt(t.n_StatMaxHp / t.n_RegerenTime, t.n_StatMaxMp
				/ t.n_RegerenTime, 0);
		PrintMe();
		setStatsCurToMax();
		PrintStat();
	}

public:
	long getExp()
	{
		return gexp;
	}

	~MuMonsterInstance()
	{
	}

	//AI Methods
	void Move()
	{
		unsigned char range = getMoveRange();
	}
	//return Ai data
	MuMonsterAiData * getAiData()
	{
		return _actualIaData;
	}
	//set ai data
	void setAiData(MuMonsterAiData * data)
	{
		_actualIaData = data;
	}
	unsigned char getAttackRange()
	{
		return 1;//(TODO) set stats
		return GobjAttackRange;
	}
};
//klasy taska

#endif /*MUMONSTERINSTANCE_H_*/
