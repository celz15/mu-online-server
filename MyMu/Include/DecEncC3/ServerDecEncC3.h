#ifndef SERVERDECENCC3_H_
#define SERVERDECENCC3_H_
#include "DecEncC3Keys.h" // klucze
#include "DecEncBase.h"
#include "HexBuffer/HexBuffer.h"
//urzycie :
//ServerDecEncC3 a=new ServerDecEncC3(buff)
//HexBuff H; // dekodowany
//a->getDec(&H);v// [pbiera kodowany
//a->getEnc(&h);	///pobierA dekodoaany
class ServerDecEncC3
{	
	HexBuff* buf; //buf do kodowania / dekodowania
	unsigned long * dec; // klucze
	unsigned long * enc; // klucze
public:
	ServerDecEncC3(HexBuff*h){
	buf=h;
	}
	virtual ~ServerDecEncC3(){};
	void getDec(HexBuff* dec)
	{
	};
	void getEnc(HexBuff* enc);
};

#endif /*SERVERDECENCC3_H_*/
