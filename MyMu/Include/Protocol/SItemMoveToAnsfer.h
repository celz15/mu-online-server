#ifndef SITEMMOVETOANSFER_H_
#define SITEMMOVETOANSFER_H_
#include "Protocol/SBPacket.h"

//clasa : SItemMoveToAnsfer
//h    -paczka budowana
class SItemMoveToAnsfer : public CSPacket
{
int _windTo;		//window to put item
int _slotTo;		//slot where put item
unsigned char _item[4];//item to put
public:
	SItemMoveToAnsfer(int windTo,int slotTo,unsigned char *i):CSPacket()
	{
	_windTo=windTo;
	_slotTo=slotTo;
	_item[0]=i[0];
	_item[1]=i[1];
	_item[2]=i[2];
	_item[3]=i[3];
	_item[4]=i[4];
		MyName="24 item move in inwentory";
	};
	 ~SItemMoveToAnsfer(){};
	HexBuff * build()
	{
	unsigned char t[]={0xc3 ,0x09 ,0x24 ,_windTo ,_slotTo ,_item[0] ,_item[1] ,_item[2] ,_item[3] ,_item[4]};
	(*h)[0].writeAC(t,0x09);
	return h;
	};
	
};

#endif /*SITEMMOVETOANSFER_H_*/
