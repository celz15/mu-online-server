#include "MuObiects/MuPcInstance.h"


	void MuPcInstance::setStr(int str){_str=str;};				//ustawia  sile
	void MuPcInstance::setAgl(int agl){_agl=agl;};				//usatwia zrecznosc
	void MuPcInstance::setVit(int vit){_vit=vit;};				//ustawia zycie
	void MuPcInstance::setEnr(int enr){_enr=enr;};				//ustawia energie
	void MuPcInstance::setCom(int com){_com=com;};				//ustawia command
	
	void MuPcInstance::setExp(long int e){_exp=e;};				//ustawia exp
	long int MuPcInstance::getExp(){return _exp;};				//pobiera exp
	
	//STATYSTYKI POBUR
	int MuPcInstance::getStr(){return _str;};						//pobiera sile
	int MuPcInstance::getAgl(){return _agl;};						//pobiera agi
	int MuPcInstance::getVit(){return _vit;};						//pobiera zycie
	int MuPcInstance::getEnr(){return _enr;};						//pobiera energie
	int MuPcInstance::getCom(){return _com;};						//pobiera command[tylko dla dl;
	
	//STAMINA/MANA
	int MuPcInstance::getMaxBaseMP(){return _maxBaseMP;};
	int MuPcInstance::getMaxBaseSP(){return _maxBaseSP;};

	void MuPcInstance::setMaxBaseMP(int mp){_maxBaseMP=mp;};
	void MuPcInstance::setMaxBaseSP(int sp){_maxBaseSP=sp;}; 
	
	int MuPcInstance::getCurentMP(){return _curentMP;};
	int MuPcInstance::getCurentSP(){return _curentSP;};
	
	//UZUPELNIANIE STAMINY/MANY
	bool MuPcInstance::ManaReqNeed(){ 						//czy potrazeba regeneracji many
		_RreqMP=(getMaxBaseMP()>getCurentMP());
		return _RreqMP;
		};
		
	bool MuPcInstance::StaminaReqNeed(){					//czy potrazeba regeneracji staminy
		_RreqSP=(getMaxBaseMP()>getCurentMP());
		return _RreqSP;
		};
	
	void MuPcInstance::MPReqRun()
	{
		if(_RreqMP)									//jesli task ma byc uruchominy	
		{
			_InitMP();								//inicjujemy task mp jesli jescze nie zainicjowany
			_RStepMP();				
			updateManaStamina();				//usupelniamy zycie (krok)
			//TaskCore->AddJob(_TaskMP,_dtMP);		//dodajemy taska do listy zadan
			//wysylamy info o updacie ??? many?
		};
		
	};

	void MuPcInstance::SPReqRun()
	{
		if(_RreqSP)									//jesli task ma byc uruchominy	
		{
			_InitSP();								//inicjujemy task mp jesli jescze nie zainicjowany
			_RStepSP();
			updateManaStamina();								//usupelniamy stamine (krok)
			//TaskCore->AddJob(_TaskSP,_dtSP);		//dodajemy taska do listy zadan
			//wysylamy info o updacie ??? many?
		};
		
	};

void MuPcInstance::CheckStatusPC()
{
		//sprawdzamy zycie:
		if(HealReq())_bTask();	//todo zmienic nazwe na bardzie pasujaca
		//sprawdzamy mane
		if(ManaReqNeed()) MPReqRun();
		//sprawdzamy stamine
		if(StaminaReqNeed())SPReqRun();
	};

void TaskMP::Run()
{
me->MPReqRun();
me->printfme();	
};
void TaskSP::Run()
{
me->SPReqRun();
me->printfme();	
};
