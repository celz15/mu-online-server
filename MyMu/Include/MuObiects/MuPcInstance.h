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

//TASK KLASY
class MuPcInstance; // predefinicja dla task klas

class TaskMP:public Job{
MuPcInstance* me;
	public:
	TaskMP(MuPcInstance* m){
		opis="Uzupelnianie many";
		me=m;};
	~TaskMP(){}
	virtual void Run();
};
class TaskSP:public Job{

MuPcInstance *me;
	public:
	TaskSP(MuPcInstance* m){
		opis="Uzupelnianie Staminy";
		me=m;};
	~TaskSP(){}
	virtual void Run();
};
//MAIN KLAS

class ObiectPool;
class MuPcInstance:public MuCharacter 
{
  friend class ObiectPool;
  // SOCKET
  Socket*_Con;				//polaczenie
	


  unsigned long  _exp; 		// ilosc posiadanego expa
  unsigned long  _nexp;		// ilosc expa na  lvl up
  int   _lp;					// lvlup points
	
  unsigned long _clvl(int t1)
  {
    unsigned long t=1000;
    for(int c=1;c==t1;c++)
      t=t*2;
    return t;
  };
	
  int _str;					//strange
  int _agl;					//agilty
  int _vit;					//vitali
  int _enr;					//energy
  int _com; 					//command tylko dla dl
	
	
  // MANA USTAWIENIA
  int _curentMP;				//aktualna ilosc many
  int _maxBaseMP;				//max punktow many
  int _reqMP;					//stopa uzupelniania mp
  int _dtMP;					//intensywnosc uzupelniania mp;
  bool _RreqMP;				//czy urucomiony task
  TaskMP *_TaskMP;			//task uzupelniania zycia
  //metody do many:
  void _InitMP(){if (_TaskMP==NULL) _TaskMP=new TaskMP(this);};
	
  void _RStepMP()
  {
    _curentMP+=_reqMP;			//uzupelniamy o dana ilosc mane
    if(_curentMP>_maxBaseMP)
      {
	_curentMP=_maxBaseMP;	//fixujemy ew nadmiar
	_RreqMP=false;			//osiagnelismy full nie trzeba uzupelniac
      };
  };	
	
  void _SetupMP()
  {
    //zalorzenie tu mamy ustawic wzorcowe ustawieni [do testow]
    _maxBaseMP =100;
    _reqMP=		5;
    _dtMP=		20;
    _curentMP=	10;
    _RreqMP=	true;
    std::cout << ">SYSTEM: SetupMP done\n";
  };
	
  //Status postaci / atakowany itp
  //ogulne zalozenia:
  //statyuse:
  //0 nic nie robie takiego:P
  //1 atakuje
  //2 jestem atakowany
  //3 podczas trade
	
	
	
  // STAMIANA USTAWIENIA
  int _curentSP;				//aktualan ilosc p. staminy
  int _maxBaseSP;				//max punktow staminy
  int _reqSP;					//stopa uzupelniania mp
  int _dtSP;					//intensywnosc uzupelniania mp;
  bool _RreqSP;				//czy urucomiony task
  TaskSP *_TaskSP;			//task zupelniania sp
  void _InitSP(){if (_TaskSP==NULL) _TaskSP=new TaskSP(this);};
  void _RStepSP()
  {
    _curentSP+=_reqSP;			//uzupelniamy o dana ilosc mane
    if(_curentSP>_maxBaseSP)
      {
	_curentSP=_maxBaseSP;	//fixujemy ew nadmiar
	_RreqSP=false;			//osiagnelismy full nie trzeba uzupelniac
      };
  };
	
  void _SetupSP()
  {
    //zalorzenie tu mamy ustawic wzorcowe ustawieni [do testow]
		 
    _maxBaseSP =100;
    _reqSP=		3;
    _dtSP=		20;
    _curentSP=	10;
    _RreqSP=	true;
    std::cout << ">SYSTEM: SetupSP done\n";
  };
	
  //dmg ?
	
