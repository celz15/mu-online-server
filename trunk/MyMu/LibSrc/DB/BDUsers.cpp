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
 
#include "DB/BDUsers.h"
#include <string>
#include <iostream>
#include <stdlib.h>
using std::string;


BDUsers::BDUsers(int id, BDBase * bd)
{
	//std::cout <<"dbuser con b\n";
	ID=id;
	
//std::cout <<"1";
	BD=bd;
//	std::cout<<"2";
	GetIds();
//	std::cout<<"po con\n";
};

BDUsers::BDUsers(BDBase *bd)
{
  BD=bd;
};
void BDUsers::SetId(int i)
{
  ID=i;
  GetIds();
};
BDUsers::BDUsers()
{
	BD=new BDBase();
}

BDUsers::~BDUsers()
{

}

bool BDUsers::EnyError()
{
     return BD->EnyError();
};


bool BDUsers::GetIds ()
{
	string lan, tmp1;
	char tmp2[10];
	sprintf(tmp2, "%d", ID);
	tmp1=tmp2;
	lan="select ch_id from characters where ch_user="+tmp1;
	mysql_query(BD->GetDB(), lan.c_str());
	for (int a=0; a<4; a++)
	{
	//std::cout <<"a="<<a<<"\n";
		characters_id[a]=0;
	}
	
	if (mysql_field_count(BD->GetDB())>0)
	{
		MYSQL_RES *wynik = mysql_store_result(BD->GetDB());
		if (wynik!=NULL)
		{
			if (mysql_num_rows(wynik)>0)
			{
				for (int a=0; a<mysql_num_rows(wynik); a++)
				{
					MYSQL_ROW wiersz = mysql_fetch_row(wynik);
					characters_id[a]=atoi(wiersz[0]);
				}
				mysql_free_result(wynik);
				return true;
			}
		}
		mysql_free_result(wynik);
	}
	return false;
			
}



//wywolanie:
////id=id usera ktory sie zalogowal
////nr=nr postaci, od 0 do 4
_listCharacter BDUsers::GetCharacter(int nr)
{
        _listCharacter postac;
        string lan, t2;
	    char tmp2[10];
        sprintf(tmp2, "%d", characters_id[nr-1]);
        t2=tmp2;
        lan="select * from characters where ch_id="+t2;
        mysql_query(BD->GetDB(), lan.c_str());
        if (mysql_field_count(BD->GetDB())>0)
        {
		MYSQL_RES *wynik = mysql_store_result(BD->GetDB());
                if (wynik!=NULL)
                {
			if (mysql_num_rows(wynik)>0)
                        {
         	               MYSQL_ROW wiersz = mysql_fetch_row(wynik);
                               postac.nr=ID;
                               postac.Nick=wiersz[2];
                               postac.klasa=(unsigned char)wiersz[3][0];
                               postac.lvl=atoi(wiersz[4]);
                               mysql_free_result(wynik);
                               return postac;
                        }
                }
		mysql_free_result(wynik); 
	}
std::cout <<"nr: "<< postac.nr << "nick:" << postac.Nick <<"/n";
}


bool BDUsers::DeleteCharacter(string nick)
{
        string lan, tmp;
        char tmp1[11];
        sprintf(tmp1, "%d", ID);
	tmp=tmp1;
        lan="delete from characters where ch_user='"+tmp+"' and ch_name='"+nick+"'";
        if (mysql_query(BD->GetDB(), lan.c_str())==0)
        {
                return true;
        }
	else
	{
		return false;
	}
						
}


bool BDUsers::NewCharacter(_listCharacter ch)
{
	bool wynik=false;
	string lan, tmp, klasa;
        char tmp1[11];
        sprintf(tmp1, "%d", ID);
        tmp=tmp1;
	klasa=ch.klasa;
        lan="insert into characters set ch_user='"+tmp+"', ch_name='"+ch.Nick+"', ch_class='"+klasa+"', ch_lvl=1";
	printf ("%s",lan.c_str());
        if (mysql_query(BD->GetDB(), lan.c_str())==0)
        {
                wynik=true;
	        lan="update users set u_characters=u_characters+1 where u_id='"+tmp+"'";
	        if (mysql_query(BD->GetDB(), lan.c_str())==0)
	        {
	                wynik=true;
	        }
		else
		{
			lan="delete from characters where ch_user='"+tmp+"' and ch_name='"+ch.Nick+"'";
			mysql_query(BD->GetDB(), lan.c_str());
			wynik=false;
		}
				
        }
	return wynik;
}




/*bool  BDUsers::GetAllBaseStats(BaseStats *b,int nr)
{
  	//TODO pobieranie z bd
  	// mozesz uzyc b->SetAllStats(short int s,short int a,short int v ,short int e , short int c=0);
  	// lub pojedynczo b->SetStr(short int);
	
        string lan, t1;
        char tmp1[10];
        sprintf(tmp1, "%d", characters_id[nr]);
        t1=tmp1;
        lan="select ch_str, ch_agi, ch_vit, ch_enr, ch_com  from characters where ch_id="+t1;
        mysql_query(BD->GetDB(), lan.c_str());
        if (mysql_field_count(BD->GetDB())>0)
	  {
	    MYSQL_RES *wynik = mysql_store_result(BD->GetDB());
	    if (wynik!=NULL)
	      {
		if (mysql_num_rows(wynik)>0)
		  {
		    MYSQL_ROW wiersz = mysql_fetch_row(wynik);
		    b->SetAllStats(atoi(wiersz[0]),atoi(wiersz[1]),atoi(wiersz[2]),atoi(wiersz[3]),atoi(wiersz[4]));
		    mysql_free_result(wynik);
		    return true;
		  }                         
	      }
	  
	mysql_free_result(wynik);
	  }
return false;
}
*/
