#include "Protocol/SHello.h"
#include <iostream>
using std::cout;


//SHello::~SHello()
//{
//}

HexBuff *SHello::build()
{
//cout << "pocz build w hello\n";
//cout << h->Size()<<"\n";
	mC1Header(0xf1,0x00,0x0c);
//cout <<  h->Size()<<"\n";
	(*h)[4].writeC(0x01);
//cout <<  h->Size()<<"\n";
	(*h)[5].writeI(id_conneted,false);
//cout <<  h->Size()<<"\n";
	(*h)[7].writeS(version);
//cout <<  h->Size()<<"\n";
	(*h)[12].writeC(0x0);
//cout <<  h->Size()<<"\n";
//	cout << h->buff2str("")<<"\n"; 
	return h;
	
}
void SHello::wyswietl()
{
	cout << h->buff2str("0x") << "\n";
}; 
/*void LoginServer::PackServVersion(Hex * h,int id) // build package 00 ansve
{
Int Id(id);
 // tu musi byc id                             id1   id2
  uchar temp_[]={0xc1, 0x0c, 0xf1, 0x00, 0x01, Id.GetHi(), Id.GetLo(), 0x30, 0x39, 0x39, 0x32, 0x38};
  Hex pack(temp_,0x0b);
  //pack.Insert(si->GetVersion(),8);
  h->Set_D(pack,0x0b);
  */
