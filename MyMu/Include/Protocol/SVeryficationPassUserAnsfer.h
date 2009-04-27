#ifndef SVERYFICATIONPASSUSERANSFER_H_
#define SVERYFICATIONPASSUSERANSFER_H_

#include "SBPacket.h"

class SVeryficationPassUserAnsfer : public CSPacket
{
	unsigned char f;
public:
// f= veryfication resultat
// 0- ok
// 1 no user or wrag pass
	SVeryficationPassUserAnsfer(unsigned char fl):CSPacket()
	{
		MyName="SC f101 Ansfer login & pass veryfication";
		f=fl;
	};
	virtual ~SVeryficationPassUserAnsfer();
	HexBuff* build();
};

#endif /*SVERYFICATIONPASSUSERANSFER_H_*/
