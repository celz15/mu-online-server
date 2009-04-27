#ifndef CPICKUPITEM_H_
#define CPICKUPITEM_H_
#include "Protocol/CBPacket.h"


//clasa: CPickUpItem
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

class CPickUpItem:public CBPacket {
	int id;					//id przedmiotu do podniesienia
public:
CPickUpItem(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
	virtual ~CPickUpItem(){};
	void debuild()
	{
	id=(*buff)[3].readI(false);
	std::cout << "request pick up item id:" << id << "\n"; 	
	
	}
};
#endif
