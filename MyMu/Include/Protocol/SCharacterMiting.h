#ifndef SCHARACTERMITING_H_
#define SCHARACTERMITING_H_
#include "Protocol/SBPacket.h"
#include "MuObiects/MuPcInstance.h"
//clasa : SCharacterMiting
//h    -paczka budowana
class SCharacterMiting : public CSPacket
{
vector<MuObiect*> _newList;		//lisat postaci spotkanych
 int off;
public:
	SCharacterMiting(vector<MuObiect*> list):CSPacket()
	{

	_newList=list;
		MyName="12 meetcharacter";
	};
	 ~SCharacterMiting(){};
	HexBuff * build()
	
	{
		_head();
	for(int a=0;a<_newList.size();a++)
	sub(
		(static_cast<MuPcInstance*> (_newList[a]))->getName(),
		(static_cast<MuPcInstance*> (_newList[a]))->getOId(),
		(static_cast<MuPcInstance*> (_newList[a]))->getNewX(),
		(static_cast<MuPcInstance*> (_newList[a]))->getNewY(),
		(static_cast<MuPcInstance*> (_newList[a]))->getX(),
		(static_cast<MuPcInstance*> (_newList[a]))->getY()
		);
		(*h)[off].writeC(0x00);
	return h;
	};
	void _head()
	{
		int ile=_newList.size(); // jesli jest 1 wedy zaczynamy od 0
		unsigned char t[]={0xc2,0x00,0xFF,0x12,0xFF};
		(*h)[0].writeAC(t,4);
		(*h)[1].writeI(5+(ile*35),false);// wielkosc 2b
		(*h)[4].writeC(ile);
		off=5;
	}
	
	void sub(std::string nick,int id,int ox,int oy,int x,int y)
	{
     unsigned char t[]={
    0x00  ,0x00  ,0x90  ,0x7C  ,0x60  ,0xA8  ,0xFF  ,0xF1  ,0x11  ,0x1F,  
    0x12  ,0x48  ,0x03  ,0x84  ,0x00  ,0x00  ,0x00  ,0x00  ,0x00  ,0x00,  
    0x00  ,0x00  ,0x00  ,0x00  ,0x00  ,0x00  ,0x00  ,0x00  ,0x00  ,0x00,  
    0x91  ,0x79  ,0x13  ,0x00 };
 	
  		//:c2 00 11 13 01 00 59 00 ee 00 00 82 7f 82 7f 10 00
  		
  		(*h)[off+0].writeAC(t,34);
  		(*h)[off+0].writeI(id,false);
  		
  		(*h)[off+2].writeC(ox);
  		(*h)[off+3].writeC(oy);
  		
  		(*h)[off+31].writeC(x);
  		(*h)[off+32].writeC(y);
  		
  		(*h)[off+20].writeS(nick);
  		off+=34;
  		
  };	
	
	
};

#endif /*SCHARACTERMITING_H_*/
