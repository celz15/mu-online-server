#include "MuObiects/MuMap.h"
#include "MuObiects/MuMonsterInstance.h"
#include "MuObiects/MuObjectsPool.h"
#include "Task/Task.h"
#include "MuObiects/MuNpcTemplate.h"
void MuMap::InitMonstersSpot()
{
	printf(" init monster function entry");
	if (_allSpotV.size() == 0)
	{
		printf(" -- NO SPOT TO INIT --\n");
	}
	else
	{
		std::cout << _name << ": INITS MOBS SPOTS\n";

		for (int a = 0; a < _allSpotV.size(); a++)
		{
			std::cout << "---INIT SPOT #" << a << "---.\n";
			MuSpot * s = _allSpotV[a];
			MuNpcTemplate t = MuNpcTempMng::getNpcTempl(s->getR());
			for (int c = 0; c <= s->getC() - 1; c++)
			{
				MuMonsterInstance *mob =
						ObiectPool::getInstance()-> newMuMonsterInstance(t,
								(unsigned char) s->startX(),
								(unsigned char) s->startY(), this->getCode());
				storeNewObiect(mob);
				//mob->RunMoveInst();
			};
			std::cout << "---INIT SPOT #" << a << " DONE---.\n\n";
		};
	};
}

void MuMap::updatePortView(MuViewPortSet * view)
{
	unsigned short _id = 0;
	unsigned short _for = view->getIndex();
	if (!_allObiectV.empty())
		for (std::vector<unsigned short>::iterator i = _allObiectV.begin(); i
				!= _allObiectV.end(); i++)
		{
			if ((*i) == view->getIndex())
				continue;
			MuViewPortSet * his =
					ObiectPool::getInstance()->getObject(*i)->getViewPort();
			MuViewPortPair p = ObiectPool::getInstance()->getDistance(
					his->getIndex(), view->getIndex(), his->getViewRad());
			his->addViewPort(p.second);
			view->addViewPort(p.first);
		};
}

