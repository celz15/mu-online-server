#ifndef MUHANDINWENTORY_H_
#define MUHANDINWENTORY_H_
#include "MuObiects/MuItemT.h"


class MuHandInwentory
{
protected:
  unsigned long _map; // 8x8 bits 
  ItemInInwentory * inw[75];		//tabela inw 
public:
  MuHandInwentory()
  {
     for (int a=0;a<=75;a++)
      inw[a]=NULL;					//nulujemy inw
  };
  ~MuHandInwentory(){};
	
  ItemInInwentory* getImp()		//pobieramy impa
  {
    return inw[1];
  };
  ItemInInwentory* getHelm()
  {
    return inw[2];
  };
  ItemInInwentory* getWings()
  {
    return inw[3];
  };
  ItemInInwentory* getLWapon()
  {
    return inw[4];
  };
  ItemInInwentory* getPedant()
  {
    return inw[5];
  };
  ItemInInwentory* getArmur()
  {
    return inw[6];
  }
  ItemInInwentory* getRWapon()
  {
    return inw[7];
  }
  ItemInInwentory* getGuard()
  {
    return inw[8];
  }
  ItemInInwentory* getPants()
  {
    return inw[9];
  }

  ItemInInwentory* getLRing()
  {
    return inw[10];
  }

  ItemInInwentory* getRRing()
  {
    return inw[11];
  }
  ItemInInwentory* getBoots()
  {
    return inw[12];
  }
	
  bool putIn(ItemInInwentory *i, int sl)
  {
    return true;
  };
};
//11   22   3333 1 - imp 2 helm 3 wings
//44 5 66    777 4 lwapon 5 pedant 6 armur
//44   66    777 7 rwapon 8 guar   a lring
//44   66    777 9 pants  b rring c boots
//88 a 99 b  ccc
//
//1 2 3 4 5 6 7 8
/****personal inw 8x8**********
 * # # # # # # # #
 * # # # # # # # #
 * # # # # # # # #
 * # # # # # # # #
 * # # # # # # # #
 * # # # # # # # #
 * # # # # # # # #
 * # # # # # # # #
 *******************************/
	
#endif /*MUHANDINWENTORY_H_*/
