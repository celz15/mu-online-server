#include "MuObiects/MuMonsterInstance.h"
#include "MuObiects/MuPcInstance.h"
#include "Task/Task.h"
void MuMonsterInstance::RunMoveInst()
{
  // Si();
  if (movable){
    Task::Instance()->AddJobA ( _moveInst,3+(rand()%7)); // co 30 sec
  } 
};

void MobMove::Run()
{
  int newx=MySpot->getNewX(4,me->getX());
  int newy=MySpot->getNewY(4,me->getY());
  me->MoveTo(newx,newy);
  me->RunMoveInst();	
};

void MobRespown::Run()
{
  std::cout << "powrucilem : " << me->getOId() <<" na "<< (int)me->getX()<<","<<(int)me->getY()<<".\n";
  me->setX(_x);
  me->setY(_y);
  me->setNX(_x);
  me->setNY(_y);
  me->RestartHP();				//restarujemy hp
  me->setAtRespown(false); 
  me->setMovable(true);
  me->RunMoveInst();
};

void MobSI::Run()
{
  int time;
  switch (myStatus){
  case 0: time=RunAutoMove();break;  	//nic auto run
  case 1: time=RunScan(0);break;		//skan przeciwniow
  case 2: break;		//chodze
  case 3: break;		//atakuje	
  case 5: break;		//respownuje
  case 6: break;		//uciakem ?
  case 7: break;		//jestem atakowany
  };
  me->Si(time);
};
int MobSI::RunScan(int r)
{
  printf("In RunScan(int r)");
  std::vector<MuPcInstance * > lp; // lista pcinstance
  std::vector<MuObiect * >lo=me->getKnowsObiects();
  for(int a=0;a<lo.size();a++)
    if (lo[a]->getMType()==1)lp.push_back(static_cast<MuPcInstance*>(lo[a]));
  if(!lp.empty()){
    std::cout << "Znaleziono: " << lp.size()<<"\n";
    //ustawiamy cel:
    me->setTarget(lp[rand()%lp.size()]);
    myStatus=3; // atakuje
    return RunAtack(20);
  };
  return RunAutoMove(); //
};
	
int MobSI::RunAutoMove()
{
  printf("in RunAutoMove()");
  int newx=MySpot->getNewX(4,me->getX());
  int newy=MySpot->getNewY(4,me->getY());
  me->MoveTo(newx,newy);
  return 3+(rand()%7);
			
};
	
int MobSI::RunMove(int x,int y)
{
  me->MoveTo(x,y);
  return 1; // 1 swc
} 
int MobSI::RunHeal(int st)
{
  return 1;
};
int MobSI::RunRespown(int x,int y)
{
  return 1;
};
int MobSI::RunAtack(int idcalu)
{
  std::cout << "Atakuje: \n";
  //sprawdz czy jestes blisko celu
  int cx=me->getTarget()->getX();
  int cy=me->getTarget()->getY();
  me->IAtackU();
  myStatus=1; //skan
  //RunMove(me->getX(),me->getY());
  return 3;
};
