#include "Protocol/SBPacket.h"
#include <iostream>
using std::cout;
SBPacket::SBPacket()
{

	h = new HexBuff;
}

SBPacket::~SBPacket()
{

	delete h;
}

void SBPacket::wyswietl()
{
	cout << h->buff2str("0x") << "\n";
}

void CSPacket::mC1Header(unsigned char ptyp, int size)
{

	(*h)[0].writeC(0xc1);
	(*h)[1].writeC(size);
	(*h)[2].writeC(ptyp);
}
void CSPacket::mC2Header(unsigned char ptyp, int size)
{
	(*h)[0].writeC(0xc2);
	(*h)[1].writeI(size, true);
	(*h)[3].writeC(ptyp);
}

void CSPacket::mC3Header(unsigned char ptyp, int size)
{

	(*h)[0].writeC(0xc3);
	(*h)[1].writeC(size);
	(*h)[2].writeC(ptyp);
}
void CSPacket::mC4Header(unsigned char ptyp, int size)
{
	(*h)[0].writeC(0xc4);
	(*h)[1].writeI(size, true);
	(*h)[3].writeC(ptyp);
}

//twozenie z podwujnych typow
void CSPacket::mC1Header(unsigned char ptyp, unsigned char p1typ, int size)
{
	(*h)[0].writeC(0xc1);
	(*h)[1].writeC(size);
	(*h)[2].writeC(ptyp);
	(*h)[3].writeC(p1typ);
}

void CSPacket::mC2Header(unsigned char ptyp, unsigned char p1typ, int size)
{
	(*h)[0].writeC(0xc2);
	(*h)[1].writeI(size, true);
	(*h)[3].writeC(ptyp);
	(*h)[4].writeC(p1typ);
}

void CSPacket::mC3Header(unsigned char ptyp, unsigned char p1typ, int size)
{
	(*h)[0].writeC(0xc3);
	(*h)[1].writeC(size);
	(*h)[2].writeC(ptyp);
	(*h)[3].writeC(p1typ);
}

void CSPacket::mC4Header(unsigned char ptyp, unsigned char p1typ, int size)
{
	(*h)[0].writeC(0xc4);
	(*h)[1].writeI(size, true);
	(*h)[3].writeC(ptyp);
	(*h)[4].writeC(p1typ);
}

