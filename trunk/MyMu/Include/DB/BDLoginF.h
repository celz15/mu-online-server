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
 
#ifndef BDLOGIN_H_
#define BDLOGIN_H_
#include "DB/BDBase.h"
#include <string>
using std::string;

enum flag_ls {
       OK=0, // moze sie zalogowac
       Loged=1,// zalogowany juz
       Blocked=2// zablokowany
};

typedef struct login_info {
       int id;
       string user;
       string pass;
       flag_ls flag;
       int HCHar; // how many chars have ?
}login_info;

class BDLoginF
{
	std::string use;
	std::string pas;
	unsigned char f;
	int id;
	int ile_c;

      BDBase * BD;
       public:
       BDLoginF();
       BDLoginF(BDBase *d);
       ~BDLoginF();

       //metody
       bool IsUser(string login);
       void GetUser(string nick,login_info*i);
       bool NewUser(login_info);
       bool DelteUser(login_info);
       bool setFlag(string login, flag_ls);
       bool EnyError();
};
#endif /*BDLoginF_H_*/

