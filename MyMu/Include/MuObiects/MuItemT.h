#ifndef MUITEMT_H_
#define MUITEMT_H_
#include "HexBuffer/HexBuffer.h"

//troche predefinicji itemow
#define IT_OPTp4 0x01 // 00000001b
#define IT_OPTp8 0x02 // 00000010b
#define IT_LUCK  0x04 // 00000100b
#define IT_SKILL 0x80 // 10000000b
#define IT_LVL(x) (x)>>4 // 00001000b 1 lvl
#define IT_OPT(x) (x)   // 1..3
////exe bits		  
#define EXEOPT1   0x01 // 00000001b
#define EXEOPT2   0x02 // 00000010b
#define EXEOPT3   0x04 // 00000100b
#define EXEOPT4   0x08 // 00001000b
#define EXEOPT5   0x10 // 00010000b
#define EXEOPT6   0x20 // 00100000b
#define IT_p16    0x40 // 01000000b
#define IT_LONGID 0x80 // 10000000b

struct ItemHex
{
  unsigned char index;
  unsigned char duration;
  unsigned char options;
  unsigned char eoptions;
  unsigned char aoptions;
  void setIndex(unsigned char _grup,unsigned char _index)
  {
    index = 0x00;
    duration = 0x00;
    options = 0x00;
    eoptions=0x00;
    aoptions=0x00;
    index=_grup  << 4;
    index|=_index & 0x0F; 
    if((_grup <<4)!=0) 
      {
	eoptions|=IT_LONGID;
      }
  };
void  makeItem(unsigned char _grup, unsigned char _index,
	   unsigned char _lvl,
	   unsigned char _duration,
	   unsigned char _options,
	   unsigned char _eoptions,
	   unsigned char _aoptions)
  {
    
    setIndex(_grup,_index);
    duration = _duration;
    options|=(_lvl>>4);
    options|=_options;
    eoptions|=eoptions;
    aoptions|=_aoptions;
  };
};

struct ItemInInwentory
{
  unsigned char slot;
  ItemHex hexData;
};


    // fscanf("%d",_grup);
    //base stats
    // fscanf("%d %d %d %d %d",index,x,y,serial,serial1,drop);
    //fscanf("\"%s\" %d",name , droplvl}; 
    //grup 0
    //fscanf("%d %d %d %d %d %d %d %d %d %d %d",
    //   DamMin,DamMax,Speed,Dur,MDur,Str,Agil,DWSM,DKBK,EME,MG);
    //grup 1
    //fscanf(


 
 
#endif /*MUITEMT_H_*/
