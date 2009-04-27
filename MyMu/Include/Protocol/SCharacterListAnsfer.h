#ifndef SCHARACTERLISTANSFER_H_
#define SCHARACTERLISTANSFER_H_

#include "SBPacket.h"
#include "MuObiects/MyCharacterList.h"
#include "Protocol/BaseStruct.h"
#include <string.h>
struct CharacterListSub
{
  unsigned char m_uScreenPosition;
  char m_sName[10];
  unsigned char m_uUnk; // lvl high byte ?
  unsigned char m_uLvl;
  unsigned char m_uCtrCode;
  unsigned char m_uClass;
  unsigned char m_uItems[18];
  //some usefull functions;

  void setDefault(unsigned char pos,char * name,unsigned short lvl , unsigned char clas )
  {
    memcpy(name, &m_sName,10);
    m_uUnk = HIBYTE(lvl);
    m_uLvl = LOBYTE(lvl);
    m_uCtrCode=0x00;
    m_uScreenPosition=pos;
    m_uClass=clas;
    //todo fix that its wrong !!!
    unsigned char t[]= {
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x01,0x00,0x00,0x10,0xff,0xff,0xff,0xff,0x00,
      0x00,0x00,0xf8,0x00,0x00};
    memcpy(&m_uItems, &t,18);
       
  }

};


struct CharacterList
{
  PMSG_HEADA m_Head;
  unsigned char m_uSubType;
  unsigned char m_uAvailbleClases;
  unsigned char m_uZero2;
  unsigned char m_uCharacterCount;
  CharacterListSub m_Characters[5];
};

class SCharacterListAnsfer : public CSPacket
{
  int offset;								//offset w paczce budowanej
  MyCharacterList * list; 				//wskaznik do posiadanych postaci
 public:
  SCharacterListAnsfer(MyCharacterList *my):CSPacket()
	{
	  offset=0;
	  list=my;
	  MyName="SC F300 character list ansfer";
	};
  virtual ~SCharacterListAnsfer(){};
	
  
  // buduje naglowek listy postaci
  void _buildHeader()
    {
      
      int _cCount=list->getCharacterCount();		//pobieram ilosc postaci
      
      unsigned char t[]={0xc1, 0xff, 0xf3, 0x00, 0x04, 0x00, 0xff};
      t[6]=_cCount;					// wpisujemy ilosc postaci
      t[1]=7+(_cCount*28); 			// wielkosc przyszlej paczki
      (*h)[0].writeAC(t,6); 			// temp paczke zapisyjemy do paczki
      offset=7;
      
    };
  
  // budujemy sub postacie:
  void _buildSub(int nr)
    {
      
      MuCharacterBase *ch;
      ch=list->getCharacter(nr);
      
      
      
      unsigned char t[]=	{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x00, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
	0x00, 0x00, 0xf8, 0x00, 0x00, 0x00 };
      
      t[0]=nr;				 						// nr chara zaczyna sie od 0
      
      (*h)[offset].writeAC(t,27);			 			// zapisuemy paczeke do wlasciwego buffora 
      
      (*h)[offset+1].writeS(ch->getName()); 			// nick
      
      (*h)[offset+12].writeI(ch->getLvl(),true);		// zapisujemy lvl
      
      (*h)[offset+15].writeC(ch->getClass());  		// zapisujemy klase
      
      offset+=28;										// zwiekszamy offset 
    };
  
  
  HexBuff *build()
    {
      
      int count=list->getCharacterCount();		// ilosc postaci
      
      _buildHeader(); 							// budujemy nagowek paczki
      
      for(int i=0;i<count;++i)
	{
	  
	  _buildSub(i); 							// budujemy sub cinformacje paczki
	};	
      (*h)[offset].writeC(0x00);							// 0x00 na koncu
      return h;
    }
  
  
};

#endif /*SCHARACTERLISTANSFER_H_*/
