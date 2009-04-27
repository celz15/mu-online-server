#ifndef SFRIENDLIST_H_
#define SFRIENDLIST_H_
#include "Protocol/SBPacket.h"
#include "MuObiects/MuFriendCharacter.h"
//clasa : SFriedList
//h    -paczka budowana
class SFriedList : public CSPacket
{
vector<MuFriendCharacter*> _friendList;		//lista frenda
std::string _test;
public:
	SFriedList()
	{
	_test=".Comsole .";
	};
	SFriedList(vector<MuFriendCharacter*> friendList):CSPacket()
	{
	_friendList=friendList;
		MyName="C0 friend list";
	};
	 ~SFriedList(){};
	HexBuff * build()
	{
		unsigned char t[]=
		{
			0xc1 ,0x0f ,0xc1 ,0x01 ,
			0x00 ,0x00 ,0x00 ,0x00  ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 
			,0xff};
		//lista friend{0xc2 ,0x00 ,0x12 ,0xc0 ,0x00 ,0x32 ,0x01 ,0x6d ,0x69 ,0x6b ,0x69 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0xff};
		(*h)[0].writeAC(t,0x0f);
		//(*h)[5].writeS(_test);
		
	
	return h;
	};
	
};

#endif /*SFRIENDLIST_H_*/
