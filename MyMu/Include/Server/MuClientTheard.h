#ifndef MUCLIENTTHEARD_H_
#define MUCLIENTTHEARD_H_
#include "IdFactory.h"							//przydzielanie id'ow
#include <iostream>
#include <Socket/Socket.h>
#include "DB/BDBase.h"							//baza danych
#include "Protocol/PacketHandler.h"				//obsluga protokolu
#include "Protocol/SHello.h"					//paczka hello
#include "MuObiects/MyCharacterList.h"			//moja lista postaci
#include "MuObiects/MuUser.h"					//informacje o userze
#include "MuObiects/MuPcInstance.h"				//gracz w swiecie
#include "MuObiects/MuMaps.h"					//mapy w grze
#include "MuObiects/MuHandInwentory.h"
#include "AdminTools/ACommandMng.h"				//komendy dla fracza/hm'a



class MuClientTheard 
{
  MuClientTheard * me;							//Wskaznik zwrotny
  BDBase *_DB;				    				//polaczenie z bd
  Socket *_connected;							//polaczenie z klijentem

  MyCharacterList* _myChList; 					//lista postaci posiadanych [przez gracza
  MuUser *_user;								//user connected to server
  PacketHandler* _handler;						//obsluga protokolu
  MuPcInstance* _activeChar;					//aktualna postac w grze
  MuHandInwentory *_inw;
  
  
  int ConnectID; 								//id polaczenia
  int DBId;     								//id do bazy danych



public:
  MuClientTheard(Socket  * c,BDBase* db)
  {
    _myChList=new MyCharacterList;				//buduje pusta liste postaci gracza
    ConnectID=ObiectPool::getInstance()->reserveId();					//przydzielam id postaci
    _DB=db;									//ustawiam polaczenie z BD
    _connected=c;								//ustawiam polaczenie z klientem
  }

  BDBase * getDB(){return _DB;};
  virtual ~MuClientTheard();

  void setMe(MuClientTheard *a){me=a;};

  void Run(){
    _handler=new PacketHandler(me);					//buduje obsluge pakietow
    _connected->Send(new SHello("09928",ConnectID));

    while(!_connected->EnyError())					//dopuki klijent sie nie rozlaczy
      {
	HexBuff *buff=new HexBuff;
	_connected->Recv(*buff);						//odbieram paczke
	_handler->handlePacket(buff);					//posylam do obrubki
      };
  };
  MuHandInwentory * getCharactersInwentory()
  {
    return _inw;
  };
  
  void setDBId(int i)
  {
    DBId=i;
  };						//utawiam id w bd usera

  int getDBId()
  {
    return DBId;
  };						//pobieram id w bd usera 
  
  int getConnectID()
  {
    return ConnectID;
  };			//pobieram id polaczenia klijenta

  Socket * getConnected()
  {
    return _connected;
  };		//pobieram polaczenie z klijentem
  
  void Send(SBPacket *h)
  {
    _connected->Send(h);
  };

  void ASend(SBPacket *h)
  {
    _connected->multiAdd(h);
  };

  void MSend()
  {
    _connected->multiSend();
  };
  
  MyCharacterList * getMyCharacterList()			//pobieram liste postaci usera
  {
    return _myChList;
  };
  
  void setUser(MuUser * u)
  {
    _user=u;
  };
  //ustawiam usera
  MuUser* getUser()
  {
    return _user;
  };					//pobieram usera
  
  MuPcInstance* getActiveCharacter()				//pobiera postac z grze
  {
    return _activeChar;
  }

  void setActiveCharacter(MuPcInstance *o)			//ustawia postac w grze
  {
    _activeChar=o;
    _inw=new MuHandInwentory();
  };

