#ifndef CUSELVLUPPOINTS_H_
#define CUSELVLUPPOINTS_H_
#include "Protocol/CBPacket.h"
#include "MuObiects/MuPcInstance.h"
#include "Protocol/SIncraseStatAnsfer.h"

//clasa: CUseLvlUpPoints
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

class CUseLvlUpPoints:public CBPacket {
	int tsp; 	//typ sp
	
public:
CUseLvlUpPoints(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
	virtual ~CUseLvlUpPoints(){};
	void debuild()
	{
		MuPcInstance *c=_cl->getActiveCharacter();
		tsp=(*buff)[4].readC();
	switch(tsp)
	{
		case 0x00:
		{
			if(c->decLp())
			{
			c->incStr();
			std::cout << "Incrase str.\n";
			c->Send(new SIncraseStatAnsfer(true,0,0,0));
			}else
			c->Send(new SIncraseStatAnsfer(false,0,0,0));
			
		};break;
		case 0x01:
		{
			if(c->decLp())
			{
			c->incAgl();
			std::cout << "Incrase agi.\n";
			c->Send(new SIncraseStatAnsfer(true,1,0,0));
			}else
			c->Send(new SIncraseStatAnsfer(false,1,0,0));
		};break;
		case 0x02:
		{
			if(c->decLp())
			{
			c->incVit();
			std::cout << "Incrase vit.\n";
			c->Send(new SIncraseStatAnsfer(true,2,0,0));
			}else
			c->Send(new SIncraseStatAnsfer(false,2,0,0));
		};break;
		case 0x03:
		{
			if(c->decLp())
			{
			c->incEnr();
			std::cout << "Incrase enr.\n";
			c->Send(new SIncraseStatAnsfer(true,3,0,0));
			}else
			c->Send(new SIncraseStatAnsfer(false,3,0,0));
		};break;
		
		default : std::cout << "unknown : " << (int) tsp << "\n";
	};
	c->UpdateMaxims();
	c->updateMaxLive();

	};
};
#endif /*CUSELVLUPPOINTS_H_*/
