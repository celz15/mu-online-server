#ifndef MUFRIENDCHARACTER_H_
#define MUFRIENDCHARACTER_H_
#include <string>
class MuFriendCharacter
{
	protected:
	std::string _nick;			//nick freienda
	int 		_onServer;		//na jakim serwerze jesli 256 offline
	bool 		_akcepted;		//czy zaakcepowany
	bool		_system;		//czy systemowe np sellline czy konsola
	public:
	MuFriendCharacter(std::string nick,int server,bool accepted)
	{
		_nick=nick;
		_onServer=server;
		_akcepted=accepted;
		_system=false;
	};
	virtual ~MuFriendCharacter(){};
	
	
	//akcesory
	std::string getName(){return _nick;};
	int getServer(){return _onServer;};
	bool getStatus(){return _akcepted;};
	void setServer(int s){_onServer=s;};
	void setStatus(bool s){_akcepted=s;};
	
	//metody
	void FriendAkcept(){_akcepted =true;};
	void FriendNoAkcept(){_akcepted=false;};
	bool isAkcepted(){return _akcepted;};
	
	bool isOnline(){return _onServer !=0xff;};
	
	bool IsSystem(){return _system;};
	bool setSystem(bool s=true){_system=s;};
    
    virtual void Run(std::string msg) // po otrzymaniu wiadomoci 
    {
    	std::cout <<"wiadomosc chat'a :"<<msg<<"\n";
    };	
    
};




#endif /*MUFRIENDCHARACTER_H_*/
