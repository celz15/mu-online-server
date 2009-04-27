#ifndef MUFRIENDMYLIST_H_
#define MUFRIENDMYLIST_H_
#include "MuFriendCharacter.h"
#include <vector> 

//zalozenia listama wygladac:
//-=-=-=-=-=- offline 1
//-=Console=- onlinr  1
//-=Events =- online  1
//-=debug  =- online  1
//-=-=-=-=-=- offline 1
//-=online-=-
//lista online
//-=offline=-
//lista offline
//-=wainting-
//lista oczeujacych na akceptacji

class MuFriendMyList
{
	protected:
	vector <MuFriendCharacter* > _friendAllList;
	public:
	vector <MuFriendCharacter* > getOnline()
	{
		vector <MuFriendCharacter* > temp;
		for(int i=0i< _friendAllList.size();i++)
		if(_friendAllList[i]->isOnline())temp.push_back(_friendAllList[i]);
		
		return temp;
	}; 
	//teoretycznie gdy user jest online i nie jest zaakceptowany to nie pokazujemy jego
	//statusu online :/
	vector <MuFriendCharacter* > getOffline()
	{
		vector <MuFriendCharacter* > temp;
		for(int i=0i< _friendAllList.size();i++)
		if(!_friendAllList[i]->isOnline())temp.push_back(_friendAllList[i]);
		return temp;
	};
	
	void AddNewFriend(MuFriendCharacter* c)
	{
		_friendAllList.push_back(c);
	};
	
	
	
};
#endif /*MUFRIENDMYLIST_H_*/
