#include "MuObiects/MuMap.h"
#include "MuObiects/MuMonsterInstance.h"
#include "MuObiects/MuObjectsPool.h"
#include "Task/Task.h"
void MuMap::InitMonstersSpot()
{
  printf (" init monster function entry");
  if(_allSpotV.size()==0)
    {
      printf(" -- NO SPOT TO INIT --\n");
    }
  else
    {
      std::cout << _name<<": INITS MOBS SPOTS\n";
      
      for(int a=0;a<_allSpotV.size();a++)
	{
	  std::cout << "---INIT SPOT #"<<a<<"---.\n" ;
	  MuSpot * s=_allSpotV[a];
	  
	  for(int c=0;c<=s->getC()-1;c++)
	    {
	      MuMonsterInstance *mob=ObiectPool::getInstance()->
		newMuMonsterInstance(s->startX(),s->startY(),s->getR(),this,a);
	      //	
	      storeNewObiect(mob);
	      mob->RunMoveInst();
	    };
	  std::cout << "---INIT SPOT #"<<a<<" DONE---.\n\n";
	};
    };
};
