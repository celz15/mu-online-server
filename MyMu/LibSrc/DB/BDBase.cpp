/*
 * OpenMuServe
 *
 * Copyright (C) 2006 Dariusz Kie³kowski alians lardux
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

#include "DB/BDBase.h"
#include <string>
#include <iostream>
using std::cout;
using std::string;

BDBase::BDBase(string host, string user, string pass, string db_name)
{
	Error = false;
	P = mysql_init(NULL);
	if (!P)
	{
		printf("Blad przy ustawianu socket'a!\n");
		Error = true;
	};
	if (!mysql_real_connect(P, host.c_str(), user.c_str(), pass.c_str(),
			db_name.c_str(), 0, NULL, 0))
	{
		printf("|SYSTEM: DB: Blond podczas polaczenia do bazy danych: %s\n",
				mysql_error(P));
		Error = true;
	}
	else
	{
		printf("|SYSTEM: DB Connected... \n");
		cout << "|SYSTEM: DB Base done\n";
	};
}

BDBase::BDBase()
{
	Error = false;
	P = mysql_init(NULL);
	if (!P)
	{
		printf("Blad przy ustawianu socket'a!\n");
		Error = true;
	}
	if (!mysql_real_connect(P, "localhost", "mu_online", "mu", "mu_online", 0,
			NULL, 0))
	{
		printf("|SYSTEM: DB Blad prz podlaczeniu do bazy\n");
		Error = true;
	}
	else
	{
		Error = false;
		printf("|SYSTEM: DB Connected :> \n");
	};

}

BDBase::~BDBase()
{
	mysql_close(P);
}

bool BDBase::EnyError()
{
	return Error;
}
MYSQL * BDBase::GetDB()
{
	return P;
}

//bool BDBase::TestDB()
//{
//	string zapuser="SELECT COUNT(*) from 'users'";			//pytanei o ilosc userow
//	string zapchar="SELECT COUNT(*) from 'characters'";		//pytanie o ilosc postaci
//
//	mysql_query(GetDB(), zapuser.c_str());					//pytamy o userow
//
//};

bool BDBase::isConnected()
{
	return this->Error;
}
