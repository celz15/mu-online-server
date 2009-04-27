#include "MuObiects/MuObjectsPool.h"
#include "MuObiects/MuPcInstance.h"
#include "MuObiects/MuMonsterInstance.h"
#include "MuObiects/MuNpcInstance.h"

void ObiectPool::initPoolData()
{
  for (int i = 0 ; i <=0xffff;i++)
    {
      _pool[i]=NULL; //sets empty flag
      _freeCels.push(i); // sets empty cels
    }
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

ObiectPool::~ObiectPool()
{
}
MuMonsterInstance* ObiectPool::newMuMonsterInstance(unsigned char _x,unsigned char _y ,unsigned char _r, MuMap *m , int nrsp)
{
  MuMonsterInstance * temp;

  temp= new MuMonsterInstance(_x,_y,_r,m,nrsp);
  int freeId= _freeCels.top();
  temp->setOId(freeId);
  _pool[freeId]=temp;
  _freeCels.pop();
  contOfMonsters++;
  return temp;
}

MuPcInstance * ObiectPool::newMuPcInstance()
{
  return new MuPcInstance();
}
