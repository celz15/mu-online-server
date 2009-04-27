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
 * This library is distributaed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */ 

#include "DB/BDLoginF.h"
#include <iostream>
using std::cout;
BDLoginF::BDLoginF(BDBase *Db)
{
use="admin";
pas="admin";
id=1;
ile_c=0;
f=0;
BD=Db;
};

BDLoginF::BDLoginF()
{
BD=new BDBase();
}

BDLoginF::~BDLoginF()
{

}
bool BDLoginF::EnyError()
{
     return BD->EnyError();
};

bool BDLoginF::IsUser(std::string login)
{
       if(login.compare(0,login.size(),use)==0)return true; else return false;
}

void BDLoginF::GetUser(string login,login_info *l)
{
       login_info tmp;
		       l->id=id;
		       l->user=use;
		      l->pass=pas;
		      l->HCHar=ile_c;
		       
		       switch (f)
      			{
           		    case 0:l->flag=OK;     break;
	                case 1:l->flag=Loged;  break;
                    case 2:l->flag=Blocked;break;
		        }
}

bool BDLoginF::DelteUser(login_info l)
{
 return true;
 }


bool BDLoginF::setFlag(string login, flag_ls flagi)
{
    return true;
    }
	      



