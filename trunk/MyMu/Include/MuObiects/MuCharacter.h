#ifndef MUCHARACTER_H_
#define MUCHARACTER_H_
#include <string>

//OBIECTS
#include "MuObiects/MuObiect.h"
#include "MuObiects/MuCharacterBase.h"
#include "MuObiects/MuMaps.h"

//PROTOCOL
#include "Protocol/SBPacket.h"
#include "Protocol/SIdDie.h"
#include "Protocol/SToMoveID.h"
#include "Protocol/SIdGetDmg.h"
#include "Protocol/SChangeDirectionOrStatus.h"

class MuCharacter: public MuObiect
{
	//------------------POSITION----------------------
	unsigned char o_PosOldX; //old x position
	unsigned char o_PosOldY; //old y position
	//-------------------lvl-------------------------
	unsigned short o_Lvl; //level of character
	//------------------Stats Maximals----------------
	int o_StatMaxHp; //max hp
	int o_StatMaxMp; //max mp
	int o_StatMaxSt; //max st
	//------------------Stats Curents-----------------
	int o_StatCurHp;
	int o_StatCurMp;
	int o_StatCurSt;
	//------------------stats timers------------------
	unsigned long o_StatTimeHp;
	unsigned long o_StatTimeMp;
	unsigned long o_StatTimeSt;
	//------------------stats DeltaTime---------------
	float o_StatDHp;
	float o_StatDMp;
	float o_StatDSt;
	//------------------stats resistants--------------
	int o_MagicDevense;
	int o_AttackSuccesRate;
	int o_DevenseSuccesRate;
	int o_AttackRange;
	int o_MoveSpeed;
	int o_WindResist;
	int o_PoisonResist;
	int o_IceResist;
	int o_ElectricResist;
	int o_FireResist;
	//-----------------------------------actual target ?? -----
	MuObiect * _target;
public:
	//------------------------------------Get/Set--------------
	//position
	void setPosNewX(unsigned char x)
	{
		o_PosOldX = getPosX();
		setPosX(x);
	}
	void setPosNewY(unsigned char y)
	{
		o_PosOldY = getPosY();
		setPosY(y);
	}
	unsigned char getPosNewX()
	{
		return getPosX();
	}

	unsigned char getPosNewY()
	{
		return getPosX();
	}

	void setPosNewXY(unsigned char x, unsigned char y)
	{
		setPosNewX(x);
		setPosNewY(y);
	}
	/*
	 * `@return From X Position move
	 */
	unsigned char getPosOldX();
	/*
	 * 	@return From Y Position move
	 */
	unsigned char getPosOldY()
	{
		return o_PosOldY;
	}

	//lvl
	unsigned short getLvl()
	{
		return o_Lvl;
	}

	void setLvl(unsigned short lvl)
	{
		o_Lvl = lvl;
	}

	//stats maximals
	int getStatMaxHp()
	{
		return o_StatMaxHp;
	}
	int getStatMaxMp()
	{
		return o_StatMaxMp;
	}
	int getStatMaxSt()
	{
		return o_StatMaxSt;
	}
	void setStatMaxHp(int max)
	{
		o_StatMaxHp = max;
	}
	void setStatMaxMp(int max)
	{
		o_StatMaxMp = max;
	}
	void setStatMaxSt(int max)
	{
		o_StatMaxSt = max;
	}
	void setStatCurHpMpSt(unsigned short hp, unsigned short mp,
			unsigned short st)
	{
		if (hp != 0)
			o_StatCurHp = hp;
		else
			o_StatCurHp = o_StatMaxHp;
		if (mp != 0)
			o_StatCurMp = mp;
		else
			o_StatCurMp = o_StatMaxMp;
		if (st != 0)
			o_StatCurSt = st;
		else
			o_StatCurSt = o_StatMaxSt;
	}

	void setStatMaxHpMpSt(int hp, int mp, int st)
	{
		setStatMaxHp(hp);
		setStatMaxMp(mp);
		setStatMaxSt(st);
	}

	void setStatDHpMpSt(float hp, float mp, float st)
	{
		o_StatDHp = hp;
		o_StatDMp = mp;
		o_StatDSt = st;
	}
	//stats Curent
	void setStatsCurToMax()
	{
		unsigned long t = time(0);
		o_StatCurHp = o_StatMaxHp;
		o_StatCurMp = o_StatMaxMp;
		o_StatCurSt = o_StatMaxSt;
		o_StatTimeHp = o_StatTimeMp = o_StatTimeSt = t;
	}

	void actualizeHp()
	{
		unsigned long t = time(0);
		if (o_StatMaxHp != o_StatCurHp)
		{
			int dt = (int) ((t - o_StatTimeHp) * o_StatDHp);
			o_StatCurHp += dt;
			if (o_StatCurHp > o_StatMaxHp)
				o_StatCurHp = o_StatMaxHp;
		};
		o_StatTimeHp = t;
	}


