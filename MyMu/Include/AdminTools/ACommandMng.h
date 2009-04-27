#ifndef ACOMMANDMNG_H_
#define ACOMMANDMNG_H_
#include "AdminTools/ACommandT.h"
#include <map>
#include <vector>
#include <iostream>

using std::map;
class ACommandMng
{
 protected:
  int _acces;				                  //rodzaj dostepu do mng -1 globalny
  map<std::string , ACommandT*> _commandMap;
 public:
  
  ACommandT *getCommand(std::string s){
    return _commandMap[s];
  };
  
  ACommandMng(std::vector < ACommandT * > list)
    {
      for (int i=0;i<list.size();i++)
	{
	  std::cout << "Register new Command in CommandMng: " << list[i]->getCommand() << "\n";
	  _commandMap.insert(std::make_pair(list[i]->getCommand(),list[i]));
	};
    };
  ACommandMng()
    {
    };
  //pobieamy komendy z dango lvl'u
  std::vector < ACommandT * >  getCommandListFor(int lvl)
    {
      std::vector < ACommandT * > tList;
      for ( map<std::string , ACommandT*>::iterator i= _commandMap.begin(); i!=_commandMap.end();i++)
	if((*i).second->getAccesLvl()>=lvl) tList.push_back((*i).second);    	//sortujemy wedlug hierarhi
      return tList;
    };
  
  void ParseComandLine(std::string lin, bool flag) 					// podajemy z '/'
    {
      if(lin.empty())return;
      std::string args;									//argumenty
      std::string comm;									//comaenda
      
      int eComand=lin.find(' ',0); 						//poszukujemy spacji konczoncej nazwe komendy
      
      if (eComand!=-1)
	{
	  args=lin.substr(eComand,lin.size()-eComand);	//parsujemy arg
//	  std::cout <<"["<< args <<"]\n";
	};
      if(flag)
	comm=lin.substr(1,eComand);
      else comm = lin.substr(0,eComand);
      //samo polecenie
     // std::cout <<"po parse comm ["  <<comm <<"]\n";
      
      if(CommandExist(comm))
	{							//jesli polexenie istnieje
	  _commandMap[comm]->ParseArgs(args);				//parsujemu arg
	  _commandMap[comm]->Run();						//uruchamiamy polecenia
	}else
	  std::cout << "Command : [" << comm << "] Not exist.!! try help -l for list availble commands.\n";
      
    };
  
  
  bool CommandExist(std::string comm)
    {
      
      int cont =_commandMap.count(comm);
    //  std::cout << "ilosc znalezionych dla : [" << comm << "] jest : [" << cont << "]\n";
      if (cont <=0) return false;
      else return true;
					// nie wiem jak zwraca ale powinno byc op flse przy -1 :P
    };
  
  void AddNew(ACommandT *c)
    {
      c->Mng = this;
      std::cout << "Register new Command in CommandMng: " << c->getCommand() << "\n";
      _commandMap.insert(std::make_pair(c->getCommand(),c));
    };
  std::string getHelpFor(std::string com)
    {
      if (CommandExist(com))
	return _commandMap[com]->getDesc();
    };
  
  std::string getListOfCommands()
    {
      std::string s;
      for(map<std::string,ACommandT*>::iterator i=_commandMap.begin();i!=_commandMap.end();i++)
	{
	  s+=(*i).second->getCommand()+"    "+(*i).second->getShortDesc()+"\n";
	};
	s+="exit    shout down the server\n";
      s+="type help <command> for more informations...\n";
      return s;
    };
  
  
};
#endif /*ACOMMANDMNG_H_*/
