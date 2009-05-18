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




#ifndef BDBASE_H_
#define BDBASE_H_

#if defined(__WIN__)
  #include <winsock2.h>
  #include <mysql/mysql.h>
#eif defined(__MINGW32__)
  #include <mysql/mysql.h>
#else
#include <windows.h>
  #include <mysql/mysql.h>
#endif

#include <string>
using std::string;

class BDBase
{
       MYSQL * P; 
       bool Error; // jesli bald to koniec :(
       public:
       BDBase();
       BDBase(string host , string user , string pass,string db_name );
       ~BDBase();

       //metody
       MYSQL * GetDB();
       bool EnyError();
       bool isConnected();
};
#endif /*BDLOGIN_H_*/

