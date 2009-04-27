#ifndef SNEWCHARACTERANSFER_H_
#define SNEWCHARACTERANSFER_H_

#include "Protocol/SBPacket.h"
#include "MuObiects/MuCharacterBase.h"

//clasa : SNewCharacterAnsfer
//h    -paczka budowan
class SNewCharacterAnsfer : public CSPacket
{
MuCharacterBase* _Chara;		//opis
int flag;						//flaga
int gdzie;						//gdzie pokazac
public:
	SNewCharacterAnsfer(MuCharacterBase* Chara,int f,int g):CSPacket()
	{
	_Chara=Chara;
	flag=f;
	gdzie=g;
		MyName="F301 - new character ansfer";
	};
	 ~SNewCharacterAnsfer(){};	
	HexBuff * build()
	{
	 unsigned char t[]=
    {
    	0xC1  ,0x2A  ,0xF3  ,0x01  , //NAG
    	0x01  ,							//FLAG
    	0x00  ,0x00  ,0x00  ,0x00  ,0x00  ,0x00  ,0x00  ,0x00  ,0x00  ,0x00  ,//NICK
    	0x04  , //GDZIE
     	0x01  , //KLASA
     	0x00  ,
     	0x20  ,0x00  ,0xFF  ,0xFF  ,
     	0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,
     	0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,0x00};
 	 	t[4]=flag ;
  	 (*h)[0].writeAC(t,43);
  	 (*h)[5].writeS(_Chara->getName());
  	 (*h)[15].writeC(gdzie); // slots of screen
  	 (*h)[16].writeI(_Chara->getLvl(),true); 
  	 (*h)[18].writeC(_Chara->getClass());
  	 (*h)[19].writeC(0x00); // gm,or blocked
  	 
  	 
  return h;
};
	
	
	
	
};


#endif /*SNEWCHARACTERANSFER_H_*/
