#include "MuObiects/MuCharacter.h"
#include "MuObiects/MuPcInstance.h"
#include "MuObiects/MuMaps.h"

unsigned char MuCharacter::getPosOldX()
{
	return o_PosOldX;
}

void MuCharacter::broadcastPacket(SBPacket *p)
{
	unsigned short id = 0;
	for (int i = 0; i < o_ViewPort->getViewSize(); i++)
	{
		if ((*o_ViewPort)[i].c_State != MuViewPort::S_Empty)
		{

			if ((*o_ViewPort)[i].o_Type == O_Player)//if i'm player
			{
				//printf("......i:%d z :%d\n", i, o_ViewPort->getViewSize());
				//printf("---->found player in broadcast package \n");
				id = (*o_ViewPort)[i].o_Index;
				MuObiect * o = ObiectPool::getInstance()->getObject(id);
				if (o != NULL)
				{
					printf("OBJECT[%d] BRODCATING MSG: [%s] to Player[%d]\n",
							getIndex(), p->getName().c_str(),
							(*o_ViewPort)[i].o_Index);
					(static_cast<MuPcInstance*> (o))->Send(p);
				}
				else
				{
					printf("ObiectPool returned empty object for Id(%d)\n", id);
				}
			}
		};
	};
}

void MuCharacter::CheckViewPort()
{
	MuMaps::getInstance()->getMap(getPosMapNb())->updatePortView(getViewPort());
	CheckToForgetInViewPort();
	checkNewInViewPort();
}

void MuCharacter::IDie()
{
	MuPcInstance * pc;
	printf("Monster [%d] Died ... \n", getIndex());
	SIdDie * pack = new SIdDie(getIndex());
	broadcastPacket(pack);
	MuMaps::getInstance()->getMap(getPosMapNb())->removeVisibleObject(
			getIndex());
	this->setVisibable(false);
	//o_ViewPort->printMe();
	for (int i = 0; i <= o_ViewPort->getViewSize(); i++)
	{
		MuViewPort * p = o_ViewPort->getViewPort(i);
		p->PrintMe();
		if ((p->o_Type == O_Player) && (p->c_State == MuViewPort::S_Known))
		{
			p->PrintMe();
			pc
					= static_cast<MuPcInstance*> ((ObiectPool::getInstance()->getObject(
							p->o_Index)));
			pc->getViewPort()->printMe();
			pc->getViewPort()->getViewPort(pc->getViewPort()->searchId(
					getIndex()))->c_State = MuViewPort::S_Empty;
			pc->getViewPort()->printMe();
		}
	}
	delete pack;
}
