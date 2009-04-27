#ifndef MUITEMINSTANCE_H_
#define MUITEMINSTANCE_H_
#include "MuObiects/MuObiect.h"			//podstawowa klasa
#include "MuObiects/MuItemT.h"			//podstawa itemow
#include "IdFactory.h"					//auto id
#include "DB/BDItems.h"

class MuItemInstance:public MuObiect ,public MuItemT
{
	int _slot;			//pozycje jesli jest w inw lub stor itp
	int _window;			//gdzie jest
	int _price;				//cena za item w sklepie
	int _Wid;				//id wlasciciela ew kto zabil potwora i ma pierwszensteo do podniesienia
	unsigned char item[4];	//itemek
protected:
MuItemInstance()
{
	setMType(5);
	setOId(IdFactory());
};
public:
~MuItemInstance(){}

void setSlot(int p)
{
	_slot=p;
};
//void SetFromDB(DbitemBase * t)
//{
//	t->getItem(item);
//	_slot=t->getSlot();
//	_window=t->getWindowId();
//};
int getSlot()
{
	return _slot;
};



};


#endif /*MUITEMINSTANCE_H_*/
