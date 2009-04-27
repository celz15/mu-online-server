#include "MuObiects/MuCharacter.h"
#include "MuObiects/MuPcInstance.h"

	void MuCharacter::broadcastPacket(SBPacket *p)
	{
		int i=0;
		if(!knowsObiectList.empty()) //jesli nie ma nic w kolejce to koncz
		for( i=0;i<knowsObiectList.size();i++)
		{   
			
			if(knowsObiectList[i]->getMType()==1)//jesli jestm graczem
			{
			std::cout << "BROADCAST Send: character " <<knowsObiectList[i]->getOId()
					  << ".\n"; 
			(static_cast<MuPcInstance*>	(knowsObiectList[i]))->Send(p);
			};
		};
		//std::cout <<"przeszuklem: " <<i<<".\n";
		
	}

void TaskHeal::Run()
{
	//me->HpReg();  // uzupelniamy zycie
	//me->_bTask(); // dodajemy siebie do taska jsli trzeba 
};

