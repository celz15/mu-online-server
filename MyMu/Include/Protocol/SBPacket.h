#ifndef SBPACKET_H_
#define SBPACKET_H_
#include <iostream>
#include "HexBuffer/HexBuffer.h"
class SBPacket
{
protected:
  std::string MyName;
  HexBuff *h;
public:
  SBPacket();
  SBPacket(HexBuff *_h){h=_h;};
  virtual ~SBPacket();
  virtual HexBuff* build()=0;
  void wyswietl();
  virtual void printDesc(){std::cout << MyName << "\n";};
  std::string getName()
  {
    return MyName;
  };

};

class CSPacket:public SBPacket
{
protected:
	
public:
  CSPacket():SBPacket(){};
  CSPacket(HexBuff *h):SBPacket(h){};
  virtual	~CSPacket(){};
  virtual HexBuff* build()=0;
	
	
  virtual void mC1Header(unsigned char ptyp,int size);
  virtual void mC2Header(unsigned char ptyp,int size);
  virtual void mC3Header(unsigned char ptyp,int size);
  virtual void mC4Header(unsigned char ptyp,int size);
  //twozenie z podwujnych typow
  virtual void mC1Header(unsigned char ptyp,unsigned char p1typ,int size);
  virtual void mC2Header(unsigned char ptyp,unsigned char p1typ,int size);
  virtual void mC3Header(unsigned char ptyp,unsigned char p1typ,int size);
  virtual void mC4Header(unsigned char ptyp,unsigned char p1typ,int size);
	
};
	

#endif /*SBPACKET_H_*/
