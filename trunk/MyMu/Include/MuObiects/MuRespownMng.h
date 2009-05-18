#pragma once

#include <list>
#include "MuObiect/MuMonsterInstance.h"

using std::list;

struct RespownNode
{
  MuMonsterInstance * mon;
  unsigned long time;
};

class MuRespownMng
{

  list <RespownNode > _respownList;

public:
  void addToRespown(MuMonsterInstance * m, unsigned long time)
  {
    RespownNode node;
    node.mon=m;
    node.time = time(0) + time;     
  };

  void Run()
  {
    for (list<RespownNode>::iterator i = _respownList.begin() ; i!=_respownList.end(); i++)
      {
	RespownNode r = (RespownNode)(*i);
	if (r.time >= time(0))
	  {
	    
	  }
      }
  };
}
