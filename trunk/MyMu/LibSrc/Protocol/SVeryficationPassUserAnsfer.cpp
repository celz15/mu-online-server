#include "Protocol/SVeryficationPassUserAnsfer.h"



SVeryficationPassUserAnsfer::~SVeryficationPassUserAnsfer()
{
}
HexBuff * SVeryficationPassUserAnsfer::build(){
mC1Header(0xf1,0x01,0x05);
(*h)[4].writeC(f);
(*h)[5].writeC(0x00);
return h;
}

	
