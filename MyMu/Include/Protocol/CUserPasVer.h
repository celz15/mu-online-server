#include <iostream>
#include "CBPacket.h"
#include "SVeryficationPassUserAnsfer.h"
#include <string>
#include "DB/BDLogin.h"

//stale
#define PA_InvaltPassword    0x00
#define PA_PassOK    0x01
#define PA_AccInvalt           0x02
#define PA_AccAlredyConnected  0x03
#define PA_ServerIsFull    0x04
#define PA_AccBlacked    0x05
#define PA_NewVersionOfGamereq 0x06
#define PA_NoChargeInfo        0x09


class  CUserPasVer:public CBPacket{
  BDLogin * bd; //obsluga bs logowania
  login_info login;
  std::string user;
  std::string pass;
 public:
  CUserPasVer(HexBuff *b, MuClientTheard *t):CBPacket(b,t)
{
 // cout << "pascv cons\n";
  bd=new BDLogin(t->getDB());
  //cout <<"pasv ecos\n";
}
  virtual ~CUserPasVer(){}
  
  
  void debuild(){
    GetUser();
    GetPass();
   
    unsigned char f=Login();
   
    SVeryficationPassUserAnsfer *log=new SVeryficationPassUserAnsfer(f);
   
    _cl->Send(log);
    cout << "powyslaniu userczek\n";
    
  };
  unsigned char Login()
    {
      unsigned char status;
      cout <<"  1User= |" << user << "| Pass= |" << pass << "|\n";  
     
      if(bd->IsUser(user)) // jesli dany uer wystepuje w BD
	{
	  bd->GetUser(user,&login);// pobieram go
	  _cl->setUser(new MuUser(login.user,login.pass,login.HCHar,login.id));
	  

	  cout <<"  2User= |" << login.user << "| Pass= |" << login.pass << "|\n";
	  if ((user.substr(0,user.size())==login.user.substr(0,user.size()))&&
	      (pass.substr(0,pass.size())==login.pass.substr(0,pass.size())))
	    return PA_PassOK;
	    
	}else 
	  return PA_AccInvalt;
      
    };

  void GetUser()
    {
      
      Dec3bit(buff,4,10); //user
      std::string ret1=(*buff)[4].readS(9);
      std::string ret2;
      for (int a=0;a<=10;a++)
	{
	  if((ret1.c_str())[a]==0x00)break;
	  ret2+=(ret1.c_str())[a];
	  
	}
      user=ret2;
    }
  void GetPass()
    {
      
      Dec3bit(buff,14,10); //user
      std::string ret1=(*buff)[14].readS(9);
      std::string ret2;
      for (int a=0;a<=10;a++)
	{
	  if((ret1.c_str())[a]==0x00)break;
	  ret2+=(ret1.c_str())[a];
	  
	}
      pass=ret2;
    }
  
  
void Dec3bit(HexBuff *pck, int start, int len) 
  {
  unsigned char bs[] ={252, 207, 171};
  for (int i = start; i < start + len; i++)
    {
      (*pck)[i].writeC(((*pck)[i].readC() ^ bs[(i - start) % 3]));
    }
  std::cout << "   Derypt Done!!! \n";
  };
};

