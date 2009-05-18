#ifndef SPUTITEMININW_H_
#define SPUTITEMININW_H_
#include "Protocol/SBPacket.h"



  struct packPutItemInInwentory{
    PMSG_HEADA _head;
    unsigned char pos;
    ItemHex _hex;
    void set(unsigned char pos,ItemHex *hex)
    {
      _head.set(0xc3,sizeof (packPutItemInInwentory) , 0x22);
      pos=pos;
      memcpy(&_hex,hex,sizeof (ItemHex));
    };
  };

  //clasa : SPutItemInInwetory
  //h    -paczka budowana
    class SPutItemInInwetory : public CSPacket
    {
      unsigned char posi;
      ItemHex *_item;		//item do dodania
    public:
      SPutItemInInwetory(unsigned char pos,ItemHex *item):CSPacket()
      {
	posi=pos;
	_item=item;
	MyName="22 Put Item In inw";
      };
      ~SPutItemInInwetory(){};
      HexBuff * build()
      {    
	packPutItemInInwentory pack;
	pack.set(posi,_item);

	unsigned char *t;
	t = reinterpret_cast<unsigned char *> (&pack);
	(*h)[0].writeAC(t , sizeof(packPutItemInInwentory));
	return h;
      };
	
    };

#endif /*SPUTITEMININW_H_*/
