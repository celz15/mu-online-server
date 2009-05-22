#ifndef MUPCINSTANCE_H_
#define MUPCINSTANCE_H_
//POLACZNIE
#include "Socket/Socket.h"						//placznie
//SKLADOWE
#include "MuObiects/MuCharacter.h"				//dziedziczenia
#include "MuObiects/MuMap.h"					//mapa
#include "Task/Task.h"							//task instace
#include "MuObiects/MuHandInwentory.h"			//inwentory
#include "MuObiects/MuSkillMng.h"				//skille

//PROTOCOL
#include "Protocol/SUpdateLive.h"
#include "Protocol/SUpdateManaStamina.h"
#include "Protocol/SUpdateMaxBaseLive.h"
#include "Protocol/SServersPublicMsg.h"
#include "Protocol/SGotExp.h"
#include "Protocol/SInwentoryList.h"
#include "Protocol/SLvlUp.h"
#include "Protocol/SNpcMiting.h"
#include "Protocol/SForgetId.h"

class MuPcInstance; // predefinicja dla task klas


class ObiectPool;
class MuPcInstance:public MuCharacter 
{
  friend class ObiectPool;
  //------------------connection----------------------------
  Socket* p_Con;				//polaczenie
  //---------------------lvl up and experance --------------
  unsigned long  p_CurExp; 		// ilosc posiadanego expa
  unsigned long  p_NexExp;		// ilosc expa na  lvl up
  unsigned short p_CurLP;		// lvlup points
  unsigned char  p_LpPerLvl;            // lp per lvl
  //------------------------base stats
  unsigned short p_StatStr;					//strange
  unsigned short p_StatAgl;					//agilty
  unsigned short p_StatVit;					//vitali
  unsigned short p_StatEnr;					//energy
  unsigned short p_StatCom; 					//command tylko dla dl
  //------------------------other 
  unsigned char p_Class;
  bool          p_NewChar;
  //-------------------------inwentory
  unsigned long p_InwZen;

protected:

  MuPcInstance()	
  {
    
    std::cout << "MuPcIntancr init done \n";
  }

public:
  unsigned long getCurExp()
  {
    return p_CurExp;
  };
  unsigned short getCurLp()
  {
    return p_CurLP;
  };
  void setCurExp(unsigned long exp)
  {
    p_CurExp=exp;
  }
  void setInwZen(unsigned long zen)
  {
    p_InwZen=zen;
  }
  unsigned long getInwZen()
  {
    return p_InwZen;
  }
  void setCurExp(unsigned long exp , unsigned short lp)
  {
    setCurExp(exp);
    p_CurLP=lp;
  };
  void SetFromCharacterBase(MuCharacterBase * c)
  {
    setName((char *)c->getName().c_str());
    setLvl(c->getLvl());
    setClass(c->getClass());
    setNewChar(c->getChNew());
    
  }
  void setNewChar(bool t)
  {
    p_NewChar=t;
  };
  void setClass(unsigned char cl)
  {
    p_Class = cl;
  };
  unsigned char getClass()
  {
    return p_Class;
  }
  bool decCurLp()
  {
    if(p_CurLP<=0) return false;
    p_CurLP--;
    return true;
  };

  virtual ~MuPcInstance()
  {
    std::cout << "Preparing to close Character\n";
  }
  void setConnected(Socket*s)
  {
    p_Con=s;
  };			

  void Send(SBPacket *p)
  {
    if (p !=NULL)
    p_Con->Send(p);
  };			

  //STATYSTYKI USTAWIANUE
  void setStr(unsigned short str);				//ustawia  sile
  void setAgl(unsigned short agl);				//usatwia zrecznosc
  void setVit(unsigned short vit);				//ustawia zycie
  void setEnr(unsigned short enr);				//ustawia energie
  void setCom(unsigned short com);				//ustawia command

  //STATYSTYKI POBUR
  unsigned short getStr();						//pobiera sile
  unsigned short getAgl();						//pobiera agi
  unsigned short getVit();						//pobiera zycie
  unsigned short getEnr();						//pobiera energie
  unsigned short getCom();						//pobiera command[tylko dla dl;

  //INCRASE STATS
  void incStr(){p_StatStr++;};
  void incAgl(){p_StatAgl++;};
  void incVit(){p_StatVit++;};
  void incEnr(){p_StatEnr++;};
  void incCom(){p_StatCom++;};
 
  void setLpPerLvl(unsigned char lp)
  {
    p_LpPerLvl = lp;
  };
  //knowns list
  void CheckToForgetInViewPort()
  {
    MuViewPortSet * t = getViewPort();
    for (int i =0 ; i< t->getViewSize(); i++)
      if (t->getViewPort(i)->c_State== MuViewPort::S_ToForget)
	{
	  Send(new SForgetId(t->getViewPort(i)->o_Index));
	  t->getViewPort(i)->c_State=MuViewPort::S_Empty;
	};
  };

 void checkNewInViewPort()
  {
  SNpcMiting * mit =new SNpcMiting();
  unsigned char c=0;
    MuViewPortSet * t = getViewPort();
    for (int i =0 ; i< t->getViewSize(); i++)
      {
	if (t->getViewPort(i)->c_State== MuViewPort::S_New)
	  {
	    c++;
	    mit->addToPack(t->getViewPort(i)->o_Index);
	    t->getViewPort(i)->c_State=MuViewPort::S_Known;
	  };
      };
    if(c!=0)Send(mit);
    delete mit;
  }
  
