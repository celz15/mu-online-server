#ifndef HEXBUFFER_H_
#define HEXBUFFER_H_
#include <string>
class HexBuff
{
protected:
unsigned char buf[0xffff+1]; // bufer
int pos; // [pzycja do zapisu/odczytu
int size;// wielkosc buffora
//aktualizacja wielkosci pakietu;
void _a_size();
public:
	HexBuff();
	virtual ~HexBuff();
	
	// metody
	unsigned char * getPointer(){return buf;}
	//zapusu
	void writeC(const unsigned char c);					//zapisuje unsigned char		
	void writeAC(const unsigned char * b,int s);		//zapisuje const unsigned char *
	void writeAC(const  char * b,int s);				//zapisuje unsigned char
	void writeS(std::string s);							//zapisuje stringa
	void writeB(bool b);								//zapisuje bool
   	void writeHB(HexBuff hb,int s);						//zapisuje hexbuff						
	void writeI(int i,bool HiLo);						//zapisuje int
	void writeL(unsigned long l,bool HiLo);						//zapisuje long
	//odczytu
	const unsigned char readC();
	std::string readS(int i);
//TODO HexBuff readHB(int i){};
	int readI(bool HiLo=true);
	
	HexBuff & operator[](int i){pos=i;return *this;};
	//uchar& operator[](int a){return buf[a];};

	unsigned char * getAsSChar(){return buf;};
	
	//wyswietlanie
	protected:
	std::string _uchar2str(unsigned char h,std::string przed);
	public:
	//laduje do stringa zawartosc bufora w postac 0x00 gdzie '0x' to przed
	std::string buff2str(std::string przed="");
	int Size(){return size;};
        void setSize(int s){size=s;}; 
 void CryptMe(int from)
      {
      unsigned char t[1024];
    unsigned char key[]={
        0xe7,0x6D,0x3a,0x89,
        0xbc,0xB2,0x9f,0x73,
        0x23,0xa8,0xfe,0xb6,
        0x49,0x5d,0x39,0x5d,
        0x8a,0xcb,0x63,0x8d,
        0xea,0x7d,0x2b,0x5f,
        0xc3,0xb1,0xe9,0x83,
        0x29,0x51,0xe8,0x56};
     unsigned char T1;//temp
   
	 int a=from;
     for(int i=0;i<=size;i++,a++)
   	  {             //cout <<"a=" << a << "\n";
			if(a==32)a=0;
             T1=key[i+3]^buf[i+2];
             t[i+3]=buf[i+3]^T1;
	    };
  for (int a=from;a<=size;a++)buf[a]=t[a];

};

void DecryptMe(int from)
{
if (size<=0)return ;
     unsigned char key[]={
        0xe7,0x6D,0x3a,0x89,
        0xbc,0xB2,0x9f,0x73,
        0x23,0xa8,0xfe,0xb6,
        0x49,0x5d,0x39,0x5d,
        0x8a,0xcb,0x63,0x8d,
        0xea,0x7d,0x2b,0x5f,
        0xc3,0xb1,0xe9,0x83,
        0x29,0x51,0xe8,0x56};
    unsigned char decrypt[1024]; 
 	unsigned char T1;//templ
 	int a=from;
 	for(int i=0;i<=size-1;i++,a++)
 		{	  
 			if (a == 32)a=0;
  			T1=(buf[i+2])^(key[a]);
  			(decrypt)[i+3]=((buf)[i+3])^(T1);
		};     
for(int c=from;c<=size-1;c++)buf[c]=decrypt[c];
};


//troche pomocnych funkcji .. 
unsigned char getType1Pack();
unsigned char getType2Pack();
unsigned char getHeaderType();

void AddEnd00(){
	buf[size]=0x00;
}
};

#endif /*HEXBUFFER_H_*/

