/****************************************************************************
 * This program is free software; you can redistribute it and/or            *
 * modify it under the terms of the GNU General Public License              *
 * as published by the Free Software Foundation; either version 2           *
 * of the License, or (at your option) any later version.                   *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See                 *
 * the GNU General Public License for more details.                         *
 *                                                                          *
 * You should have received a copy of the GNU General Public License        *
 * along with this program; if not, write to the Free Software Foundation,  *
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.          *
 ****************************************************************************/

// Encryption/Decryption methods, thanks to _Hitman47 (at forum.ragezone.com) for the base functions

#include <iostream>
#include <fstream>
#include <string.h>
#include "Encryption/encryption.h"



using namespace std;

unsigned char Encryption::C3Keys[]={0x9B,0xA7,0x08,0x3F,0x87,0xC2,0x5C,0xE2,0xB9,
0x7A,0xD2,0x93,0xBF,0xA7,0xDE,0x20};
unsigned char Encryption::C2Keys[]={0xE7,0x6D,0x3A,0x89,0xBC,0xB2,0x9F,0x73,
							  0x23,0xA8,0xFE,0xB6,0x49,0x5D,0x39,0x5D,
							  0x8A,0xCB,0x63,0x8D,0xEA,0x7D,0x2B,0x5F,
							  0xC3,0xB1,0xE9,0x83,0x29,0x51,0xE8,0x56};
unsigned char Encryption::LoginKeys[]={0xFC, 0xCF, 0xAB};

int Encryption::DecryptC3(unsigned char*Dest,unsigned char*Src,int Len,unsigned long*Keys)
{
	if(Dest==0 || !keysLoaded)
		return 0;
	unsigned char *TempDest=Dest,*TempSrc=Src;
	int DecLen=0;
	if(Len>0)
		do
		{
			if(DecC3Bytes(TempDest,TempSrc,Keys)<0)
				return 0;
			DecLen+=11;
			TempSrc+=11;
			TempDest+=8;
		} while(DecLen<Len);
	return Len*8/11;
}

