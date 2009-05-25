/* OpenMuServe
*
 
* Copyright (C) 2006 Michal Kinasiewicz alians MiKiOnE
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */   
//#include <iostream>					//cout
#if defined (__WIN__)||defined(__MINGW32__)
 
#include "Socket/SocketWin32.h"			//Sockt
 
#else
 
#include "Socket/SocketUnix.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <string>
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif 

#include "Encryption/encryption.h"		//kodowanie dekodowanie 
#include "IdFactory.h"					//IdFactory-przydzielanei id'ow 
#include "Server/MuClientTheard.h"		//obsluga klijenta 
#include "DB/BDBase.h"					//Baza danych 
#include "MuObiects/MuMaps.h"			//mapy w grze 
#include "MuObiects/MuMonsterInstance.h"//potworek:P 
#include "MuObiects/MuItemInstance.h"	//itemy na ziemi 
#include "MuObiects/MuNpcTemplate.h" 
#include "MuObiects/MuItemT.h"
#ifdef USE_PYTHON 
#include <python/python.h> 
#endif // USE_PYHON 
 
//komende gm i userow 
#include "AdminTools/ACommandMng.h" 
#include "AdminTools/AComTest.h" 
#include "AdminTools/AHelp.h"
#include "AdminTools/AInfo.h"
#include "AdminTools/AMapsMng.h"
#include "AdminTools/AComRunPy.h" 
using std::cout; 

#define GSPORT 55901
#define GSCHATPORT 55990
#if  !defined (__WIN__)||defined(__MINGW32__)
 #define BACKLOG 10


void sigchld_handler(int s)
{
  //while(waitpid(-1, NULL, WNOHANG) > 0);
}

#endif

static BDBase *BD; 

static ACommandMng* Commands;


//static ServerCore *SC;
UrandGen IdFactory;
Encryption Enc;


class tetstask:public Job
{
public:
  tetstask()
  {
    opis="test dzialanie task core";
  };
 
  void Run()
  {
    std::cout << ">SYSTEM TASK TEST DONE\n";
  };
};
#if defined(__WIN__)||defined(__MINGW32__)
DWORD WINAPI TaskThread(LPVOID lpParam)
#else
  void *TimeTask(void *arg)
#endif
{ 
  Task::Instance()->Run();
        
};

#if defined (__WIN__)||defined (__MINGW32__)
DWORD WINAPI ClientThread1(LPVOID lpParam)
#else
  void * ClientThread1(void * lpParam)
#endif
{

  cout << "\nCLIENT THERATT INIT ... \n";

#if defined (__WIN__)||defined (__MINGW32__)
  SocketWin32 WS((SOCKET)lpParam);
#else
  SocketUnix WS(*((int *)lpParam));
#endif
  cout << "SOCKET INIT DONE ... \n";
  MuClientTheard * th=new MuClientTheard(&WS,BD);
  th->setMe(th);
  cout << "CLIENTMNG INIT DONE ... \n";	
  //sth->initCommans(Commands->getCommandListFor(100)); 		//wszystkie komendy
  cout << "Runing Client ... \n";
  th->Run();
  cout << "Closing Client ... \n";
  cout << "Cleaning Client ... \n";
  unsigned short id = th->getConnectID();
  // th->SaveCharacterInDb();
  delete th;
  ObiectPool::getInstance()->returnId(id);
  std::cout << "ClientTheard Closed... \n\n";
};

#if !defined (__WIN__)

void *GsAccept(void * t)
{
 
  int c_w=0;
  int sockfd,new_fd;
  struct sockaddr_in my_addr;
  struct sockaddr_in their_addr;
  socklen_t sin_size;
  struct sigaction sa;
  int yes =1;
  if ((sockfd = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP)) ==-1){
    perror("socket");
    exit(1);
  }

  if(setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &yes,sizeof (int))==-1){
    perror("setSockopt");
    exit(1);
  }

  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(GSPORT);
  my_addr.sin_addr.s_addr=INADDR_ANY;
  memset(&(my_addr.sin_zero),'\0',8);

  if (bind (sockfd,(struct sockaddr * ) & my_addr,sizeof(struct sockaddr)) ==-1)
    {
      perror ("bind");
      cout << "errrrorrr!!!\n";
      //      exit(1);
    }
  if(listen(sockfd,BACKLOG) ==-1)
    {
      perror("listen");
      //      exit(1);
    }

  sa.sa_handler = sigchld_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags=SA_RESTART;
  if(sigaction (SIGCHLD,&sa,NULL)==-1)
    {
      perror("sigaction");
      exit(1);
    }
  while(1)
   

    {
      sin_size = sizeof(struct sockaddr_in);
      if((new_fd = accept(sockfd,(struct sockaddr *)&their_addr,&sin_size))==-1)
	{
	  perror("accept");
	  continue;
	}
      printf("|>SERVER:got connection from %s\n",inet_ntoa(their_addr.sin_addr));
      pthread_create(new pthread_t,0,ClientThread1,&new_fd);
    }
};

#else

