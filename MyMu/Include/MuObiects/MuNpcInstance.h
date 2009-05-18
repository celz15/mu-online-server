#ifndef MUNPCINSTANCE_H_
#define MUNPCINSTANCE_H_

#include "MuObiects/MuCharacter.h"
#include "Task/Task.h"

class MuNpcInstance:public MuCharacter
{

  unsigned short n_ObjId;     //id w grze

protected:
  MuNpcInstance():MuCharacter()
  {
	
    setType(O_NPC); // npc ogulnie
	
  };
public:
  void setObjId(int id)
{
n_ObjId=id;
};
  int getObjId()
{
return n_ObjId;
};
 
 ~MuNpcInstance(){}

};
 
#endif /*MUNPCINSTANCE_H_*/
