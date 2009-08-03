/*
 * MuAiProcess.cpp
 *
 *  Created on: 2009-08-03
 *      Author: Administrator
 */

#include "MuObiects/MuAiProcess.h"
#include "MuObiects/MuMonsterInstance.h"
MuAiProcess::MuAiProcess()
{
	// TODO Auto-generated constructor stub

}

MuAiProcess::~MuAiProcess()
{
	// TODO Auto-generated destructor stub
}

void MuAiProcess::Process(MuMonsterInstance *inst)
{
	MuMonsterAiData * data = inst->getAiData();
	if (data == NULL)
	{

	}
	else if (data->runTime())
		switch (data->_aiTask)
		{
		case MuMonsterAiData::AiRespown:
			inst->setVisibable(true);
			printf("AI Monster[id:] Respowned!\n", inst->getIndex());
			break;
		case MuMonsterAiData::AiGoto:
			break;
		case MuMonsterAiData::AiTurn:
			break;
		};

}

void MuAiProcess::setAiProcessId(unsigned char id)
{
	_ai_id = id;
}

unsigned char MuAiProcess::getAiProcessId()
{
	return _ai_id;
}

void MuAiProcess::Signall(unsigned short from, unsigned short who,
		unsigned char what)
{
	MuMonsterAiData * data;
	MuMonsterInstance * mon = ObiectPool::getInstance()->getObject(from);
	MuPcInstance * pc = ObiectPool::getInstance()->getObject(who);
	if (mon == NULL)
		return;
	switch (what)
	{
	case SigDie:
		if (mon->getAiData() == NULL)
			mon->setAiData(new MuMonsterAiData());
		data = mon->getAiData();
		//respown in next 100ms
		data->runInNextXMSec(100);
		data->_aiTask = MuMonsterAiData::AiRespown;
		mon->setVisibable(false);
		printf("Ai Monster[Id:%d] set to respown in next [%d] milisecond\n",
				mon->getIndex(), 100);
		break;
	case SigAtacked:
		if (mon->getAiData() == NULL)
			mon->setAiData(new MuMonsterAiData());
		data = mon->getAiData();
		int viewPortId = mon->getViewPort()->searchId(who);
		if (viewPortId != 0xff)//we see who atack me
		{
			if (mon->getViewPort()->getViewPort(viewPortId)->o_dist
					<= mon->getAttackRange()) //we are in atack range
			{
				printf("AI Monster[id:%d] attack Player[Id:%d] \n", from, who);
			}
			else //not in attack range
			{
				printf("AI monster [Id:%d] goto to Player[Id:%d]\n", from, who);
			}
		}
	}
}

