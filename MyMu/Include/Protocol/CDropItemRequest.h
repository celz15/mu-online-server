#ifndef CDROPITEMREQUEST_H_
#define CDROPITEMREQUEST_H_
#include "Protocol/CBPacket.h"
#include "Protocol/SDropItemAnsfer.h"

//clasa: CDropItemRequest
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

class CDropItemRequest:public CBPacket {
	int _slot;			//slot to drop item
	int _x;				//x to drop item
	int _y;				//y pos to drop item
public:
CDropItemRequest(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
	virtual ~CDropItemRequest(){};
	void debuild()
	{
	
	_x=(*buff)[3].readC();
	_y=(*buff)[4].readC();
	_slot=(*buff)[5].readC();
	std::cout << "Drop item rquest trom slot " << _slot << " to pos : (" << _x << "," << _y<< ").\n";
	_cl->Send(new SDropItemAnsfer(false,_slot));
	}
};
#endif /*CDROPITEMREQUEST_H_*/
