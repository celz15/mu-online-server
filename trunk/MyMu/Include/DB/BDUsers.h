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

#ifndef BDUSER_H
#define BDUSER_H
/*
 * klasy postaci
0x00 = DW
0x10 = SOUL MASTER
0x20 = DK
0x30 = BLADE KNIGHT
0x40 = ELF
0x50 = MUSE ELF
0x60 = MG
0x80 = DARK LORD
*/
#include "DB/BDBase.h"
 //#include "Server/BaseStats.h" 					// klasas ststystyk postaci
#include <string>
using std::string;

typedef struct _listCharacter{
	int nr; 						//which one on the list i'am
	string Nick;						//my nick
	short int lvl;						//my lvl
	unsigned char klasa;					//my class - knight, soul master etc.
};


class BDUsers
{           
        BDBase * BD;
        bool Error;              				//if any error, then program is ending
	int ID;							//id of user who is log in
	int characters_id[4];					//ids of all characters chosen user
	
        public:
        BDUsers();						//constructor
        BDUsers(int id, BDBase * b);				//constructor with parameters
	BDUsers(BDBase *b);
        ~BDUsers();						//destructor
	void SetId(int i);	       

	//gathering info
	bool GetIds ();						//reading characters id and put them into characters_id table
 	_listCharacter GetCharacter(int nr);			//get info about characters
   	bool DeleteCharacter(string nick);			//delete one character from chosen user
	bool NewCharacter( _listCharacter ch);		   	//adding one character for chosen user
	// 	bool GetAllBaseStats(BaseStats *b,int nr);		//read from base all stats
	bool EnyError();					//checking for errors

	//section items ;P
		
	//needed for delete
	string GetUserPrvCode ();	 			//reading from database code needed for delete user
};
#endif
