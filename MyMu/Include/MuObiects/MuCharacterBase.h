#ifndef MUCHARACTERBASE_H_
#define MUCHARACTERBASE_H_
#include <string>
class MuCharacterBase
{
	std::string ch_name;			//moj nik
	int 		ch_class;			//klasa
	int 		ch_lvl;				//lvl
	bool 		ch_new;				//czy postac nowa
protected:
void setAll(std::string name,int clas,int lvl=1,bool n=true)
{
	ch_name=name;
	ch_class=clas;
	ch_lvl=lvl;
	ch_new=n;
}
public:
	MuCharacterBase(){};
	MuCharacterBase(std::string name,int clas,int lvl=1,bool n=true)
				:ch_name(name),ch_class(clas),ch_lvl(lvl),ch_new(n){};
	virtual ~MuCharacterBase(){};
	std::string getName()	{return ch_name;};
	int getClass()			{return ch_class;};
	int getLvl()			{return ch_lvl;};
	bool getChNew()			{return ch_new;};
	void setName(std::string n){ch_name=n;};
	void setLvl(int lvl)	{ch_lvl=lvl;};
	void setClass(int cl)	{ch_class=cl;};
	void etChNew(bool n)	{ch_new=n;};
	void Set(MuCharacterBase *b)
	{
	ch_name=b->getName();
	ch_class=b->getClass();
	ch_lvl=b->getLvl();
	ch_new=b->getChNew();
	};
		
	//KALKULACJE DLA KLAS
	int calculateHP(int lvl,int vit)
	{
		switch(getClass())
		{
			case 0x00: 
			case 0x10: return 60+(lvl*1)+(vit*1);
			case 0x20: 
			case 0x30: return 110+(lvl*2)+(vit*3);
			case 0x40: 
			case 0x50: return 80+(lvl*1)+(vit*1);
			case 0x60: return 110+lvl+(vit*2);
			case 0x80: return 110+lvl+(vit*2);
			
		};
	};

	int calculateMP(int lvl,int enr)
	{
		switch(getClass())
		{
			case 0x00: 
			case 0x10: return 60+(lvl*2)+(enr*2);
			case 0x20: 
			case 0x30: return (int)(20+(lvl*0.5)+(enr*1));
			case 0x40: 
			case 0x50: return (int)(30+(lvl*1.5)+(enr*1.5));
			case 0x60: return 60+(lvl*1)+(enr*2);
			case 0x80: return 60+(lvl*1)+(enr*2);	
		};
	};


		
int getBaseLP()
	{
		switch(getClass())
		{
			case 0x00: return 5; 
			case 0x10: return 6;
			case 0x20: return 5;
			case 0x30: return 6;
			case 0x40: return 5;
			case 0x50: return 6;
			case 0x60: return 5;
			case 0x80: return 7;
			
		};
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

#endif /*MUCHARACTERBASE_H_*/
