#include "MuObiects/MuObjectsPool.h"
#include "MuObiects/MuPcInstance.h"
#include "MuObiects/MuMonsterInstance.h"
#include "MuObiects/MuNpcInstance.h"
#include "MuObiects/MuViewPort.h"
#include "MuObiects/MuNpcTemplate.h"
#include <utility>

#include <math.h>
void ObiectPool::initPoolData()
{
	for (int i = 0; i <= 0xffff; i++)
	{
		_pool[i] = NULL; //sets empty flag
		_freeCels.push(i); // sets empty cels
	}
	printf("|SYSTEM ObjPoool Init Succesfull\n");
}

ObiectPool::ObiectPool()
{
	sizeOfPointer = sizeof(MuObiect*);

	sizeOfPcInstance = sizeof(MuPcInstance);
	sizeOfMonsterInstance = sizeof(MuMonsterInstance);
	sizeOfNpcInstance = sizeof(MuNpcInstance);
	sizeOfItemInstance = sizeof(MuItemInstance);

	contOfMonsters = contOfPlayers = contOfNpcs = contOfItems = 0;

}

ObiectPool* ObiectPool::_instance = NULL;
ObiectPool* ObiectPool::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new ObiectPool;
		_instance->initPoolData();
	}
	return _instance;
}

unsigned short ObiectPool::reserveId()
{
	unsigned short freeid = _freeCels.top();
	_freeCels.pop();
	return freeid;
}
void ObiectPool::returnId(unsigned short id)
{
	if (_pool[id] != NULL)
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

MuPcInstance* ObiectPool::newMuPcInstance(unsigned short id)
{
	MuPcInstance * temp = new MuPcInstance();
	temp->setIndex(id);
	temp->setType(O_Player);
	_pool[id] = temp;
	return temp;
}

MuMonsterInstance* ObiectPool::newMuMonsterInstance(MuNpcTemplate t,
		unsigned char _x, unsigned char _y, unsigned char map)
{
	MuMonsterInstance * temp;
	int freeId = _freeCels.top();
	_freeCels.pop();
	temp = new MuMonsterInstance(t, _x, _y, map, freeId);
	temp->setType(O_Mob);
	_pool[freeId] = temp;
	contOfMonsters++;
	//printf ("|OBJECTPOOL Object %d Creted and Stored Succesfull \n",freeId);
	return temp;
}

MuNpcInstance* ObiectPool::newMuNPCInstance(MuNpcTemplate t, unsigned char _x,
		unsigned char _y, unsigned char map)
{
	MuMonsterInstance * temp;
	int freeId = _freeCels.top();
	_freeCels.pop();
	temp = new MuMonsterInstance(t, _x, _y, map, freeId);
	temp->setType(O_NPC);
	_pool[freeId] = temp;
	contOfMonsters++;
	//printf ("|OBJECTPOOL Object %d Creted and Stored Succesfull \n",freeId);
	return temp;
}

MuViewPortPair ObiectPool::getDistance(unsigned short id1, unsigned short id2,
		unsigned char dist)
{
	MuViewPortPair te = std::make_pair(new MuViewPort(), new MuViewPort());
	te.first->o_Index = id1;
	te.first->o_dist = 0xff;
	te.first->c_State = 0x00;
	te.second->o_Index = id2;
	te.second->o_dist = 0xff;
	te.second->c_State = 0x00;

	register MuObiect * o1 = getObject(id1);
	register MuObiect * o2 = getObject(id2);
	if ((o1 == NULL) || (o2 == NULL))
	{
		te.first->o_Index = 0x00;
		te.second->o_Index = 0x00;
		te.first->c_State = 0x04;
		te.second->c_State = 0x04;
		te.first->PrintMe();
		te.second->PrintMe();
		return te;
	}
	else
	//obiects exists
	{
		if ((o1->getPosX() == o2->getPosX())
				&& (o1->getPosX() == o2->getPosY()))
		{
			te.first->o_dist = 0;
			te.second->o_dist = 0;
		}
		else
		{
			//Calculate the distance
			float fCalcX = (float) abs(o1->getPosX() - o2->getPosX());
			float fCalcY = (float) abs(o1->getPosY() - o2->getPosY());
			int res = (int) sqrt((fCalcX * fCalcX) + (fCalcY * fCalcY));
			te.first->o_dist = res;
			te.second->o_dist = res;
		};
	}
	if (te.second->o_dist <= dist)
	{
		te.first->c_State = MuViewPort::S_New;
		te.second->c_State = MuViewPort::S_New;
	}
	else
	{
		te.first->c_State = MuViewPort::S_ToForget;
		te.second->c_State = MuViewPort::S_ToForget;

	}
	te.first->o_Type = o1->getType();
	te.second->o_Type = o2->getType();
	return te;

}

void ObiectPool::ProcessPool()
{
	for (unsigned int i = 0; i <= 0xffff; i++)
	{
		if (_pool[i] == NULL)
			continue;
		MuObiect * o = _pool[i];
		if (!o->isVisibable())
		{
			printf("Spown Object: \n");
			MuMaps::getInstance()->getMap(o->getPosMapNb())->storeNewObiect(o);
			o->setVisibable(true);
			continue;
		}
		o->PrintMe();
	}
}

std::list<MuObiect*> ObiectPool::toObjList()
{
	std::list<MuObiect*> vec;
	for (unsigned int i = 0; i <= 0xffff; i++)
	{
		if (_pool[i] == NULL)
			continue;
		vec.push_back(_pool[i]);
	};
	return vec;

}

std::list<MuObiect*> ObiectPool::toMonList()
{
	std::list<MuObiect*> vec;
	for (unsigned int i = 0; i <= 0xffff; i++)
	{
		if (_pool[i] == NULL)
			continue;
		if (_pool[i]->getType() == O_Mob)
			vec.push_back(_pool[i]);
	};
	return vec;
}

std::list<MuObiect*> ObiectPool::toPlaList()
{
	std::list<MuObiect*> vec;
	for (unsigned int i = 0; i <= 0xffff; i++)
	{
		if (_pool[i] == NULL)
			continue;
		if (_pool[i]->getType() == O_Player)
			vec.push_back(_pool[i]);
	};
	return vec;
}
std::list<unsigned short> ObiectPool::toIdObjList()
{
	std::list<unsigned short> lis;
	for (unsigned int i = 0; i <= 0xffff; i++)
	{
		if (_pool[i] == NULL)
			continue;
		lis.push_back(i);
	}
	return lis;
}

std::list<unsigned short> ObiectPool::toIdMobList()
{
	std::list<unsigned short> lis;
	for (unsigned int i = 0; i <= 0xffff; i++)
	{
		if (_pool[i] == NULL)
			continue;
		if (_pool[i]->getType() == O_Mob)
			lis.push_back(i);
	}
	return lis;
}

std::list<unsigned short> ObiectPool::toIdPlaList()
{
	std::list<unsigned short> lis;
	for (unsigned int i =0 ; i <= 0xffff; i++)
	{
		if(_pool[i]==NULL)continue;
		if(_pool[i]->getType() == O_Player)
			lis.push_back(i);
	}
}
