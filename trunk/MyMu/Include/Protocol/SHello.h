#ifndef SHELLO_H_
#define SHELLO_H_

#include "Protocol/SBPacket.h"

class SHello : public CSPacket
{
	std::string version;// wersja erwera
	int id_conneted;// id polaczenia
public:
	SHello(std::string v,int s):CSPacket(),version(v),id_conneted(s)
	{
		MyName="SC F100 Hello";
	};
	 ~SHello(){};
	HexBuff * build();
	void wyswietl();
};

#endif /*SHELLO_H_*/
