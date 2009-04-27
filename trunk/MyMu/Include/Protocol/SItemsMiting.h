#ifndef SITEMSMITING_H_
#define SITEMSMITING_H_
#include "Protocol/SBPacket.h"
#include "MuObiects/MuItemInstance.h"
#include <vector>
using std::vector;

//clasa : SItemMiting
//h    -paczka budowana
class SItemMiting : public CSPacket
{
vector<MuObiect *> _newList;		//lista itemow na ziemi
int off;
public:
	SItemMiting(vector<MuObiect *> newList):CSPacket()
	{
		off=0;
		_newList=newList;
		MyName="20 Meet Items On ground";
	};
	 ~SItemMiting(){};
	HexBuff * build()
	{
		head();
		std::cout << "ilosc i" << _newList.size();
		for (int i=0;i<_newList.size();i++)
			sub(static_cast<MuItemInstance*>(_newList[i]));
		(*h)[off].writeC(0x00);
		(*h)[off+1].writeC(0x00);
	
	return h;
	};
	void head()
	{
		unsigned char t[]={0xC2,0x00,0x0E,0x20,0x01};
		(*h)[0].writeAC(t,4);
		(*h)[1].writeI(calculateSize(),false);			//ustawiamy wielkosc
		(*h)[4].writeC(_newList.size());				//ustawiamy ilosc sub wpaczce
		off=5;											//offset dla ssub

	};
	void sub(MuItemInstance * i)
	{
	unsigned char t[]={0x81,0x26,0x8D,0xA8,0xC4,0x00,0x03,0x80};
	unsigned char it[5];
	int id=i->getOId();								//item
	i->get4BItem(it);									//pobieramy 5b itemu
	(*h)[off+0].writeAC(t,7);							//
	(*h)[off+0].writeI(id,false);				//id
	(*h)[off+2].writeC(i->getX());						//xpos
	(*h)[off+3].writeC(i->getY());						//ypos
	(*h)[off+4].writeAC(it,4);							//item
	off+=8;												//zwiakszamy off o wielkosc sub
	};
	
	int calculateSize()
	{
		return 5+(8*_newList.size()); // narazie
	};
};

#endif /*SITEMSMITING_H_*/