  //inwentory
  MuHandInwentory* _inwentory;
	
  //Skille
  MuSkillMng * _skillMng;
protected:
  MuPcInstance()	
  {
    _inwentory=new MuHandInwentory();
    _SetupMP();							//ustawiamy mp
    _SetupSP();							//ustawiamy sp
    //_nexp=calculateLvlUpExp();		//liczymy exp na lvlup
    //_skillMng=new MuSkillMng(this);		//ustawiamy skil list
    std::cout << "MuPcIntancr init done \n";
  }
public:	

  virtual ~MuPcInstance()
  {
    std::cout << "Preparing to close Character\n";
  }

  //MAPA
  //MuMap* getAMap(){return _mapa;};				//pobiera aktualna mape
  //void   setAMap(MuMap*m){_mapa=m;};				//ustawia aktualna mape

  //WYSYLANIE PACZEK
  void setConnected(Socket*s){_Con=s;};			//pobiera Polaczenie
  void Send(SBPacket *p){_Con->Send(p);};			//posyla do klijenta paczke

  //STATYSTYKI USTAWIANUE
  void setStr(int str);				//ustawia  sile
  void setAgl(int agl);				//usatwia zrecznosc
  void setVit(int vit);				//ustawia zycie
  void setEnr(int enr);				//ustawia energie
  void setCom(int com);				//ustawia command

  //STATYSTYKI POBUR
  int getStr();						//pobiera sile
  int getAgl();						//pobiera agi
  int getVit();						//pobiera zycie
  int getEnr();						//pobiera energie
  int getCom();						//pobiera command[tylko dla dl;

  //INCRASE STATS
  void incStr(){_str++;};
  void incAgl(){_agl++;};
  void incVit(){_vit++;};
  void incEnr(){_enr++;};
  void incCom(){_com++;};
 
