#ifndef CITEMMOVETOREQUEST_H_
#define CITEMMOVETOREQUEST_H_
#include "Protocol/CBPacket.h"
#include "MuObiects/MuItemT.h"
#include "Protocol/SItemMoveToAnsfer.h"
#include "Protocol/BaseStruct.h"

struct ItemMoveReq
{
  PMSG_HEADA    head;
  unsigned char windowFrom;
  unsigned char slotFrom;
  ItemHex       item;
  unsigned char windowTo;
  unsigned char slotTo;
};

//clasa: CItemMoveToRequest
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex 

class CItemMoveToRequest:public CBPacket {
  unsigned char _item[4];		//item to move
  int _slotFrom;				//from slot
  int _windFrom;				//from window id
  int _slotTo;				//to slot
  int _windTo;				//to window id
public:
  CItemMoveToRequest(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
  virtual ~CItemMoveToRequest(){};
  void debuild()
  {
	  
    unsigned char * pbuff = buff->getPointer();
    ItemMoveReq * p = (ItemMoveReq *)pbuff;
    MuHandInwentory * i = _cl->getCharactersInwentory();
    if((p->windowFrom == WId_Inwentory)&& (p->windowTo==WId_Inwentory))
      {
	ItemInInwentory * itemToMove= i->getItemFrom(p->slotFrom);
	if(itemToMove!=NULL)
	  {
	    if (memcpy(&p->item,&itemToMove->inw_ItemHex,sizeof(ItemHex))==0)
	      {
		//todo
	      }
	    else
	      {
		printf("Requared Item to move from position [d] its not this same from inwentory\n",
		       p->slotFrom);
	      };
	  }
	else
	  {
	    printf("Requared Item to move from position [%d] dosnt exxist in inwentory!!\n"
		   ,p->slotFrom); 
	  };

	//c3 0c 24 00 00 21 00 14 00 f4 00 0c
	//             0x21 00 14 00 00
	_windFrom=(*buff)[3].readC();
	_slotFrom=(*buff)[4].readC();
	
	_item[0]=(*buff)[5].readC();
	_item[1]=(*buff)[6].readC();
	_item[2]=(*buff)[7].readC();
	_item[3]=(*buff)[8].readC();
	_item[4]=(*buff)[9].readC();
	
	_windTo=(*buff)[10].readC();
	_slotTo=(*buff)[11].readC();
	
	std::cout<< "Item Move request from window " << _windFrom <<
	  " from slot " << _slotFrom << " to window " << _windTo
		 << " on slot " << _slotTo << " .\n";
	_cl->Send(new SItemMoveToAnsfer(_windTo,_slotTo,_item));			
	
      }
  }
};
#endif /*CITEMMOVETOREQUEST_H_*/
