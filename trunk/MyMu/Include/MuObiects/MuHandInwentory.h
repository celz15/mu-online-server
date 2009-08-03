#ifndef MUHANDINWENTORY_H_
#define MUHANDINWENTORY_H_
#include "MuObiects/MuItemT.h"

enum WindowId
{
	WId_Inwentory = 0x00, WId_Vault = 0x02, WId_Trade = 0x80
};

class MuHandInwentory
{
protected:
	unsigned char _map[7]; // 8x8 bits map
	ItemInInwentory * inw[75]; //tabela inw
public:
	MuHandInwentory()
	{
		for (int a = 0; a <= 75; a++)
			inw[a] = NULL; //nulujemy inw
	}
	~MuHandInwentory()
	{
	}


	ItemInInwentory* getImp() //pobieramy impa
	{
		return inw[1];
	}
	ItemInInwentory* getHelm()
	{
		return inw[2];
	}
	ItemInInwentory* getWings()
	{
		return inw[3];
	}
	ItemInInwentory* getLWapon()
	{
		return inw[4];
	}
	;
	ItemInInwentory* getPedant()
	{
		return inw[5];
	}
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

	bool putItemInInwentory(ItemInInwentory *it)
	{

		if (inw[it->inw_slot] != NULL)
			return false;
		inw[it->inw_slot] = it;
		if (it->inw_slot > 12)
			updateItemMap(it->inw_ItemInfo->i_InfoHight,
					it->inw_ItemInfo->i_InfoLenght, getXFromArrayPos(
							it->inw_slot), getYFromArrayPos(it->inw_slot));
		return true;
	}

	bool addItemToInwentory(ItemInInwentory *it)
	{
		unsigned char h = it->inw_ItemInfo->i_InfoHight;
		unsigned char l = it->inw_ItemInfo->i_InfoLenght;
		int fposx = -1;
		int fposy = -1;

		for (int i = 0; i <= 8 - l; i++)
		{
			fposx = checkInX(i, h, l);
			if (fposx != -1)
			{
				//printf ("found in %d , %d \n",posx,i);
				fposy = i;
				break;
			};
		};

		if ((fposx == -1) || (fposy == -1))
			return false;
		else
		{
			int off = posXYtoArrayPos(fposx, fposy);
			inw[off] = it;
			it->inw_slot = off;
			return true;
		};
		return false;
	}
	std::vector<ItemInInwentory *> getAsVector()
	{
		std::vector<ItemInInwentory*> list;
		for (int i = 0; i <= 75; i++)
			if (inw[i] != NULL)
				list.push_back(inw[i]);
		return list;
	}

	void updateItemMap(unsigned char h, unsigned char l, unsigned char x,
			unsigned char y)
	{
		unsigned char *tmap = new unsigned char[h - 1];
		for (int i = 0; i < h; i++)
			tmap[i] = 0xffff << 8 - l;

		for (int i = 0; i < h; i++)
			_map[i + y] |= tmap[i] >> x;
	}

	int checkInX(unsigned char y, unsigned char h, unsigned char l)
	{
		unsigned char *tmap = new unsigned char[h - 1];
		for (int i = 0; i < h; i++)
			tmap[i] = 0xffff << 8 - l;

		for (int i = 0; i <= 8 - l; i++)
		{
			unsigned char ret = checkOnPos(i, y, h, tmap);
			if (ret == 0)
				return i;

		};
		return -1;
	}

	unsigned char posXYtoArrayPos(int x, int y)
	{
		return 12 + (y * 8) + x;
	}
	unsigned char getXFromArrayPos(unsigned char pos)
	{
		return (pos - 12) % 8;
	}

	unsigned char getYFromArrayPos(unsigned char pos)
	{
		return (unsigned char) ((pos - 12) / 8);
	}

	unsigned char checkOnPos(unsigned char x, unsigned char y, unsigned char h,
			unsigned char *tmap)
	{
		unsigned char ret = 0;
		for (int i = 0; i < h; i++)
			ret |= _map[i + y] & tmap[i] >> x;
		return ret;
	}

	void printBitMap()
	{
		for (int i = 0; i <= 7; i++)
		{
			for (int j = 0; j < sizeof(unsigned char) * 8; j++)
			{
				printf("%d", (_map[i] >> sizeof(unsigned char) * 8 - 1 - j) % 2);
			}
			printf("\n");
		};
	}
	ItemInInwentory * getItemFrom(unsigned char pos)
	{
		return inw[pos];
	}

	void PrintMe()
	{

		for (int i = 0; i <= 75; i++)
		{
			if (inw[i] != NULL)
				printf("SLOT[%d] Item[%s]\n", i,
						inw[i]->inw_ItemInfo->i_InfoName);
		}
	}
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
