#ifndef CPUBLICMSG_H_
#define CPUBLICMSG_H_
#include "Protocol/CBPacket.h"
#include "Protocol/SPublicMsg.h"
#include "Protocol/SItemList.h"
#include "Protocol/SGotExp.h"
#include "Protocol/SPutItemInInw.h"

//clasa: CPublicMsg
//_cl      - wskaznik do clientTheart
//buff   - wskaznik do bufora Hex

class CPublicMsg: public CBPacket
{
	std::string msg; // wiadomsc
	std::string who;
public:
	CPublicMsg(HexBuff *b, MuClientTheard *t) :
		CBPacket(b, t)
	{
	}
	virtual ~CPublicMsg()
	{
	}
	;
	void debuild()
	{
		int msglen = (*buff)[1].readC() - 14;
		who = (*buff)[3].readS(10);
		msg = (*buff)[13].readS(msglen);
		std::cout << "Public msg: od" << who << "[" << msg << "]\n";
		//jesli to komenda to wykonujemy i jesl nie jest to komenda wtedy wysylamy komunikat ?
		if (msg.c_str()[0] == '\\')
			switch (msg.c_str()[1])
			{
			case '1':
			{
				ItemInInwentory * t = new ItemInInwentory();
				t->inw_slot = 20;
				t->inw_ItemHex.makeItem(1, 0, 0, 20, 0, 0, 0);
				ItemInInwentory * t1 = new ItemInInwentory();
				t1->inw_slot = 25;
				t1->inw_ItemHex.makeItem(0, 1, 0, 20, 0, 0, 0);
				vector<ItemInInwentory*> _list;
				_list.push_back(t);
				_list.push_back(t1);
				_cl->Send(new SItemList(_list));
				break;
			}
				;
			case '2':
				_cl->Send(new SGotExp(1, 1));
				break;
			case '3':
			{
				ItemHex item;
				item.makeItem(5, 1, 0, 1, 0x00, 0x00, 0x00);
				_cl->Send(new SPutItemInInwetory(1, &item));
				break;
			}
				;
			case 'o':
				_cl->getActiveCharacter()->getViewPort()->optymalize();
				break;
			case 'p':
				ObiectPool::getInstance()->ProcessPool();
				break;
			};
		//		_cl->getCommands()->ParseComandLine(msg);

		_cl->Send(new SPublicMsg(who, msg));
	}
};
#endif /*CPUBLICMSG_H_*/
