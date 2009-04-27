#ifndef CA0UNKOWNREQ_H_
#define CA0UNKOWNREQ_H_
#include "Protocol/CBPacket.h"
#include "Protocol/SA0UnkownRep.h"

//clasa: CA0UnkownReq
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

class CA0UnkownReq:public CBPacket {
	
public:
CA0UnkownReq(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
	virtual ~CA0UnkownReq(){};
	void debuild()
	{
	_cl->Send(new SA0UnkownRep());
	}
};
#endif /*CA0UNKOWNREQ_H_*/
