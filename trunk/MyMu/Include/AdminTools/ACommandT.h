#ifndef ACOMMANDT_H_
#define ACOMMANDT_H_
#include <string>
class ACommandMng;
class ACommandT
{
	
	protected:
	int up;
	std::string _decs; 						//uprawnienia
	std::string _command;			//komenda bez '/'
	public:
	ACommandMng *Mng;
	ACommandT(int uprawnienie,std::string com){_command=com;};
	ACommandT(){};
	virtual ~ACommandT(){};
	virtual void Run()=0;			//zadanie wykonywane;
	virtual void ParseArgs(std::string arg)=0;//argumenty polecenia
	std::string getCommand(){return _command;};
	std::string getDesc(){return _decs;}; // return decryption of command
	std::string getShortDesc(){
	  return _decs.substr(0,(_decs.find("\n",0)==-1)?_decs.size():_decs.find("\n",0));};
	int getAccesLvl(){return up;};
	bool isAdmin(){return up == 0;};
	bool isOpera(){return up == 1;};
	bool isVip  (){return up == 2;};
	bool isUser (){return up == 9;};
};

#endif /*ACOMMANDT_H_*/
