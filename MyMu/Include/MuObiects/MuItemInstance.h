#ifndef MUITEMINSTANCE_H_
#define MUITEMINSTANCE_H_

#include "MuObiects/MuObiect.h"			//podstawowa klasa
#include "MuObiects/MuItemT.h"			//podstawa itemow
#include "IdFactory.h"					//auto id
#include "DB/BDItems.h"

class MuItemInstance:public MuObiect 
{
  unsigned short  i_dropProtect;
  ItemHex         i_item;
protected:
  MuItemInstance()
  {
    setType(O_Item);
    setIndex(IdFactory());
  };
public:
  ~MuItemInstance(){}
  ItemHex* getItem()
  {
    return &i_item;
  };
  
  void setItem(ItemHex * h)
  {
    memcpy (&i_item , h , sizeof(ItemHex));
  };

};


#endif /*MUITEMINSTANCE_H_*/
