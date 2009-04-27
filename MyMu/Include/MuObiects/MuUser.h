#ifndef MU_USER_H
#define MU_USER_H
#include <string>
 
class MuUser{
std::string _user;							//nazwa urzytkownika
std::string _pass;							//haslo urzytkownika
int DBID; 									//id do bd
int _flag; 									//flaga polaczenia
int _charCount; 							//ilosc postaci posiadanych
public:
MuUser(std::string user,std::string pass,int ch_c,int dbid)
{
_user=user;
_pass=pass;
_charCount=ch_c;
DBID=dbid;

}
virtual ~MuUser(){}
void Read(){//pobieram teraz z bazy danych kozystajac z tego ze BDBase jest extern
}
void Write(){//zapisuje teraz ? do bazy danych
};
std::string getUser(){return _user;};
std::string getPass(){return _pass;};
int getFlag(){return _flag;}; 
int getCharCount(){return _charCount;};
int getDBID(){return DBID;};
};
#endif