	void actualizeMp()
	{
		unsigned long t = time(0);
		if (o_StatMaxMp != o_StatCurMp)
		{
			int dt = (int) ((t - o_StatTimeMp) * o_StatDMp);
			o_StatCurMp += dt;
			if (o_StatCurMp > o_StatMaxMp)
				o_StatCurMp = o_StatMaxMp;
		};
		o_StatTimeMp = t;
	}


	void actualizeSt()
	{
		unsigned long t = time(0);
		if (o_StatCurSt != o_StatMaxSt)
		{
			int dt = (int) ((t - o_StatTimeSt) * o_StatDSt);
			o_StatCurSt += dt;
			if (o_StatCurSt > o_StatMaxSt)
				o_StatCurSt = o_StatMaxSt;
		};
		o_StatTimeSt = t;
	}

	void StatsCurentHpMpSt()
	{
		getStatCurHp();
		getStatCurMp();
		getStatCurSt();
		PrintStat();
	}

	//gets curents
	int getStatCurHp()
	{
		actualizeHp();
		return o_StatCurHp;
	}

	int getStatCurMp()
	{
		actualizeMp();
		return o_StatCurMp;
	}

	int getStatCurSt()
	{
		actualizeSt();
		return o_StatCurSt;
	}

	//-------------------dumps -----------------------
	void printHp()
	{
		printf("HP[Curent:%d,Max:%d,Step:%f,Last Check:%d]\n", o_StatCurHp,
				o_StatMaxHp, o_StatDHp, o_StatTimeHp);
	}
	;
	void printMp()
	{
		printf("MP[Curent:%d,Max:%d,Step:%f,Last Check:%d]\n", o_StatCurMp,
				o_StatMaxMp, o_StatDMp, o_StatTimeMp);
	}
	;
	void printSt()
	{
		printf("ST[Curent:%d,Max:%d,Step:%f,Last Check:%d]\n", o_StatCurSt,
				o_StatMaxSt, o_StatDSt, o_StatTimeSt);
	}

	void PrintStat()
	{
#ifdef WIN32
		printf("States for Object[index:%d] at time [%d]\n", getIndex(),
				time(0));
#else
		printf ("States for Object[index:%d] at time [%d]\n",getIndex(),_time(0));
#endif
		printHp();
		printMp();
		printSt();
	}
	;

	void _dmg(int i) //dotalem dmg prywatna poniewaz tu tulko odejmuje hp
	{
		getStatCurHp();
		o_StatCurHp -= i;
		printHp();
	}
	;
protected:

	MuCharacter()
	{
	}
	;
public:
	//void setFireResist(int fireResist){GObjFireResist=fireResist;}
	//resists all together
	virtual ~MuCharacter()
	{
	}


	void broadcastPacket(SBPacket *p);

	void MoveTo(int x, int y)
	{
		printf("Object[Index:%d] move form[x:%d,y:%d] to [x:%d,y:%d] \n",
				getIndex(), getPosOldX(), getPosOldY(), getPosX(), getPosY());
		setPosNewXY(x, y);
		CheckViewPort();
		IMove();
	}

	MuObiect* getTarget()
	{
		return _target;
	}

	void setTarget(MuObiect* t)
	{

		_target = t;
	}

	bool isTarget()
	{
		return (_target != NULL);
	}

	bool isDead()
	{
		return (getStatCurHp() <= 0);
	}

	virtual void orbinateDmg(unsigned short idfrom, int i)
	{
		_dmg(i); // i'm get damage //TODO
		IGetDmg(i, 1);

		if (isDead())
			IDie();//if i'm death then send to all pc instances package
	}

	//viewport
	virtual void CheckViewPort();
	virtual void CheckToForgetInViewPort()
	{
		MuViewPortSet *t = getViewPort();
		for (int i = 0; i < t->getViewSize(); i++)
			if (t->getViewPort(i)->c_State == MuViewPort::S_ToForget)
				t->getViewPort(i)->c_State = MuViewPort::S_Empty;
		t->opymalize();
	}

	virtual void checkNewInViewPort()
	{
		MuViewPortSet *t = getViewPort();
		for (int i = 0; i <= t->getViewSize(); i++)
			if (t->getViewPort(i)->c_State == MuViewPort::S_New)
				t->getViewPort(i)->c_State = MuViewPort::S_Known;
	}

	//protokul
	void IDie();

	void IMove()
	{

		SToMoveID *pack = new SToMoveID(getIndex(), getPosNewX(), getPosNewY(),
				0);
		broadcastPacket(pack);
		delete pack;
	}

	void IGetDmg(int h, int f)
	{
		SIdGetDmg * pack = new SIdGetDmg(getIndex(), h, f);
		broadcastPacket(pack);
		delete pack;
	}

	void IChangeMyStatusOrDirection()
	{
		SChangeDirectionOrStatus * n = new SChangeDirectionOrStatus(
				getPosHead(), getPosStatus());
		broadcastPacket(n);
		delete n;
	}

	//protocol dla pcinstance

	virtual void IUpdateMaxMpSt()
	{
	}

	virtual void IUpdateMaxHp()
	{
	}

	virtual void IUpdateCurMpSp()
	{
	}

	virtual void IUpdateCurHp()
	{
	}

};

#endif /*MUCHARACTER_H_*/