  //STATYSTYKI B ALL
  void setStats(int s=0,int a=0,int v=0,int e=0,int c=0) //domyslnie mozna tylko setStats
  {
    if(getChNew())					//jesli to nowa postac
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



  //EXP I LP	
  void setExp(long int e);			//ustawia exp
  void setExp(long int e,int lp)
  {
    setExp(e);
    _lp=lp;
  };
  long int getExp();				    //pobiera exp
  int getLp(){return _lp;};
  bool decLp()						//zmiensza LP jesli ponizej 0 zwraca false
  {
    _lp--;
    if(_lp<0)
      {
	_lp=0;
	return false;
      };
    return true;
  };
  void incLp(int i){
    std::cout << "lp z " << _lp;
    _lp+=i;
    std::cout << " na " << _lp <<"\n";
		
  };			//dodajmy nowe lp
  void updateNLvlExp()
  {
    _nexp=calculateLvlUpExp();
  }
  //STAMINA/MANA
  int getMaxBaseMP();						//pobieramy max mp
  int getMaxBaseSP();						//pobieramy maz sp

  void setMaxBaseMP(int mp);				//ustawiamy max MP
  void setMaxBaseSP(int sp); 				//ustawiamy max SP
	
  int getCurentMP();						//pobieram aktualna ilosc MP
  int getCurentSP();						//pobieramy aktualna ilosc SP
	
  //UZUPELNIANIE STAMINY/MANY
  bool ManaReqNeed();						//czy potrazeba regeneracji many
  bool StaminaReqNeed();					//czy potrazeba regeneracji staminy
		
  void MPReqRun();						//uruchamiamy uzupelnianie many
  void SPReqRun();						//uruchamiamy uzupelnianie staminy
  void UpdateMaxims()						//update hp,mp,sp po lvl up
  {
    setMaxBaseHP(calculateHP(getLvl(),getVit()));
    _maxBaseMP=calculateMP(getLvl(),getEnr());
    _maxBaseSP=getAgl()+getStr()+getEnr();			//tak narazie
  };
  void restartHMSP()					//restartuje hp,mp,sp
  {
    setCurentHP(getCurentHP());		//nie trzeba zatrzymywac taskow
    _curentMP=_maxBaseMP;			//poniewaz same sie wylacza
    _curentSP=_maxBaseSP;			//po zresetowanie hp,mp,sp
  };

	

  virtual void CheckStatusPC();					//sprwadzamy co sie dzije z postacia 
  //i jeslil np nie ma zycia uruchamimy 
  //odpowiednie taski
	

  //PACKI OBSLUGI STATUSU POSTACI
  void printfme()
  {
    //		std::cout << ">>>OB: " << getName()<<"\n";
    //		std::cout << ">> Z: " << getCurentHP()<< " na: "<<getMaxBaseHP() << "\n";
    //		std::cout << ">> M: " << getCurentMP()<< " na: "<<getMaxBaseMP() << "\n";
    //		std::cout << ">> S: " << getCurentSP()<< " na: "<<getMaxBaseSP() << "\n";
  };
	
  void updateLive()						//odswierzenei statusu zycia i staminy
  {	
    SUpdateLive *t=	new SUpdateLive(getCurentHP());
    Send(t);
    delete t;
  };
	
  void updateMaxLive()
  {
		
    SUpdateMaxBaseLive *t=new SUpdateMaxBaseLive(getMaxBaseHP());
    Send(t);
    delete t; 
  };	
  void updateManaStamina()								//odswierzenie statusu many
  {	
    SUpdateManaStamina*t=new SUpdateManaStamina(getCurentMP(),getCurentSP());
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
  void IGotExp(int from,int i)
  {
    Send(new SGotExp(from,i));
  };
    
  unsigned long calculateLvlUpExp()    
  {
    //kolejny lvl to exp potrzebny * 2 na poprzedni
    int alvl=getLvl();
    	
    unsigned long nlvl =_clvl(alvl);
    return nlvl;
  };
	
  //LVL UP!!
  void IGotLvlUp()
  {
		
    setLvl(getLvl()+1);			//zwiekszamy lvl
    _nexp=calculateLvlUpExp();	//liczymy exp potrzebny na nowy lvl
    incLp(getBaseLP());			//dodajemy nowe lp
    UpdateMaxims();				//updatujemy hp,mp,sp
    restartHMSP();				//restartujemy hp,mp,sp
									
    SLvlUp *lvlup=new SLvlUp(getLvl(),getLp(),getMaxBaseHP(),getMaxBaseMP(),getMaxBaseSP());
    Send(lvlup);				//posylamy "lvlup"
    delete lvlup;
    updateMaxLive();			//posylamy update UpdatMaxHealBase
    updateLive();				//i curent hp
		
  };
  void getExp(long exp)
  {
    _exp+=exp;
    std::cout << "dostalrm exp:"<<_exp<<"na"<<_nexp<<".\n";
    SServersPublicMsg *gexp=new SServersPublicMsg("Dostales Exp:",Mblue); 
    broadcastPacket(gexp); //info o expie
    delete gexp;
    if(_exp>_nexp)
      {
	//SServersPublicMsg*nlvl=new SServersPublicMsg("LVL UP",Mblue);
	//broadcastPacket(nlvl);		//info o lvlup
	//delete nlvl;
	IGotLvlUp();													//lvl up
      };
  };
	
  //ITEMS
	
  void MyItemList()
  {
    SInwenoryList *i=new SInwenoryList();
    Send(i);
    delete i;
  };
	
  //SKILLe
	
  MuSkillMng * getSkillMng(){return _skillMng;	};

  void UseSkill(int id)
  {
    _skillMng->getId(id)->Run();   // uruchamia skilla
  };
	
  void MySkillList()
  {
    //todo napisac klase cskillList
  };
	
  void IAddSkill(MuSkill * sk)
  {
    _skillMng->addNewSkill(sk);
    //paczka add skill
  };
  void IDeleteSkill(int id)
  {
    //_skillMng->DeleteSkill(id);
    //pacza dereister skill
  };
	
}; 

#endif /*MUPCINSTANCE_H_*/
