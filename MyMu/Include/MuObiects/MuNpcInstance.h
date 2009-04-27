#ifndef MUNPCINSTANCE_H_
#define MUNPCINSTANCE_H_

#include "MuObiects/MuCharacter.h"
#include "Task/Task.h"

class MuNpcInstance:public MuCharacter
{
	//obiekt sie potrafi sam przesuwac
int _id; 					//id w grze /rasa potwora/postaci

protected:
MuNpcInstance():MuCharacter()
{
	
	setMType(3); // npc ogulnie
	
};
public:
void setId(int id){_id=id;};
int getId(){return _id;};
~MuNpcInstance(){}
//virtual void CheckStatus(){};
};
 
#endif /*MUNPCINSTANCE_H_*/
