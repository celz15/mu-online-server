#include "MuObiects/MuCharacter.h"
#include "MuObiects/MuPcInstance.h"
#include "MuObiects/MuMaps.h"
void MuCharacter::broadcastPacket(SBPacket *p)
{
  unsigned short id=0;;
  //if(o_ViewPort->getViewSize()!=-1) //jesli nie ma nic w kolejce to koncz
      for(int i=0; i < o_ViewPort->getViewSize(); i++)
	{  
	  if((*o_ViewPort)[i].c_State != MuViewPort::S_Empty)
	    {
	     
	      if((*o_ViewPort)[i].o_Type==O_Player)//jesli jestm graczem
		{
		  printf ("......i:%d z :%d\n",i,o_ViewPort->getViewSize());
		  printf("---->found playera in brodcast package \n");
		  id=(*o_ViewPort)[i].o_Index;
		  MuObiect * o = ObiectPool::getInstance()->getObject(id);
		  if(o!=NULL) 
		    {
		      printf("OBJECT[%d] BRODCATING MSG: [%s] to Player[%d]\n",
			     getIndex(),p->getName().c_str(),(*o_ViewPort)[i].o_Index);
		      (static_cast<MuPcInstance*>(o))->Send(p);
		    }
		  else
		    {
		      printf("ObiectPool returned empty obiect for Id(%d)\n",id);
		    }
		} 
	    };

	};
	
};

void MuCharacter::CheckViewPort()
  {
    MuMaps::getInstance()->getMap(getPosMapNb())->updatePortView(getViewPort());
    checkToForgetInViewPort();
    checkNewInViewPort();
  };
  //std::cout <<"przeszuklem: " <<i<<".\n";
		