int Encryption::DecC3Bytes(unsigned char*Dest,unsigned char*Src,unsigned long*Keys)
{
	memset(Dest, 0,8);
	unsigned long TempDec[4]={0};
	int j=0;
	for(int i=0;i<4;i++)
	{
		HashBuffer((unsigned char*)TempDec+4*i,0,Src,j,16);
		j+=16;
		HashBuffer((unsigned char*)TempDec+4*i,22,Src,j,2);
		j+=2;
	}
	for(int i=2;i>=0;i--)
		TempDec[i]=TempDec[i]^Keys[8+i]^(TempDec[i+1]&0xFFFF);
	unsigned long Temp=0,Temp1;
	for(int i=0;i<4;i++)
	{
		Temp1=((Keys[4+i]*(TempDec[i]))%(Keys[i]))^Keys[i+8]^Temp;
		Temp=TempDec[i]&0xFFFF;
		((unsigned short*)Dest)[i] =(Temp1);
	}
	TempDec[0]=0;
	HashBuffer((unsigned char*)TempDec,0,Src,j,16);
	((unsigned char*)TempDec)[0]=((unsigned char*)TempDec)[1]^
		((unsigned char*)TempDec)[0]^0x3d;
	unsigned char XorByte=0xF8;
	for(int i=0;i<8;i++)
		XorByte^=Dest[i];
	if(XorByte!=((unsigned char*)TempDec)[1])
		return -1;
	else return ((unsigned char*)TempDec)[0];
}
int Encryption::HashBuffer(unsigned char*Dest,int Param10,unsigned char*Src,int Param18,int Param1c)
{
	int BuffLen=((Param1c+Param18-1)>>3)-(Param18>>3)+2;
	unsigned char *Temp=new unsigned char[BuffLen];
	Temp[BuffLen-1]=0;
	memcpy(Temp,Src+(Param18>>3),BuffLen-1);
	int EAX=(Param1c+Param18)&7;
	if(EAX)
		Temp[BuffLen-2]&=(0xff)<<(8-EAX);
	int ESI = Param18&7;
    int EDI=Param10&7;
	ShiftBuffer(Temp,BuffLen-1,-ESI);
	ShiftBuffer(Temp,BuffLen,EDI);
    unsigned char*TempPtr =(Param10>>3)+Dest;
	int LoopCount=BuffLen-1+(EDI>ESI);
	if(LoopCount)
		for(int i=0;i<LoopCount;i++)
			TempPtr[i] = TempPtr[i]|(Temp[i]);
	delete[] Temp;
	return Param10 + Param1c;
}
void Encryption::ShiftBuffer(unsigned char*Buff,int Len,int ShiftLen)
{
	if(ShiftLen)
	{
		if(ShiftLen>0)
		{
			if(Len-1>0)
				for (int i=Len-1;i>0;i--)
					Buff[i]=(Buff[i-1]<<(8-ShiftLen))|(Buff[i]>>(ShiftLen));
			Buff[0] = Buff[0]>>ShiftLen;
            return;
		}
		ShiftLen=-ShiftLen;
		if(Len-1>0)
			for(int i=0;i<Len-1;i++)
				Buff[i] =(Buff[i+1]>>(8-ShiftLen))|(Buff[i]<<ShiftLen);
		Buff[Len-1] = Buff[Len-1]<<ShiftLen;
	}
}
bool Encryption::LoadKeys(char*File,unsigned long*Where)
{
	unsigned char Buff[16];
	FILE *file=fopen(File, "rb");
	if(!file)
		return false;
	fseek(file, 6, SEEK_SET);
	fread((unsigned char*)Buff, 16, 1, file);
	for(int i=0;i<4;i++)
		Where[i]=((unsigned long*)C3Keys)[i]^((unsigned long*)Buff)[i];
	fread((unsigned char*)Buff, 16, 1, file);
	for (int i=0;i<4;i++)
		Where[i+4]=((unsigned long*)C3Keys)[i]^((unsigned long*)Buff)[i];
	fread((unsigned char*)Buff, 16, 1, file);
	for (int i=0;i<4;i++)
		Where[i+8]=((unsigned long*)C3Keys)[i]^((unsigned long*)Buff)[i];
	fclose(file);
	keysLoaded = true;
	return true;
}
int Encryption::EncryptC3(unsigned char*Dest,unsigned char*Src,int Len,unsigned long*Keys)
{
	if(Dest==0 || !keysLoaded)
		return 0;
	unsigned char *TempDest=Dest,*TempSrc=Src;
	int EncLen=Len;
	if(Len>0)
		do
		{
			EncC3Bytes(TempDest,TempSrc,(EncLen>7)?8:EncLen,Keys);
			EncLen-=8;
			TempSrc+=8;
			TempDest+=11;
		} while(EncLen>0);
	return Len*11/8;
}
void Encryption::EncC3Bytes(unsigned char*Dest,unsigned char*Src,int Len,unsigned long*Keys)
{
	unsigned long Temp=0,TempEnc[4];
	for(int i=0;i<4;i++)
	{
		TempEnc[i]=((Keys[i+8]^((unsigned short*)Src)[i]^Temp)*Keys[i+4])%Keys[i];
		Temp=TempEnc[i]&0xFFFF;
	}
	for(int i=0;i<3;i++)
		TempEnc[i]=TempEnc[i]^Keys[8+i]^(TempEnc[i+1]&0xFFFF);
	int j=0;
	memset(Dest, 0,11);
	for(int i=0;i<4;i++)
	{
		j=HashBuffer(Dest,j,(unsigned char*)TempEnc+4*i,0,16);
		j=HashBuffer(Dest,j,(unsigned char*)TempEnc+4*i,22,2);
	}
	unsigned char XorByte=0xF8;
	for(int i=0;i<8;i++)
		XorByte^=Src[i];
	((unsigned char*)&Temp)[1]=XorByte;
	((unsigned char*)&Temp)[0]=XorByte^Len^0x3D;
	HashBuffer(Dest,j,(unsigned char*)&Temp,0,16);
}
void Encryption::DecXor32(unsigned char*Buff,int SizeOfHeader,int Len)
{
	for(int i=Len-1;i>=0;i--)
		Buff[i]^=(C2Keys[(i+SizeOfHeader)&31]^Buff[i-1]);
}
void Encryption::EncXor32(unsigned char*Buff,int SizeOfHeader,int Len)
{
	for(int i=0;i<Len;i++)
		Buff[i]^=(C2Keys[(i+SizeOfHeader)&31]^Buff[i-1]);
}
void Encryption::EncDecLogin(unsigned char*Buff,int Len)
{
	for(int i=0;i<Len;i++)
		Buff[i]=Buff[i]^LoginKeys[i%3];
}
