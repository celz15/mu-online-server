#ifndef SSELECTEDCHARACTERSTATS_H_
#define SSELECTEDCHARACTERSTATS_H_
#include "Protocol/SBPacket.h"
#include "Protocol/BaseStruct.h"


struct CharacterInfoSrt
{
  PMSG_HEADA m_Head;
  unsigned char m_uSubType;
  unsigned char m_uPosX;
  unsigned char m_uPosY;
  unsigned char m_uMapID;
  unsigned char m_uDir;
  unsigned char m_uUnk1[4];
  unsigned long m_uCurrentExp;
  
  
};




//clasa : SSelectedharacterStats
//h    -paczka budowana
class SSelectedharacterStats : public CSPacket
{
	//pozycja
  int _x;					//pozycja x
  int _y;					//pozycja y
  int _m; 				//kod mapy
//Doswiadczenie
  unsigned long _exp;		//curent exp
  unsigned long _lexp;	//exp na kolejny lvl
  int _lp;				//lvl points
  //statystyki
  int _str;					//sila
  int _agi;				//agil
  int _vit;				//vital
  int _enr;				//energia
  //zycie,mana,stamina
  int _heal;				//zycie
  int _mheal;				//max zycia
  int _mana;
  int _mmana;
  int _stamina;
  int _mstamina;
  //zeny
  unsigned long _zen;		//ilosc many
  //spare
  int	_lsp;	//left spare
  int	_rsp;   //right sare

 public:
  SSelectedharacterStats(
			 int x,int y,int m, 								// pozycja
			 unsigned long exp,unsigned long lexp,int lp, 	//exp i punkty do rozdania
			 int s,int a,int v,int e,						//statystyki
			 int vi,int mvi,int ma,int mma,int st,int mst,		//zycie mana stamina
			 unsigned long zen,								//zeny
			 int lsp,int rsp									// lir spare
							
			 
			 ):CSPacket()
    {
      //pos
      _x=x;
      _y=y;
      _m=m;	
      //exp
      _exp=exp;
      _lexp=lexp;
      _lp=lp;
      // stats
      _str=s;
      _agi=a;
      _vit=v;
      _enr=e;
      //zycie...
      _heal=vi;				//zycie
      _mheal=mvi;				//max zycia	
      _mana=ma;
      _mmana=mma;
      _stamina=st;
      _mstamina=mst;
      //lvl
      //spare
      _lsp=lsp;	//left spare
      _rsp=rsp;   //right sare
      
      //zens
      _zen=zen;
      MyName="F303 Selcted Character Stats";
    };
  ~SSelectedharacterStats(){};
  HexBuff * build()
    {
      unsigned char t[]={
	0xc3 ,0x33 ,0xF3 ,0x03, 
	0x8E ,0x88 , //x,y 
		   0x00 ,//mapa 6
	0x03 , // unknown
	0x00 ,0x00 , 0x00 ,0x00, // exp 
	0x64 ,0x00 ,0x00 ,0x00,  //lexp
	0x00 ,0x01 , //lp 16
	
	0x1C ,0x00 , //str
	0x14 ,0x00 , //agi 
	0x19 ,0x00 , //vit
	0x0A ,0x00 , //enr
	
	0x6E ,0x00 , //live
	0x6E ,0x00 , //mlive
	0x14 ,0x00 , //mana
	0x14, 0x00 , //mmana
	0x0C ,0x00 , //st35
	0x19 ,0x00 , //mst
	
	
	0x0f ,0x0f , //12 00
	//       0  kolor nika?
	0x01 ,0x00 ,0x00 ,0x00 , // mony
	
	
	0x03 , //color nicka -0-3 ok 4-6 red [44]
	
	0x02 ,
	0x00 ,0x00 , //spare points max [46]
	0x0f ,0x00 , // spare point [48]
	
	0x0f ,0xff , // unk
            
	0x00};
      //todo napisac ustawiana statow
	(*h)[0].writeAC(t,53);
	(*h)[4].writeC(_x);       //x 	D
	(*h)[5].writeC(_y);		  //y	D
	(*h)[6].writeC(_m); //mapa		D
	(*h)[7].writeC(0x00);	// ??
	
	(*h)[8].writeL(_exp,true);//exp
	(*h)[12].writeL(_lexp,true);//lexp
	(*h)[16].writeI(_lp,true); // lp D
	
	(*h)[18].writeI(_str,true);//D
	(*h)[20].writeI(_agi,true);//D
	(*h)[22].writeI(_vit,true);//D
	(*h)[24].writeI(_enr,true);//D
//	
	(*h)[26].writeI(_heal,true);//D
	(*h)[28].writeI(_mheal,true);//D
	(*h)[30].writeI(_mana,true);//D
	(*h)[32].writeI(_mmana,true);//D
	(*h)[34].writeI(_stamina,true);//D
	(*h)[36].writeI(_mstamina,true);//D
	
	
	(*h)[40].writeL(_zen,true); 
	 
	return h;
	};
	
};

#endif /*SSELECTEDCHARACTERSTATS_H_*/
