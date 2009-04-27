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

#include "DB/BDLogin.h"
#include <iostream>
#include <stdlib.h>
using std::cout;
BDLogin::BDLogin(BDBase *Db)
{
//cout << "SYSTeM dbLogin Done\n";
BD=Db;
if(BD==NULL)cout <<"Error nie mam wskaznika do bdbase\n";
};

BDLogin::BDLogin()
{
BD=new BDBase();
}

BDLogin::~BDLogin()
{

}
bool BDLogin::EnyError()
{
     return BD->EnyError();
};

bool BDLogin::IsUser(string login)
{
//cout <<"w isuser\n";
       string lan;
       lan="select * from users where u_login='"+login+"'";
//       cout <<"po ustawieni lan\n" ;
       mysql_query(BD->GetDB(), lan.c_str());
//       cout <<"po zapytani do bd\n";
       if (mysql_field_count(BD->GetDB())>0)
       {
       
               MYSQL_RES *wynik = mysql_store_result(BD->GetDB());
               if (wynik!=NULL)
               {
	   
                       if (mysql_num_rows(wynik)>0)
                       {
		
                               mysql_free_result(wynik);
                               return true;
                       }
               }
               mysql_free_result(wynik);
       }
       return false;
}

void BDLogin::GetUser(string login,login_info *tmp)
{
   
       string lan;
       lan="select * from users where u_login='"+login+"'";
       mysql_query(BD->GetDB(), lan.c_str());
       MYSQL_RES *wynik = mysql_use_result(BD->GetDB());
       if (wynik!=NULL)
       		{
		       MYSQL_ROW wiersz = mysql_fetch_row(wynik);
		       tmp->id=atoi(wiersz[0]);
		       tmp->user=wiersz[1];
		       tmp->pass=wiersz[2];
		       tmp->HCHar=atoi(wiersz[4]);
		       tmp->HCHar;
		       //cout << "w bd Chara=" << tmp->HCHar <<"\n";
		       switch (atoi(wiersz[3]))
      			{
           		    case 0:tmp->flag=OK;     break;
	                case 1:tmp->flag=Loged;  break;
                    case 2:tmp->flag=Blocked;break;
		        }
		       mysql_free_result(wynik);//zwalniamy wynik bo nikt po nas nie posprzata :(
       		}else cout <<"Blad: Nie istnieje taki user w bazie!!!\n";
       
}

bool BDLogin::DelteUser(login_info l)
{
        string lan, tmp;
	char tmp1[10];
	sprintf(tmp1, "%d", l.id);
	tmp=tmp1;
	bool wynik=false;
        lan="delete from users where u_login='"+l.user+"'";
        if (mysql_query(BD->GetDB(), lan.c_str())==0)
        {
                wynik=true;
        }
	lan="delete from characters where ch_user='"+tmp+"'";
	if (mysql_query(BD->GetDB(), lan.c_str())==0)
	{
		wynik=true;
	}
	return wynik;
}


bool BDLogin::setFlag(string login, flag_ls flagi)
{
        string lan;
        string tmp_s;
        switch (flagi)
        {
                case OK:tmp_s="0";        break;
                case Loged:tmp_s="1";     break;
                case Blocked:tmp_s="2";   break;
        }
        lan="update users set u_flags="+tmp_s+" where u_login='"+login+"'";
        if (mysql_query(BD->GetDB(), lan.c_str())==0)
        {
                return 1;
        }
        else
        {
                return 0;
        }
}
	      



