#ifndef MUSKILLMNG_H_
#define MUSKILLMNG_H_
#include <vector>
#include <string>
#include <iostream>
//#include "MuObiects/MuPcInstance.h"
class MuSkill
{
	//BASE
	int id;					//id skilla
	std::string name;		//nazwa skila
	//MANA STAMINA LIVE REQ
	int _hpR;				//wymagane zycie
	int _mpR;				//wymagana mana
	int _spR;				//wymagna stamina
	public:
	MuSkill(int _id,std::string _name)
	{
		id=_id;
		name=_name;
	};
	void print()
	{
		std::cout << "SKILL : " << name << " o id[" << id << "]\n";
	};
	
	virtual void Run()
	{
		std::cout << "Urzywam ";
		print();
	}
	
	//base
	void setId(int _id){id=_id;};
	void setName(std::string n){name=n;};

	std::string getName(){return name;};
	int getId(){return id;};
	//req
	
	int getHpR(){return _hpR;};
	int getMpR(){return _mpR;};
	int geySpR(){return _spR;};
	
	void setHpR(int hp){_hpR=hp;};
	void setMpR(int mp){_mpR=mp;};
	void setSpR(int sp){_spR=sp;};
	
};
class MuPcInstance;						//predefinicja

class MuSkillMng
{
protected:
MuPcInstance *_pc;						// posiadacz skilli
std::vector <MuSkill *> Vskill; 		// vector skilli
public:
MuSkillMng(MuPcInstance *pc)
{
	_pc=pc;								//ustawaimy pc
};
~MuSkillMng(){};

void addNewSkill(MuSkill * s)
{
	Vskill.push_back(s);		
};

void setPcIns(MuPcInstance *pc) {_pc=pc;};

MuSkill * getId(int id)
{
	for (int i=0;i< Vskill.size();i++)
	if( Vskill[i]->getId() == id) return Vskill[i];
	return NULL;
};

std::vector<MuSkill*> getSkillVect(){return Vskill;};

void print()
{
	std::cout << "Lista skilli:\n";
	for(int i=0;i<Vskill.size();i++)
	{
		std::cout << i << "# ";
		Vskill[i]->print();
	};
	std::cout << "\n";
};
};
 
#endif /*MUSKILLMNG_H_*/
