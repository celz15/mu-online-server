#ifndef SSELECTEDCHARACTERSTATS_H_
#define SSELECTEDCHARACTERSTATS_H_
#include "Protocol/SBPacket.h"
#include "Protocol/BaseStruct.h"


struct CharacterInfo
{
  PMSG_HEADA m_Head;
  unsigned char SubType;
  unsigned char PosX;
  unsigned char PosY;
  unsigned char MapID;
  unsigned char Dir;
  unsigned long exp;
  unsigned long nextExp;
  unsigned short lvlUpPoints;
  unsigned short str;
  unsigned short agl;
  unsigned short vit;
  unsigned short enr;
  unsigned short hp;
  unsigned short maxHp;
  unsigned short mp;
  unsigned short maxMp;
  unsigned short st;
  unsigned short maxSt;
  unsigned long mony;
  unsigned char pkLvl;
  unsigned char ctrCode;
  unsigned short addPoints;
  unsigned short maxAddPoints;
  unsigned short leaderShip;
};




//clasa : SSelectedharacterStats
//h    -paczka budowana
class SSelectedharacterStats : public CSPacket
{
  CharacterInfo p;
public:
  SSelectedharacterStats()
  {
p.m_Head.set(0xc3,sizeof(CharacterInfo),0xf3);
    p.SubType=0x03;
    MyName="F303 Selcted Character Stats";
  }
  SSelectedharacterStats(
			 unsigned char x,unsigned char y,unsigned char m,unsigned char dir,	// pozycja
			 unsigned long exp,unsigned long lexp,unsigned short lp, 	//exp i punkty do rozdania
			 unsigned short s,unsigned short a,unsigned short v,unsigned short e,						//statystyki
			 unsigned short hp,unsigned short mhp,
			 unsigned short mp,unsigned short mmp,
			 unsigned short st,unsigned short mst,		//zycie mana stamina
			 unsigned long zen,								//zeny
			 unsigned char pk,unsigned char ctrcode,
			 unsigned short addp,unsigned short maddp									// lir spare
							
			 
			 ):CSPacket()
  {
  
    
p.m_Head.set(0xc3,sizeof(CharacterInfo),0xf3);
    p.SubType=0x03;
    p.PosX=x;    p.PosY=y;    p.MapID=m;    p.Dir=dir;
    p.exp=exp;    p.nextExp=lexp;    p.lvlUpPoints=lp;
    p.str=s;    p.agl=a;    p.vit=v;    p.enr=e;    
    p.hp=hp;    p.maxHp=mhp;
    p.mp=mp;    p.maxMp=mmp;
    p.st=st;    p.maxSt=mst;
    p.mony=zen;
    p.pkLvl=pk;    p.ctrCode=ctrcode;
    p.addPoints=addp;p.maxAddPoints=maddp;
    MyName="F303 Selcted Character Stats";
  };
  ~SSelectedharacterStats(){};
  void setAddPoints(unsigned short addp, unsigned short maddp)
  {
    p.addPoints=addp;p.maxAddPoints=maddp;
  };
  void setPkLvl(unsigned char pk,unsigned short ctrcode)
  {
    p.pkLvl=pk;    p.ctrCode=ctrcode;
  }
  void setPos(unsigned char x, unsigned char y , unsigned char map , unsigned char dir)
  {
    p.PosX=x;    p.PosY=y;    p.MapID=map;    p.Dir=dir;
  };
  void setZen(unsigned long zen)
  {
    p.mony=zen;
  }
  void setExp(unsigned long exp, unsigned long lexp,unsigned short lp)
  {
    p.exp=exp;    p.nextExp=lexp;    p.lvlUpPoints=lp;
  };

  void setMaxHpMpSt(unsigned short hp,unsigned short mhp,
		    unsigned short mp,unsigned short mmp,
		    unsigned short st,unsigned short mst)
  {
    p.hp=hp;    p.maxHp=mhp;
    p.mp=mp;    p.maxMp=mmp;
    p.st=st;    p.maxSt=mst;

  };

  void setStats(unsigned short s,unsigned short a,
		unsigned short v,unsigned short e)
  {
    p.str=s;    p.agl=a;    p.vit=v;    p.enr=e;    
  };

  
  HexBuff * build()
  {

   
    //unsigned char t[]={
    // 0xc3 ,0x33 ,0xF3 ,0x03, 
    // 0x8E ,0x88 , //x,y 
    // 0x00 ,//mapa 6
    //  0x03 , // unknown
    // 0x00 ,0x00 , 0x00 ,0x00, // exp 
    // 0x64 ,0x00 ,0x00 ,0x00,  //lexp
    //0x00 ,0x01 , //lp 16
	
    //0x1C ,0x00 , //str
    // 0x14 ,0x00 , //agi 
    //0x19 ,0x00 , //vit
    //0x0A ,0x00 , //enr
	
    // 0x6E ,0x00 , //live
    //0x6E ,0x00 , //mlive
    //0x14 ,0x00 , //mana
    //0x14, 0x00 , //mmana
    //0x0C ,0x00 , //st35
    //0x19 ,0x00 , //mst
	
	
    //0x0f ,0x0f , //12 00
    //       0  kolor nika?
    //0x01 ,0x00 ,0x00 ,0x00 , // mony
	
	
    //0x03 , //color nicka -0-3 ok 4-6 red [44]
	
    //      0x02 ,
    //0x00 ,0x00 , //spare points max [46]
    //0x0f ,0x00 , // spare point [48]
    unsigned char pack[sizeof (CharacterInfo)+1]={0};
    memmove(pack,&p,sizeof(CharacterInfo));
    //0x0f ,0xff , // unk
            
    //0x00};
    //todo napisac ustawiana statow
    (*h)[0].writeAC(pack,sizeof(CharacterInfo));

    //(*h)[6].writeC(_m); //mapa		D
    //    (*h)[7].writeC(0x00);	// ??
	
    //    (*h)[8].writeL(_exp,true);//exp
    //(*h)[12].writeL(_lexp,true);//lexp
    //(*h)[16].writeI(_lp,true); // lp D
	
    //(*h)[18].writeI(_str,true);//D
    //(*h)[20].writeI(_agi,true);//D
    //(*h)[22].writeI(_vit,true);//D
    //(*h)[24].writeI(_enr,true);//D
    //	
    //(*h)[26].writeI(_heal,true);//D
    //(*h)[28].writeI(_mheal,true);//D
    //(*h)[30].writeI(_mana,true);//D
    //(*h)[32].writeI(_mmana,true);//D
    //(*h)[34].writeI(_stamina,true);//D
    //(*h)[36].writeI(_mstamina,true);//D
	
	
    //(*h)[40].writeL(_zen,true); 
	 
    return h;
  };
	
};

#endif /*SSELECTEDCHARACTERSTATS_H_*/
