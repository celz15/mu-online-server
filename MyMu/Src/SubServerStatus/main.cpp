#include "Socket/SocketWin32.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string host="google.pl";
	hostent *he;
	if ((he = gethostbyname(host.c_str())) == 0) {
    cout <<"niewlasciwy host \n";
  }
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(80);
  addr.sin_addr = *((in_addr *)he->h_addr);
  memset(&(addr.sin_zero), 0, 8); 
  
	char  ent[2];
	for (;;)
	{
	cout << "Menu:\n1 polacz\n2 Rozlacz\n3 wyswitl suby\n4 wyswietl 1p uba 1\n\nq exit\n";
	std::cin >>ent;
	if (ent[0]=='q') break;	
	};
};
