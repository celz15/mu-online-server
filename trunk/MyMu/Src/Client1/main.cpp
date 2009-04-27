#include <winsock2.h>
#include <string>
#include <iostream>
#include "Socket/SocketWin32.h"
using namespace std;
int main()
{
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
{
    printf("B³¹d ³adowania Winsock 2.2!\n");
    return 1;
}
SOCKET klient;
	string hoststr = "everwintermu.net";
	struct sockaddr_in sin;
	struct hostent *host;
//GetDlgItemText(hWnd,104,hoststr,sizeof(hoststr));
host=gethostbyname(hoststr.c_str());
cout << "host : "<< host << "\n";


memset( &sin, 0, sizeof (sin ));
sin.sin_family = AF_INET;
sin.sin_addr.s_addr = ((struct in_addr *)(host->h_addr))->s_addr;
sin.sin_port = htons(55557);
connect(klient,(struct sockaddr *) &sin, sizeof(sin));


	
};
