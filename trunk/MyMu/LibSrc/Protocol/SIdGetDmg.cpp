#include "Protocol/SIdGetDmg.h"

SIdGetDmg::~SIdGetDmg()
{
}
HexBuff * SIdGetDmg::build()
{							
  unsigned char t[]={0xc1,0x08,0xd6,0xff,0xff,0xff,0xff,0xff,0x00};	// 99b+
  //unsigned char t[]={0xc1,0x08,0xd7,0xff,0xff,0xff,0xff,0xff,0x00};		// 1.2d
  					
  //mC1Header(0xd9,0x08);
  (*h)[0].writeAC(t,0x08);
  (*h)[3].writeI(id,false);
  (*h)[5].writeI(dmg,false);
  (*h)[7].writeC(flag);
  std::cout << "Id: " << id << " got dmg " << dmg << " with flag " << (int) flag << " .\n"; 
return h;
};
