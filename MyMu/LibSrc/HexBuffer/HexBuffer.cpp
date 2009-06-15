#include "HexBuffer/HexBuffer.h"
#include <iostream>
#include <stdlib.h>
using std::cout;
HexBuff::HexBuff()
{

	pos = 0;
	size = 0;
}

HexBuff::~HexBuff()
{
}
const unsigned char HexBuff::readC()
{
	return buf[pos];

}

void HexBuff::writeB(bool b)
{
	if (b)
		buf[pos] = 0;
	else
		buf[pos] = 1;
	pos++;
	_a_size();
}
void HexBuff::writeI(int i, bool HiLo)
{
	if (HiLo)
	{
		buf[pos] = (i & 0xff);
		buf[pos + 1] = (i >> 8);
	}
	else
	{
		buf[pos + 1] = (i & 0xff);
		buf[pos] = (i >> 8);
	}
	pos += 2;
	_a_size();
}

void HexBuff::writeL(unsigned long l, bool HiLo)
{
	if (HiLo)
	{
		buf[pos] = (l & 0xff);
		buf[pos + 1] = (l >> 8 & 0xff);
		buf[pos + 2] = (l >> 16 & 0xff);
		buf[pos + 3] = (l >> 24 & 0xff);
	}
	else
	{
		buf[pos + 3] = (l & 0xff);
		buf[pos + 2] = (l >> 8 & 0xff);
		buf[pos + 1] = (l >> 16 & 0xff);
		buf[pos + 0] = (l >> 24 & 0xff);
	}
	pos += 4;
	_a_size();
}

void HexBuff::writeC(const unsigned char c)
{
	//cout <<"writeC B\n";
	buf[pos] = c

	;
	pos++;
	_a_size();

	//cout <<"writeC E\n";
}

int HexBuff::readI(bool HiLo)
{
	int i;
	if (HiLo)
		i = buf[pos] * 256 + buf[pos + 1];
	else
		i = buf[pos + 1] * 256 + buf[pos];
	pos += 2;
	return i;
}
void HexBuff::writeAC(const unsigned char * b, int s)
{
	for (int i = 0; i <= s; i++)
		buf[pos + i] = b[i];
	pos = pos + s;
	_a_size();
}
void HexBuff::writeAC(const char * b, int s)
{
	for (int i = 0; i <= s; i++)
		buf[pos + i] = b[i];
	pos = pos + s;
	_a_size();
}
void HexBuff::writeS(std::string s)
{

	for (unsigned int i = 0; i <= s.size(); i++)
		buf[i + pos] = s[i];
	pos += s.size();
	_a_size();
}
std::string HexBuff::readS(int i)
{
	std::string s;
	for (int a = 0; ((a <= i) && (buf[pos + a] != 0x00)); a++)
	{

		//cout <<"pos "<<pos+a<<"\n";
		s += (char) buf[pos + a];
	}
	return s;
	pos += i;
}

void HexBuff::writeHB(HexBuff hb, int s)
{
	if (s = -1)
	{
		for (int i = 0; i <= hb.Size(); i++)
			buf[pos + i] = (hb.getAsSChar())[i];

		pos = pos + hb.Size();

	}
	else
	{
		for (int i = 0; i <= s; i++)
			buf[pos + i] = (hb.getAsSChar())[i];
		pos = pos + s;
	};
	_a_size();
	//	for (int i=0;i<=s;i++)

	//	buf[pos+i]=hb.readC();
}

std::string HexBuff::_uchar2str(unsigned char h, std::string przed)
{
	char t[3];
	sprintf(t, "%x", char(h));
	std::string hex = t;
	if (hex.size() > 5)
		hex.erase(0, hex.size() - 2);
	if (hex.size() == 1)
		hex = przed + "0" + hex;
	if (hex.size() == 2)
		hex = przed + hex;
	return hex;
}

void HexBuff::_a_size()
{
	if (pos > size)
		size = pos;
}

std::string HexBuff::buff2str(std::string przed)
{
	std::string str = "";
	for (int a = 0; a <= size - 1; a++)
	{
		str += _uchar2str(buf[a], przed) + " ";
	};
	return str;
}

unsigned char HexBuff::getHeaderType()
{
	return buf[0];
}
unsigned char HexBuff::getType1Pack()
{
	switch (getHeaderType())
	{
	case 0xc1:
	case 0xc3:
		return buf[2];
		break;
	case 0xc2:
	case 0xc4:
		return buf[3];
		break;
	};
}
unsigned char HexBuff::getType2Pack()
{
	switch (getHeaderType())
	{

	case 0xc1:
	case 0xc3:
		return buf[3];
		break;
	case 0xc2:
	case 0xc4:
		return buf[4];
		break;
	};
}
