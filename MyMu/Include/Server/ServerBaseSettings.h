#ifndef SERVERBASESETTINGS_H_
#define SERVERBASESETTINGS_H_
#include "DB/BDBase.h"
#include <string>
class ServerBaseSettings{
	std::string S_name;			//nazwa serwera
	int 		S_port;			//port
	int			S_maxU;			//max connected users
	
	public:
	ServerBaseSettings(BDBase * con)
	{
		std::string sql="select * from BaseSettings";    // pobieramy ustawienia 
	}

#endif /*SERVERBASESETTINGS_H_*/