  //STATYSTYKI B ALL
 
  void setStats(int s=0,int a=0,int v=0,int e=0,int c=0) //domyslnie mozna tylko setStats
  {
    if(p_NewChar)					//jesli to nowa postac
      {
	setStr(getBaseStr());		//to ustawiamy statystyki fabr
	setAgl(getBaseAgi());
	setVit(getBaseVit());
	setEnr(getBaseEnr());
	setCom(c);
      }else							//jesli nie to z bd ale nie tu :P
      {
	setStr(s);
	setAgl(a);
	setVit(v);
	setEnr(e);
	setCom(c);
      };
  };	

 void UpdateMaxims()						//update hp,mp,sp po lvl up
  {
    StatCalcMaxHp();
    StatCalclMaxMp();
    setStatMaxSt(getAgl()+getStr()+getEnr());
  };

	
  void IUpdateCurHp()						//odswierzenei statusu zycia i staminy
  {	
    SUpdateLive *t=	new SUpdateLive(getStatCurHp());
    Send(t);
    delete t;
  };
	
  void IUpdateMaxHp()
  {		
    SUpdateMaxBaseLive *t=new SUpdateMaxBaseLive(getStatMaxHp());
    Send(t);
    delete t; 
  };
	
  void IUpdateCurMpSt()
  {	
    SUpdateManaStamina*t=new SUpdateManaStamina(getStatCurMp(),getStatCurSt());
    Send(t);
    delete t;
  };
	
  //POBIREANIE DMG 
  int getRealDmg()
  {
    //todo napisac liczenia dmg
    return 6;  // ustawimy na 6
  };
    
    
  //EXPERANCE
  void IGotExp(unsigned short from,int i)
  {
    Send(new SGotExp(from,i));
  };
  
  
 
  void IGotLvlUp()
  {
  };
       	
  void IAddSkill(MuSkill * sk)
  {
    //paczka add skill
  };

  void IDeleteSkill(int id)
  {
    //pacza dereister skill
  };
	
private:
  ///---------------------misc methods
	
  unsigned long CalculateExpForNextLvl(unsigned short lvl)
  {
    unsigned long t=1000;
    for(int c=1;c<=lvl;c++)
      t=t*2;
    return t;
  };
	
  void StatCalcMaxHp()
  {
    int lvl = getLvl();
    int vit = getVit();
    int max;
    switch(getClass())
      {
      case 0x00: 
      case 0x10: max= 60+(lvl*1)+(vit*1);break;
      case 0x20: 
      case 0x30: max= 110+(lvl*2)+(vit*3);break;
      case 0x40: 
      case 0x50: max= 80+(lvl*1)+(vit*1);break;
      case 0x60: max= 110+lvl+(vit*2);break;
      case 0x80: max= 110+lvl+(vit*2);break;
      };
    setStatMaxHp(max);
  };
  void StatCalclMaxMp()
  {
    int max = 0;
    int lvl = getLvl();
    int enr = getEnr();

    switch(getClass())
      {
      case 0x00: 
      case 0x10: max= 60+(lvl*2)+(enr*2);break;
      case 0x20: 
      case 0x30: max= (int)(20+(lvl*0.5)+(enr*1));break;
      case 0x40: 
      case 0x50: max= (int)(30+(lvl*1.5)+(enr*1.5));break;
      case 0x60: max= 60+(lvl*1)+(enr*2);break;
      case 0x80: max= 60+(lvl*1)+(enr*2);break;
      };
    setStatMaxMp(max);
  };
  
  void statCalcLpPerLvl()
  {
    unsigned char lp = 0;
    switch(getClass())
      {
      case 0x00: lp= 5;break; 
      case 0x10: lp= 6;break; 
      case 0x20: lp= 5;break; 
      case 0x30: lp= 6;break; 
      case 0x40: lp= 5;break; 
      case 0x50: lp= 6;break; 
      case 0x60: lp= 5;break; 
      case 0x80: lp= 7;break; 
      };
    setLpPerLvl(lp);
  };	

  int getBaseStr()
  {
    switch(getClass())
      {
      case 0x00:  
      case 0x10: return 15;
      case 0x20: 
      case 0x30: return 28;
      case 0x40: 
      case 0x50: return 22;
      case 0x60: return 26;
      case 0x80: return 26;
			
      };
  };
  int getBaseAgi()
  {
    switch(getClass())
      {
      case 0x00:  
      case 0x10: return 18;
      case 0x20: 
      case 0x30: return 20;
      case 0x40: 
      case 0x50: return 25;
      case 0x60: return 26;
      case 0x80: return 20;
			
      };
  };
  int getBaseVit()
  {
    switch(getClass())
      {
      case 0x00:  
      case 0x10: return 15;
      case 0x20: 
      case 0x30: return 25;
      case 0x40: 
      case 0x50: return 20;
      case 0x60: return 26;
      case 0x80: return 20;
			
      };
  };
  int getBaseEnr()
  {
    switch(getClass())
      {
      case 0x00:  
      case 0x10: return 30;
      case 0x20: 
      case 0x30: return 10;
      case 0x40: 
      case 0x50: return 15;
      case 0x60: return 26;
      case 0x80: return 15;
			
      };
  };

}; 

#endif /*MUPCINSTANCE_H_*/
