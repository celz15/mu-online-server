#include "MuObiects/MuPcInstance.h"


void MuPcInstance::setStr(unsigned short str){p_StatStr=str;};				//ustawia  sile
void MuPcInstance::setAgl(unsigned short agl){p_StatAgl=agl;};				//usatwia zrecznosc
void MuPcInstance::setVit(unsigned short vit){p_StatVit=vit;};				//ustawia zycie
void MuPcInstance::setEnr(unsigned short enr){p_StatEnr=enr;};				//ustawia energie
void MuPcInstance::setCom(unsigned short com){p_StatCom=com;};				//ustawia command

//void MuPcInstance::setExp(long int e){p_CurExp=e;};				//ustawia exp
//long int MuPcInstance::getExp(){return p_CurExp;};				//pobiera exp

//STATYSTYKI POBUR
unsigned short MuPcInstance::getStr(){return p_StatStr;};						//pobiera sile
unsigned short MuPcInstance::getAgl(){return p_StatAgl;};						//pobiera agi
unsigned short MuPcInstance::getVit(){return p_StatVit;};						//pobiera zycie
unsigned short MuPcInstance::getEnr(){return p_StatEnr;};						//pobiera energie
unsigned short MuPcInstance::getCom(){return p_StatCom;};						//pobiera command[tylko dla dl;
	
