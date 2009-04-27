
#include "Protocol/PacketHandler.h"

#include "Protocol/CBUnknown.h"         //dla nie znanych
#include "Protocol/CBPlaning.h"         //dla podejrzewanych

#include "Server/MuClientTheard.h"
#include "Protocol/CPublicMsg.h"
#include "Protocol/CUserPasVer.h"
#include "Protocol/CCharacterListRequest.h"
#include "Protocol/CEnterSelectedCharacterRequest.h"
#include "Protocol/CNewCharacterRequest.h"
#include "Protocol/CCharacterMove.h"
#include "Protocol/CAtackID.h"
#include "Protocol/CPickUpItem.h"
#include "Protocol/CRequestOpenWindow.h"
#include "Protocol/CUseLvlUpPoints.h"
#include "Protocol/CChangeDirectionOrStatus.h"
#include "Protocol/CAddNewFriendRequest.h"
#include "Protocol/CChatStartRequest.h"
#include "Protocol/CA0UnkownReq.h"
#include "Protocol/CDropItemRequest.h"
#include "Protocol/CItemMoveToRequest.h"

PacketHandler::~PacketHandler()
{
}
PacketHandler::PacketHandler( MuClientTheard* t)
{
  _client=t;
};
  
void PacketHandler::handlePacket(HexBuff *p)
{
 CBPacket *pa; // przed
  switch (p->getType1Pack()) 
    { 
      
    case 0x00: pa=new CPublicMsg(p,_client);break;                         //wiadomosc publiczna
    case 0x02: pa=new CBPlaning(p,_client,"private message");break;
    case 0x07: pa=new CBPlaning(p,_client,"Use skill");break;
    case 0x18: pa=new CChangeDirectionOrStatus(p,_client);break;           //zmiana statusu lub kierunku
    case 0x22: pa=new CPickUpItem(p,_client);break;			       //podnies item
    case 0x23: pa=new CDropItemRequest(p,_client);break;
    case 0x24: pa=new CItemMoveToRequest(p,_client);break;
    case 0x30: pa=new CRequestOpenWindow(p,_client);break;		      //open window
    case 0x32: pa=new CBPlaning(p,_client,"Quest window open");break;
    case 0x36: pa=new CBPlaning(p,_client,"request to trade");break;
      
    case 0x42: pa=new CBPlaning(p,_client,"Party window open");break;
    case 0x52: pa=new CBPlaning(p,_client,"Guild window open");break; 
    case 0xa0: pa=new CA0UnkownReq(p,_client);break;
    case 0xa9: pa=new CBPlaning(p,_client,"Status window open");break;   
    case 0xc1: pa=new CAddNewUserRequest(p,_client);break;                //dodawanie frienda
    case 0xc2: pa=new CBPlaning(p,_client,"request addfriend zaproszenie");break;
    case 0xc3: pa=new CBPlaning(p,_client,"request delte friend");break;
    case 0xc4: pa=new CBPlaning(p,_client,"request wich on\\off silent chat system");break;
    case 0xca: pa=new CChatStartRequest(p,_client);break;
    case 0xD9: pa=new CAtackID(p,_client);break;		    	      //atakuje 99b+ only ?
    case 0xD7: pa=new CCharacterMove(p,_client);break; 		      //poruszam sie 99b+
      
      //case 0xD3: pa=new CCharacterMove(p,_client);break; 		      //poruszam sie 1.2b
	//case 0xD6: pa=new CAtackID(p,_client);break;		    	      //atakuje 1.7x ??
	//case 0xD7: pa=new CAtackID(p,_client);break;		    	      //atakuje 1.2b only
      
    case 0xf1:													//logowanie
      {
	switch(p->getType2Pack())
	  {
	    
	  case 0x01: pa=new CUserPasVer(p,_client);break;		//weryfikacja uip
	  case 0x02: pa=new CBPlaning(p,_client,"prosba o logout");break;		//prosba o logout
	  case 0x03: pa=new CBPlaning(p,_client,"NIEZNANA PROSBA CHYBA O AKTUALIZACJE STATYSTYK");break;
	  default:pa=new CBUnknown(p,_client);break;
	  };
      }break;
      
    case 0xf3:													//lista postaci
      {
	switch(p->getType2Pack())
	  {
	  case 0x00: pa=new CCharacterListRequest(p,_client);break;				//lista postaci
	  case 0x01: pa=new CNewCharacterRequest(p,_client);break;				//nowa postac
	  case 0x03: pa=new CEnterSelectedCharacterRequest(p,_client);break;		//wybrano postac
	  case 0x06: pa=new CUseLvlUpPoints(p,_client);break; 					//urzycie lvlup punktow
	  case 0x30: pa=new CBPlaning(p,_client,"configuration settings");break;
	    
	  default:pa=new CBUnknown(p,_client);break;							//nieznany
	  };
	
      }break;
      
    default: pa=new CBUnknown(p,_client);break;
    } 
  pa->debuild();
  delete pa;
}
