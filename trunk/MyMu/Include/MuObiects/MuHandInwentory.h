#ifndef MUHANDINWENTORY_H_
#define MUHANDINWENTORY_H_
#include "MuObiects/MuItemT.h"
class MuHandInwentory{
	protected:
	int item_c; 					//ile mamy itemow
	MuItemInInwentory * inw[75];		//tabela inw 
	public:
	MuHandInwentory()
	{
	item_c=0;
	for (int a=0;a<=75;a++)
	inw[a]=NULL;					//nulujemy inw
	};
	~MuHandInwentory(){};
	
	MuItemInInwentory* getImp()		//pobieramy impa
	{
		return inw[1];
	};
	MuItemInInwentory* getHelm()
	{
		return inw[2];
	};
	MuItemInInwentory* getWings()
	{
		return inw[3];
	};
	MuItemInInwentory* getLWapon()
	{
		return inw[4];
	};
	MuItemInInwentory* getPedant()
	{
		return inw[5];
	};
	MuItemInInwentory* getArmur()
	{
		return inw[6];
	}
	MuItemInInwentory* getRWapon()
	{
		return inw[7];
	}
	MuItemInInwentory* getGuard()
	{
		return inw[8];
	}
	MuItemInInwentory* getPants()
	{
		return inw[9];
	}

	MuItemInInwentory* getLRing()
	{
		return inw[10];
	}

	MuItemInInwentory* getRRing()
	{
		return inw[11];
	}
		MuItemInInwentory* getBoots()
	{
		return inw[12];
	}
	
	bool putIn(MuItemInInwentory *i,int sl)
	{
		if (inw[sl]==NULL)
		{
			item_c++;
			inw [sl]=i;
			return true;
		} else return false;
	};
	MuItemInInwentory* getItem(int pos)
	{
		return inw[pos];
	};
	int getItemC(){return item_c;};
	void LoadAllInwentory()
	{
		
	};
	void SaveAllInwentory()
	{
	};
	void LoadXItem(int slot)
	{
	};
	void SaveXItem(int slot){
	};
	void MoveItem(int from  ,int to)
	{
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
