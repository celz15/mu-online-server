/*
** server.c -- a stream socket server demo
*/
//
// includki systemowe
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
// c++
#include "Task/Task.h"
#include <iostream>
using std::cout;
/// nasze
#include "DB/BDBase.h"          // bazadanych
#include "ConfFile/ConfFile.h"  // obsluga pliku konfiguracyjnego
#include "Socket/SocketUnix.h"
#include "Server/MuClientTheard.h"
#include "MuObiects/MuMaps.h"
#include "MuObiects/MuMonsterInstance.h"//potworek:P
#define MYPORT 55901	// the port users will be connecting to

#define BACKLOG 10	 // how many pending connections queue will hold
// statyczne zeczy

static  BDBase * BD;
static pthread_t **watki;
static MuMaps *Maps;
Task* TaskCore=new Task;
UrandGen IdFactory;



void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}


class Test:public Job
{
public:
void Run(){cout <<"test\n";};
};


void *funkcja_watku(void *arg)
{
  try{
    cout <<"przed...\n";
    int *psock=(int*)(arg);
    int  sock=*psock;
    SocketUnix SU(sock);
    MuClientTheard * th=new MuClientTheard(&SU,BD,Maps);
    th->setMe(th);
    cout << "przed wejsciem do run\n";
    th->Run();
    cout << "...po\n";
  }catch(exception&e)
    {
      cout<<"wyjatek :"<<e.what()<<"\n";
    };
};
void *TimeTask(void *arg)
{
  TaskCore->Run();
};

int main(void)
{
  int ile_w=0;
  int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
  struct sockaddr_in my_addr;	// my address information
  struct sockaddr_in their_addr; // connector's address information
  socklen_t sin_size;
  struct sigaction sa;
  int yes=1;
  
  //polaczenie \ bd:
  
  BD=new BDBase("localhost","mu_online","mu","mu_online");
  Maps=new MuMaps(BD);
  
  std::cout << " MOBS INIT...\n";
  MuMonsterIntance * mob1=new MuMonsterIntance(130,127,238,Maps->getMap(0),0);
  mob1->setOId(258);//IdFactory());//id
  mob1->setMType(4);
  mob1->setX(0x7f);//x
  mob1->setY(0x82);//y
  mob1->setId(10); //jakis potworek
  
  MuMonsterIntance * mob2=new MuMonsterIntance(130,128,238,Maps->getMap(0),0);
  mob2->setOId(101);//IdFactory());//id
  mob2->setMType(4);
  mob2->setX(148);//x
  mob2->setY(127);//y
  mob2->setId(238); //jakis potworek
  
  Maps->getMap(0)->storeNewObiect(mob1);
  Maps->getMap(0)->storeNewObiect(mob2);
  std::cout << " MOBS INIT Done...\n";
  
  
  
  pthread_create(new pthread_t,0,TimeTask,NULL);
  
  
  if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
    perror("socket");
    exit(1);
  }
  
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
  }
  
  my_addr.sin_family = AF_INET;		 // host byte order
  my_addr.sin_port = htons(MYPORT);	 // short, network byte order
  my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
  memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct
  
  if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
    perror("bind");
		exit(1);
  }
  
  if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
  }
  
  sa.sa_handler = sigchld_handler; // reap all dead processes
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }
  
  while(1) {  // main accept() loop
    sin_size = sizeof(struct sockaddr_in);
    if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
      perror("accept");
      continue;
    }
    printf("|>SERVER: got connection from %s\n",inet_ntoa(their_addr.sin_addr));
    pthread_create(new pthread_t,0,funkcja_watku,&new_fd); // twozymy watek
    
    
  }
  
  return 0;
};