  void ReadCharacter(std::string charname)
  {
    int dbcharid =getUser()->getDBID();   
    ReadCharacterFromDb(charname,dbcharid);
  }
  void ReadCharacterFromDb(std::string charname,int dbUserId)
  {
    char sqlQuery [80]={0x00};
    sprintf(sqlQuery,"SELECT * FROM characters WHERE ch_user=%d AND ch_name='%s'",dbUserId,charname.c_str());
    printf ("SQL QUERY: %s",sqlQuery);
    if(!_DB->isConnected())
      {
	mysql_query(_DB->GetDB(),sqlQuery);
	if(mysql_field_count(_DB->GetDB())>0)
	  {
	    MYSQL_RES *wynik=mysql_store_result(_DB->GetDB());
	    if (wynik != NULL)
	      {
		if(mysql_num_rows(wynik)>0)
		  {
		    MYSQL_ROW w=mysql_fetch_row(wynik);
		    _activeChar->setName(w[2]);
		    _activeChar->setClass(atoi(w[3]));
		    _activeChar->setLvl(atoi(w[4]));
		    _activeChar->setLpPerLvl(atoi(w[5]));
		    _activeChar->setCurExp(atoi(w[6]));
		    _activeChar->setStr(atoi(w[7]));
		    _activeChar->setAgl(atoi(w[8]));
		    _activeChar->setEnr(atoi(w[10]));
		    _activeChar->setVit(atoi(w[9]));
		    _activeChar->setCom(atoi(w[11]));
		    _activeChar->setStatCurHpMpSt(atoi(w[12]),atoi(w[13]),atoi(w[14]));
		    _activeChar->setPosXY(atoi(w[15]),atoi(w[16]));
		    _activeChar->setPosHead(atoi(w[18]));
		    _activeChar->setPosStatus(atoi(w[19]));
		    _activeChar->setPosMapNb(atoi(w[17]));
		    _activeChar->setInwZen(atoi(w[20]));
		  };
	      };
	  };
      };
    
  }
    
  void SaveCharacterInDb()
  {
    char sqlQuery[120];
    sprintf(sqlQuery,
	    "UPDATE cheracters SET ch_ExpLvl = %d, ch_ExpLvlP = %d, "
	    "ch_Exp = %d,"
	    "ch_StatStr= %d,"
	    "ch_StatAgl= %d,"
	    "ch_StatVit= %d,"
	    "ch_StatEnr= %d,"
	    "ch_StatCom= %d,"
	    "ch_StatCurHp=%d,"
	    "ch_StatCurMp=%d,"
	    "ch_StatCurSt=%d,"
	    "ch_PosX=%d,"
	    "ch_PosY=%d,"
	    "ch_PosM=%d,"
	    "ch_PosS=%d,"
	    "ch_InwZen=%d"
	    "WHERE  ch_Name ='%s' and ch_Uid=%d LIMIT 1",
	    _activeChar->getCurExp(),
	    _activeChar->getStr(),
	    _activeChar->getAgl(),
	    _activeChar->getVit(),
	    _activeChar->getEnr(),
	    _activeChar->getCom(),
	    _activeChar->getStatCurHp(),
	    _activeChar->getStatCurMp(),
	    _activeChar->getStatCurSt(),
	    _activeChar->getPosX(),
	    _activeChar->getPosY(),
	    _activeChar->getPosMapNb(),
	    _activeChar->getPosStatus(),
	    _activeChar->getInwZen(),
	    _activeChar->getName().c_str(),
	    DBId
	    ) ;
    printf("SQLQUERY save character:%s",sqlQuery);
  }

  void LoadInwentoryFromDb()
  {
    char sqlQuery[80]={0};
    sprintf(sqlQuery,"SELECT * FROM items WHERE i_OwnerId=%d",DBId);
    if(!getDB()->isConnected())
      {
	mysql_query(getDB()->GetDB(),sqlQuery);
	if(mysql_field_count(getDB()->GetDB())>0)
	  {
	    MYSQL_RES * res = mysql_store_result(getDB()->GetDB());
	    if(res!=NULL)
	      {
		if(mysql_num_rows(res)>0)
		  {
		    for(int i =0; i<mysql_num_rows(res);i++)
		      {
			MYSQL_ROW row=mysql_fetch_row(res);
			unsigned long serial=atol(row[0]);
			unsigned char windowId=atoi(row[2]);
			unsigned char slot = atoi (row[3]);
			unsigned char grup = atoi (row[4]);
			unsigned char index = atoi (row[5]);
			unsigned char lvl = atoi (row[6]);
			unsigned char dur= atoi (row[7]);
			unsigned char opt = atoi (row[8]);
			unsigned char eop = atoi (row[9]);
			unsigned char aop = atoi (row[10]);
			ItemInInwentory * i = new ItemInInwentory();
			i->inw_ItemHex.makeItem(grup,index,lvl,dur,opt,eop,aop);
			i->inw_ItemSerial=serial;
			i->inw_slot= slot;
			i->inw_windowId=windowId;
			i->inw_ItemInfo= ItemInfoMng::getItemInfo(grup,index);
			if(windowId==WId_Inwentory)_inw->putItemInInwentory(i);
			//if(windowId==WId_Vault)_vault->putItemInInwentory(i); todo loult
		      };
		  };
	      };
	    mysql_free_result(res);
	  };
      };


  }

  void SaveInwentoryToDb()
  {
  }
  
  
};

#endif /*MUCLIENTTHEARD_H_*/
