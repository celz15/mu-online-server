#ifndef CCHANGEDIRECTIONORSTATUS_H_
#define CCHANGEDIRECTIONORSTATUS_H_
#include "Protocol/CBPacket.h"
#include "Protocol/SChangeDirectionOrStatus.h"


//clasa: CChangeDirectionOrStatus
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

class CChangeDirectionOrStatus:public CBPacket {
	
public:
CChangeDirectionOrStatus(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
	virtual ~CChangeDirectionOrStatus(){};
	void debuild()
	{
	unsigned char nd=(*buff)[3].readC(); 		//new direction
	unsigned char ns=(*buff)[4].readC();		//new status
	std::cout << "Change direction: " << (int)nd<< " OR status: " << (int) ns << "\n";
	_cl->getActiveCharacter()->setPosHead(nd);
	_cl->getActiveCharacter()->setPosStatus(ns);
	_cl->getActiveCharacter()->broadcastPacket(new SChangeDirectionOrStatus(ns,nd) ); 
	
	}
	
};
#endif /*CCHANGEDIRECTIONORSTATUS_H_*/
