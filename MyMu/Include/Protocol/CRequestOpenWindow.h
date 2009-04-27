#ifndef CREQUESTOPENWINDOW_H_
#define CREQUESTOPENWINDOW_H_
#include "Protocol/CBPacket.h"
#include "Protocol/SOpenDialog.h"

//clasa: CRequestOpenWindow
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

class CRequestOpenWindow:public CBPacket {
//	c3 05 30 37 1f
int id;			//id npc na ktorego kliknieto
public:
CRequestOpenWindow(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
	virtual ~CRequestOpenWindow(){};
	void debuild()
	{
		id=(*buff)[3].readI(false);
		std::cout << "Request open windod dla id: " << id << ".\n";
		_cl->Send(new SOpenDialog(0x01)); 
	
	}
};
#endif /*CREQUESTOPENWINDOW_H_*/
