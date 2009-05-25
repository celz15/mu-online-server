#ifndef SITEMLIST_H_
#define SITEMLIST_H_
#include "Protocol/SBPacket.h"
#include "Protocol/BaseStruct.h"
#include "MuObiects/MuItemT.h"
struct ItemNode
{
  unsigned char slot;
  ItemHex       item;
};
struct msgItemList
{
  PMSG_HEADB  head;
  unsigned char code;
  unsigned char ItemCount;
  ItemNode    items[75];
};

//clasa : SItemList
//h    -paczka budowana
class SItemList : public CSPacket
{
  std::vector<ItemInInwentory*> _list;
public:
  SItemList(std::vector<ItemInInwentory*> list):CSPacket()
  {
    _list=list;
    MyName="OpisPaczki";
  };
  ~SItemList(){};
  HexBuff * build()
  {
    msgItemList pack;
    int size = _list.size()*sizeof(ItemNode)+sizeof(PMSG_HEADB)+1;
    pack.head.set(0xc4,size,0xf3);
    pack.code=0x10;
    if(_list.empty())pack.ItemCount=0;
    else pack.ItemCount=_list.size();
    for( int i =0 ; i< _list.size();i++)
      {
	printf("add item to pack on pos[%d]\n",_list[i]->inw_slot);
	pack.items[i].slot=_list[i]->inw_slot;
	memcpy(&pack.items[i].item,&_list[i]->inw_ItemHex,sizeof(ItemHex));
      };
    
    
    //    unsigned char  t[]={
    //  0xc4 ,0x00 ,0x24 ,0x6b ,0x66 ,0x28 ,0x7a ,0xd1 ,0xf7 ,0xf6 ,0x57 ,0xf0 ,0xc3 ,0xf6 ,0x5d ,0x39 ,0x2c ,0xe6 ,0x9f ,0xba ,0x62 ,0x58 ,0xa4 ,0x2a ,0x1f ,0xf0 ,0x0d ,0x30 ,0x85 ,0x1c ,0x99 ,0x92 ,0x41 ,0xe0 ,0x00 ,0x3a 
      //0xc4 ,0x00 ,0x17 ,0xf3 ,0x10 ,0x03, 
      //0x0c ,0xe3 ,0x00 ,0x00 ,0x80 ,0x00, 
      //0x0d ,0xea ,0x00 ,0x00 ,0x80 ,0x00, 
      //0x0e ,0x21 ,0x00 ,0x14 ,0x00 ,0x00
  
  
  (*h)[0].writeAC((unsigned char*)(&pack),size);
    return h;
  };
	
};

#endif /*SITEMLIST_H_*/
