#ifndef DECENCBASE_H_
#define DECENCBASE_H_
#include "DecEncC3Keys.h"
#include "DecEncRollBits.h"
#include <fstream>
#include <iostream>
using std::cout;
using std::ofstream;
//#include "EncDec.h"

int DecryptC3(unsigned char*Dest,unsigned char*Src,int Len,unsigned long*Keys);
int DecC3Bytes(unsigned char*Dest,unsigned char*Src,unsigned long*Keys);
int HashBuffer(unsigned char*Dest,int Param10,unsigned char*Src,int Param18,int Param1c);
void ShiftBuffer(unsigned char*Buff,int Len,int ShiftLen);
int EncryptC3(unsigned char*Dest,unsigned char*Src,int Len,unsigned long*Keys);
void EncC3Bytes(unsigned char*Dest,unsigned char*Src,int Len,unsigned long*Keys);
//int DecC3Bytes(unsigned char*Dest,unsigned char*Src,unsigned long*Keys);
//
//unsigned char const C3Keys[]={0x9B,0xA7,0x08,0x3F,0x87,0xC2,0x5C,0xE2,
//							  0xB9,0x7A,0xD2,0x93,0xBF,0xA7,0xDE,0x20};
//unsigned char const C2Keys[]={0xE7,0x6D,0x3A,0x89,0xBC,0xB2,0x9F,0x73,
//							  0x23,0xA8,0xFE,0xB6,0x49,0x5D,0x39,0x5D,
//							  0x8A,0xCB,0x63,0x8D,0xEA,0x7D,0x2B,0x5F,
//							  0xC3,0xB1,0xE9,0x83,0x29,0x51,0xE8,0x56};
//unsigned char const LoginKeys[]={0xFC, 0xCF, 0xAB};
///////////////////////////////////////////////////////////////////////////////////
//unsigned long ClientDecryptKeys[12];
//unsigned long ClientEncryptKeys[12];
//unsigned long ServerDecryptKeys[12];
//unsigned long ServerEncryptKeys[12];
//bool ClientDecryptKeysLoaded=0;
//bool ClientEncryptKeysLoaded=0;
//bool ServerDecryptKeysLoaded=0;
//bool ServerEncryptKeysLoaded=0;

//int DecryptC3asClient(unsigned char*Dest,unsigned char*Src,int Len)
//{
//	if(!ClientDecryptKeysLoaded)
//		if(!LoadKeys("Dec2.dat",ClientDecryptKeys))
//			return 0;
//		else ClientDecryptKeysLoaded=1;
//	return DecryptC3(Dest,Src,Len,ClientDecryptKeys);
//}

//int EncryptC3asClient(unsigned char*Dest,unsigned char*Src,int Len)
//{
//	if(!ClientEncryptKeysLoaded)
//		if(!LoadKeys("Enc1.dat",ClientEncryptKeys))
//			return 0;
//		else ClientEncryptKeysLoaded=1;
//	return EncryptC3(Dest,Src,Len,ClientEncryptKeys);
//}
//int DecryptC3asServer(unsigned char*Dest,unsigned char*Src,int Len)
//{
//	if(!ServerDecryptKeysLoaded)
//		if(!LoadKeys("Dec1.dat",ServerDecryptKeys))
//			return 0;
//		else ServerDecryptKeysLoaded=1;
//		for (int a=0;a<=12;a++)cout<< ServerDecryptKeys[a] <<"\n";
//	return DecryptC3(Dest,Src,Len,ServerDecryptKeys);
//}
//int EncryptC3asServer(unsigned char*Dest,unsigned char*Src,int Len)
//{
//	if(!ServerEncryptKeysLoaded)
//		if(!LoadKeys("Enc2.dat",ServerEncryptKeys))
//			return 0;
//		else ServerEncryptKeysLoaded=1;
//	return EncryptC3(Dest,Src,Len,ServerEncryptKeys);
//}
//int LoadKeys(char*File,unsigned long*Where)
//{
//	unsigned char Buff[16];
//	HANDLE hFile=CreateFile(File,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL,NULL);
//	if((!hFile)||GetFileSize(hFile,0)!=54)
//		return 0;
//	unsigned long bytesRead;
//	SetFilePointer(hFile,6,0,FILE_BEGIN);
//	ReadFile(hFile,Buff,16,&bytesRead,0);
//	for(int i=0;i<4;i++)
//		Where[i]=((unsigned long*)C3Keys)[i]^((unsigned long*)Buff)[i];
//	ReadFile(hFile,Buff,16,&bytesRead,0);
//	for (int i=0;i<4;i++)
//		Where[i+4]=((unsigned long*)C3Keys)[i]^((unsigned long*)Buff)[i];
//	ReadFile(hFile,Buff,16,&bytesRead,0);
//	for (int i=0;i<4;i++)
//		Where[i+8]=((unsigned long*)C3Keys)[i]^((unsigned long*)Buff)[i];
//	CloseHandle(hFile);
//        return 1;
//}

//int newLoadKeys(char*File,unsigned long*Where)
//{
//	unsigned char Buff[16];
//	ofstream plik;
//	plik.open(File,std::ios::in|std::ios::binary);
//	if(!plik.is_open())
//	HANDLE hFile=CreateFile(File,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL,NULL);
//	if((!hFile)||GetFileSize(hFile,0)!=54)
//		return 0;
//	unsigned long bytesRead;
//	SetFilePointer(hFile,6,0,FILE_BEGIN);
//	ReadFile(hFile,Buff,16,&bytesRead,0);
//	for(int i=0;i<4;i++)
//		Where[i]=((unsigned long*)C3Keys)[i]^((unsigned long*)Buff)[i];
//	ReadFile(hFile,Buff,16,&bytesRead,0);
//	for (int i=0;i<4;i++)
//		Where[i+4]=((unsigned long*)C3Keys)[i]^((unsigned long*)Buff)[i];
//	ReadFile(hFile,Buff,16,&bytesRead,0);
//	for (int i=0;i<4;i++)
//		Where[i+8]=((unsigned long*)C3Keys)[i]^((unsigned long*)Buff)[i];
//	CloseHandle(hFile);
//        return 1;
//}

/*void DecXor32(unsigned char*Buff,int SizeOfHeader,int Len)
{
	for(int i=Len-1;i>=0;i--)
		Buff[i]^=(C2Keys[(i+SizeOfHeader)&31]^Buff[i-1]);
}
*/
//void EncXor32(unsigned char*Buff,int SizeOfHeader,int Len)
//{
//	for(int i=0;i<Len;i++)
//		Buff[i]^=(C2Keys[(i+SizeOfHeader)&31]^Buff[i-1]);
//}
//void EncDecLogin(unsigned char*Buff,int Len)
//{
//	for(int i=0;i<Len;i++)
//		Buff[i]=Buff[i]^LoginKeys[i%3];
//}
#endif /*DECENCBASE_H_*/
