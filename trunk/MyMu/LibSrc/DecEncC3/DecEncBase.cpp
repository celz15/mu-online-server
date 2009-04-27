//#include "DecEncC3/DecEncC3Keys.h"
#include "DecEncC3/DecEncBase.h"

int DecC3Bytes(unsigned char*Dest,unsigned char*Src,unsigned long*Keys)
{
//	ZeroMemory(Dest,8);
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

int DecryptC3(unsigned char*Dest,unsigned char*Src,int Len,unsigned long*Keys)
{
	if(Dest==0)
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


int HashBuffer(unsigned char*Dest,int Param10,unsigned char*Src,int Param18,int Param1c)
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

int EncryptC3(unsigned char*Dest,unsigned char*Src,int Len,unsigned long*Keys)
{
	if(Dest==0)
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
void EncC3Bytes(unsigned char*Dest,unsigned char*Src,int Len,unsigned long*Keys)
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


