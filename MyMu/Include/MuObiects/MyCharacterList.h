#ifndef MYCHARACTERLIST_H_
#define MYCHARACTERLIST_H_
#include "MuCharacterBase.h"
#include <vector>
using std::vector;
#include <iostream>
using std::cout;

struct class_stat
{
  unsigned short _str;
  unsigned short _agl;
  unsigned short _vit;
  unsigned short _enr;
  unsigned short _com;
  unsigned char _lp;
};



class MyCharacterList
{
  vector <MuCharacterBase *>list;
public:
  MyCharacterList()
  {
		
  };
  virtual ~MyCharacterList();

  //pobiera ilosc postaci
  int getCharacterCount(){return list.size();};


  // pobieramy dana postac
  // n=	numer postaci 0...4 
  MuCharacterBase * getCharacter(int n)
  {
    return list[n];
  }

  //doadjaemy nowa postac
  //ne=	nowa postac
  void addNewCharacter(MuCharacterBase * ne)
  {
    list.push_back(ne); // utawiamy postac
  };
  MuCharacterBase* getCharacter(std::string nick)
  {
    for(int a=0;a<list.size();a++)
      if(list[a]->getName().compare(nick)==0)return list[a];
  };	
	
};

#endif /*MYCHARACTERLIST_H_*/
