#include "MuObiects/MuObjectsPool.h"
#include "MuObiects/MuPcInstance.h"
#include "MuObiects/MuMonsterInstance.h"
#include "MuObiects/MuNpcInstance.h"
#include "MuObiects/MuViewPort.h"
#include "MuObiects/MuNpcTemplate.h"

#include <math.h>
void ObiectPool::initPoolData()
{
  for (int i = 0 ; i <=0xffff;i++)
    {
      _pool[i]=NULL; //sets empty flag
      _freeCels.push(i); // sets empty cels
    }
  printf ("|SYSTEM ObjPoool Init Succesfull\n");
}

ObiectPool::ObiectPool()
{
  sizeOfPointer=sizeof(MuObiect*);

  sizeOfPcInstance=sizeof(MuPcInstance);
  sizeOfMonsterInstance=sizeof(MuMonsterInstance);
  sizeOfNpcInstance=sizeof(MuNpcInstance);
  sizeOfItemInstance=sizeof(MuItemInstance);

  contOfMonsters=contOfPlayers=contOfNpcs=contOfItems=0;

}

ObiectPool* ObiectPool::_instance=NULL;
 ObiectPool* ObiectPool::getInstance()
{
  if(_instance==NULL)
    {
      _instance = new ObiectPool;
      _instance->initPoolData();
    }
  return _instance;
};
unsigned short ObiectPool::reserveId()
{
  unsigned short freeid =_freeCels.top();
  _freeCels.pop();
  return freeid;
}
void ObiectPool::returnId(unsigned short id)
{
  if(_pool[id] != NULL)
    {
      MuObiect *t = _pool[id];
      delete t;
      _pool[id] = NULL;
    };
  _freeCels.push(id);
}
ObiectPool::~ObiectPool()
{
}



MuMonsterInstance* ObiectPool::newMuMonsterInstance(MuNpcTemplate t,unsigned char _x ,unsigned char _y, unsigned char map)
{
  MuMonsterInstance * temp;
  int freeId= _freeCels.top();
  _freeCels.pop(); 
  temp= new MuMonsterInstance(t, _x,_y,map,freeId);
  _pool[freeId]=temp;
  contOfMonsters++;
  //printf ("|OBJECTPOOL Object %d Creted and Stored Succesfull \n",freeId);
  return temp;
}

MuPcInstance * ObiectPool::newMuPcInstance(unsigned short id )
{
  MuPcInstance *pc = new MuPcInstance();
  pc->setIndex(id);
  if(_pool[id]==NULL)
    {
      _pool[id]=pc;
      contOfPlayers++;
    }
  else
    printf ("Error in try to put object [Index:] in ObiectPool !!!\n",id);

  return pc;
}



MuViewPort ObiectPool::getDistance(unsigned short id1 , unsigned short id2,unsigned char dist)
{
  MuViewPort temp;
  temp.o_Index=id2;
  temp.o_dist=0xff;
  temp.c_State=0x00;
 register MuObiect * o1 = getObject(id1);
 register MuObiect * o2 = getObject(id2);
  if ((o1==NULL) || (o2 == NULL))
    {
      temp.o_Index =0x00;
      temp.o_dist=0xff;
      temp.c_State=0x04;
      printf("NULL :/\n");
      temp.PrintMe();
      return temp; 
    }
  else
    //obiects exists
    {
      if((o1->getPosX() == o2->getPosX()) && (o1->getPosX() == o2->getPosY()))
	{
	  temp.o_dist=0;
	}
      else
	{
	  //calcuate the distance
	  float fCalcX = (float)abs(o1->getPosX() - o2->getPosX());
	  float fCalcY = (float)abs(o1->getPosY() - o2->getPosY());      
	  temp.o_dist  = (int)sqrt((fCalcX * fCalcX) + (fCalcY * fCalcY));
	};
    }
  if (temp.o_dist<=dist) temp.c_State = MuViewPort::S_New;
  else temp.c_State=MuViewPort::S_ToForget;
  temp.o_Type  = o2->getType();
  temp.o_Index = id2;
  return temp;
  
};
  
