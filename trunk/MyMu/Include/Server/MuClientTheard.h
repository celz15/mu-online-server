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
#include "AdminTools/ACommandMng.h"				//komendy dla fracza/hm'a


//#include "Obiects/MuCharacters.h"
class MuClientTheard 
{
  MuClientTheard * me;							//Wskaznik zwrotny
  BDBase *_DB;				    				//polaczenie z bd
  Socket *_connected;							//polaczenie z klijentem

  MyCharacterList* _myChList; 					//lista postaci posiadanych [przez gracza
  MuUser *_user;								//user connected to server
  PacketHandler* _handler;						//obsluga protokolu
  MuPcInstance* _activeChar;					//aktualna postac w grze

  
  
  int ConnectID; 								//id polaczenia
  int DBId;     								//id do bazy danych
  //  ACommandMng *_commands;						//komnedy gracza gm;a
  //	MuPcInstance *_character;					//postac w grze


public:
  MuClientTheard(Socket  * c,BDBase* db)
  {
 	  
    _myChList=new MyCharacterList;				//buduje pusta liste postaci gracza
    ConnectID=IdFactory();					//przydzielam id postaci
    _DB=db;									//ustawiam polaczenie z BD
    _connected=c;								//ustawiam polaczenie z klientem
    
    //
  }
  BDBase * getDB(){return _DB;};
  virtual ~MuClientTheard();

  //  void initCommans(std::vector < ACommandT * > list)
  //  {
  //  	 _commands=new ACommandMng(list);				//komendy dla gm'a / gracza inicjuje
  //  	 
  //  }	
  void setMe(MuClientTheard *a){me=a;};

  void Run(){
  
    _handler=new PacketHandler(me);					//buduje obsluge pakietow
    _connected->Send(new SHello("09928",ConnectID));//("10114",ConnectID));
    //"00001",ConnectID));	//wysylam paczke hello do klijenta NeWUnionMu

    while(!_connected->EnyError())					//dopuki klijent sie nie rozlaczy
      {
	HexBuff *buff=new HexBuff;//alokuje miejsce na paczke przychozaca

	_connected->Recv(*buff);						//odbieram paczke
	_handler->handlePacket(buff);					//posylam do obrubki
	  
	//zalozenia tu ma byc odbierana pazka i wysylana do obrubki [w zalozeniach] 
	// klasa PacketHandler ma za zadanie robienie tego	
      };
	
  };
  
  //ACommandMng* getCommands(){return _commands;};
  void setDBId(int i){DBId=i;};						//utawiam id w bd usera
  int getDBId(){return DBId;};						//pobieram id w bd usera 
  
  int getConnectID(){return ConnectID;};			//pobieram id polaczenia klijenta
  Socket * getConnected(){return _connected;};		//pobieram polaczenie z klijentem
  
  void Send(SBPacket *h){_connected->Send(h);};		//zbindowane wysylanie paczki do klijenta
  void ASend(SBPacket *h){_connected->multiAdd(h);};//dodawanie paczki do wysylania
  void MSend(){_connected->multiSend();};			//wysylania kilka pazek na raz
  
  MyCharacterList * getMyCharacterList()			//pobieram liste postaci usera
  {return _myChList;};
  
  void setUser(MuUser * u){_user=u;};				//ustawiam usera
  MuUser* getUser(){return _user;};					//pobieram usera
  
  MuPcInstance* getActiveCharacter()				//pobiera postac z grze
  {return _activeChar;}
  void setActiveCharacter(MuPcInstance *o)			//ustawia postac w grze
  {_activeChar=o;};
  				
  
};

#endif /*MUCLIENTTHEARD_H_*/