DWORD WINAPI GSAccept(LPVOID lpParam)
{
  // winsocket 2.2 setup
  WSADATA wsd;
  SOCKET sListen, 
    sClient;
  int iAddrSize;
  HANDLE hThread;
  
  DWORD dwThreadID;
  
  struct sockaddr_in local, client; 
  struct hostent *host = NULL;
  
  // inicjuj Winsock 2.2  
  if (WSAStartup(MAKEWORD(2,2), &wsd) != 0) 
    { 
      printf("B³¹d ³adowania Winsock 2.2!\n"); 
      return 1; 
    } 
   
  // twórz gniazdo do nas³uchu po³¹czeñ klientów 
  sListen = socket(AF_INET, SOCK_STREAM, 0); 
  if (sListen == SOCKET_ERROR)  
    { 
      printf("B³¹d funkcji socket(): %d\n", WSAGetLastError()); 
      return 1; 
    } 

  // wybierz interfejs (warstwê komunikacyjn¹) 
  local.sin_addr.s_addr = htonl(INADDR_ANY); 
  local.sin_family = AF_INET; 
  local.sin_port = htons(GSPORT);  
  if (bind(sListen, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR) 
    { 
      printf("B³¹d funkcji bind(): %d\n", WSAGetLastError()); 
      return 1; 
    } 
   
   
  // nas³uch 
  host = gethostbyname("localhost"); 
  if (host == NULL) 
    { 
      printf("Nie uda³o siê wydobyæ nazwy serwera\n"); 
      return 1; 
    } 
   
  listen(sListen, 8); 
  printf("Serwer nas³uchuje.\n"); 
  printf("Adres: %s, port: %d\n", host->h_name, GSPORT); 
   
  // akceptuj nadchodz¹ce po³¹czenia 
  while (1) 
    { 
      iAddrSize = sizeof(client); 
      sClient = accept(sListen, (struct sockaddr *)&client, &iAddrSize); 
      if (sClient == INVALID_SOCKET) 
	{ 
	  printf("B³¹d funkcji accept(): %d\n", WSAGetLastError()); 
	  //return 1; 
	} 
      printf("Zaakceptowano po³¹czenie: serwer %s, port %d\n",  
	     inet_ntoa(client.sin_addr), ntohs(client.sin_port)); 
      hThread = CreateThread(NULL, 0, ClientThread1,(LPVOID)sClient, 0, &dwThreadID); 
      //    if (hThread == NULL) 
      //    { 
      //        printf("B³¹d funkcji CreateThread(): %d\n", WSAGetLastError()); 
      //       // return 1; 
      //    }  
      CloseHandle(hThread);  
    }  
  closesocket(sListen); 
}; 
#endif 
     
     
#if defined (__WIN__)||defined (__MINGW32__)
DWORD WINAPI GSChatAccept(LPVOID lpParam) 
{ 
  // winsocket 2.2 setup 
  WSADATA wsd; 
  SOCKET sListen, 
    sClient; 
  int iAddrSize; 
  HANDLE hThread; 
	       
  DWORD dwThreadID; 
		 
  struct sockaddr_in local, client;  
  struct hostent *host = NULL; 
		     
		     
		     
  // inicjuj Winsock 2.2  
  if (WSAStartup(MAKEWORD(2,2), &wsd) != 0) 
    { 
      printf("B³¹d ³adowania Winsock 2.2!\n"); 
      return 1; 
    } 
		       
  // twórz gniazdo do nas³uchu po³¹czeñ klientów 
  sListen = socket(AF_INET, SOCK_STREAM, 0); 
  if (sListen == SOCKET_ERROR)  
    { 
      printf("B³¹d funkcji socket(): %d\n", WSAGetLastError()); 
      return 1; 
    } 
			   
  // wybierz interfejs (warstwê komunikacyjn¹) 
  local.sin_addr.s_addr = htonl(INADDR_ANY); 
  local.sin_family = AF_INET; 
  local.sin_port = htons(GSCHATPORT);  
  if (bind(sListen, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR) 
    { 
      printf("B³¹d funkcji bind(): %d\n", WSAGetLastError()); 
      return 1; 
    } 
				   
				   
  // nas³uch 
  host = gethostbyname("localhost"); 
  if (host == NULL) 
    { 
      printf("Nie uda³o siê wydobyæ nazwy serwera\n"); 
      return 1; 
    } 
				       
  listen(sListen, 8); 
  printf("Serwer nas³uchuje.\n"); 
  printf("Adres: %s, port: %d\n", host->h_name, GSCHATPORT); 
					     
  // akceptuj nadchodz¹ce po³¹czenia 
  while (1)
    {
      iAddrSize = sizeof(client);
      sClient = accept(sListen, (struct sockaddr *)&client, &iAddrSize);
      if (sClient == INVALID_SOCKET)
	{
	  printf("B³¹d funkcji accept(): %d\n", WSAGetLastError());
	  //return 1;
	}
      printf("Zaakceptowano po³¹czenie: serwer %s, port %d\n", 
	     inet_ntoa(client.sin_addr), ntohs(client.sin_port));
      //hThread = CreateThread(NULL, 0, ClientThread1,(LPVOID)sClient, 0, &dwThreadID);
      //    if (hThread == NULL)
      //    {
      //        printf("B³¹d funkcji CreateThread(): %d\n", WSAGetLastError());
      //       // return 1;
      //    } 
      //CloseHandle(hThread); 
    } 
  closesocket(sListen);	
};
#endif
    
    
   
    
void SetUpGsStub()
{      
      
  std::cout << "\nDEC ENC INIT...\n";
#if defined (__WIN__)||defined (__MINGW32__)
  cout << ">> Loading decryption keys ...\n";
  if (!Enc.LoadKeys("./data/Dec1.dat",Enc.DecryptKeys)) {
    std::cerr << "Error: Failed to load Dec1.dat!\n" ;
   // return ;
  }
	    
  cout << ">> Loading encryption keys ...\n" ;
  if (!Enc.LoadKeys("./data/Enc2.dat",Enc.EncryptKeys)) {
    std::cerr << "Error: Failed to load Enc2.dat!\n" ;
   // return ;
  }
#endif
  cout << "Load Items definition\n";
  ItemInfoMng::Init("item.txt");
  ItemInfoMng::getInstance()->PrintMe();
		
#if defined(HAVE_PYTHON)
  cout << ">> INIT Python Core ... \n";
  Py_Initialize() ;
#endif 
		    
		    
#if defined (__WIN__)||defined (__MINGW32__)
  HANDLE hThread1;
  DWORD dwThreadID1;    
  hThread1 = CreateThread(NULL, 0, TaskThread,
			  (LPVOID)0, 0, &dwThreadID1);
			  
			  
  if (hThread1 == NULL)
    {
      printf("Error in create new theard: %d\n", WSAGetLastError());
	     return ;
	     }    
				
#else
			 
			 
	pthread_create(new pthread_t,0,TimeTask,NULL);
#endif
				
				
      Task::Instance()->AddJobA(new tetstask(),1);
				  
      //otwieranie BD;
      BD=new BDBase("localhost","mu_online","mu","mu_online");
      if(BD->EnyError()){cout << "Blad ladowania BDL.. cya :( \n";return ;};
      std::cout << "\n";
      //budujemy mapy w grze
      MuNpcTempMng::Init(BD);
      MuNpcTempMng::getNpcTempl(0);
      MuMaps::InitInstance(BD);
      std::cout << "\nMOBS INIT...\n";
      MuNpcTemplate m = MuNpcTempMng::getNpcTempl(238);
      MuMonsterInstance * mob1=ObiectPool::getInstance()->newMuMonsterInstance(m,130,127,0);
      MuMonsterInstance * mob2=ObiectPool::getInstance()->newMuMonsterInstance(m,130,128,0);
      MuMaps::getInstance()->initMobs(); 
      MuMaps::getInstance()->getMap(0)->storeNewObiect(mob1);
      MuMaps::getInstance()->getMap(0)->storeNewObiect(mob2);
						    
      std::cout << "MOBS INIT Done...\n";
						      
						      
      //inicjjemy komendy globalnt
      std::cout << "COMMANDMNG INIT \n";
      Commands=new ACommandMng();
      Commands->AddNew(new AComTest);
      Commands->AddNew(new AComandHelp);
      Commands->AddNew(new AInfo);
      Commands->AddNew(new AMapsMng);
      Commands->AddNew(new ARunPy);
      std::cout << "COMMANDMNG INIT DONE\n";
	
    };
    
    
  int main(int argc, char *argv[])
  {
    SetUpGsStub();
#if defined (__WIN__)||defined (__MINGW32__)
	
    HANDLE hTGS;
    HANDLE hTCGS;
    DWORD dwTGS;
    DWORD dwTCGS;
    hTGS = CreateThread(NULL, 0, GSAccept,
			(LPVOID)0, 0, &dwTGS);
    if (hTGS == NULL)
      {
	printf("B³¹d funkcji CreateThread(): %d\n", WSAGetLastError());
	return 1;
      }
#else
		     	     
    pthread_create(new pthread_t,0,GsAccept,NULL);
					  
#endif
    // tu bendzie komunikacja z innymi gs'ami i cs
    //	hTCGS = CreateThread(NULL, 0, GSChatAccept,
    //        (LPVOID)0, 0, &dwTCGS);
    //    if (hTCGS == NULL)
    //    {
    //        printf("B³¹d funkcji CreateThread(): %d\n", WSAGetLastError());
    //        return 1;
    //    }    
    std::string cmd;
    for(;;)
      {
	std::cout << "Emu:>";
	getline(std::cin,cmd);//(cmd.c_str(),);
	if (cmd=="exit") break;
	Commands->ParseComandLine(cmd,false);      
      }
    //GSAccept();
		    
#if defined (__WIN__)||defined (__MINGW32__)
    WSACleanup();
#endif
    return 0;
  
    system("pause");
  
#if defined (HAVE_PYTHON)
    Py_Finalize();
#endif
  }


