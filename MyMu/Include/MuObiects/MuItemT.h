#ifndef MUITEMT_H_
#define MUITEMT_H_
#include "HexBuffer/HexBuffer.h"

//troche predefinicji itemow
#define IT_OPTp4 0x01 // 00000001b
#define IT_OPTp8 0x02 // 00000010b
#define IT_LUCK  0x04 // 00000100b
#define IT_SKILL 0x80 // 10000000b
#define IT_LVL(x) (x)>>4 // 00001000b 1 lvl
#define IT_OPT(x) (x)   // 1..3
////exe bits		  
#define EXEOPT1   0x01 // 00000001b
#define EXEOPT2   0x02 // 00000010b
#define EXEOPT3   0x04 // 00000100b
#define EXEOPT4   0x08 // 00001000b
#define EXEOPT5   0x10 // 00010000b
#define EXEOPT6   0x20 // 00100000b
#define IT_p16    0x40 // 01000000b
#define IT_LONGID 0x80 // 10000000b
class MuItemT {
	
	unsigned char _item[4]; // item
public:	
MuItemT()
{
	for (int t=0;t<=4;t++)
	_item[t]=0x00;
}
~MuItemT(){}

void mBItem(int grupa,int index)							//twor\ymy podstawowy item
{
unsigned char t=0x00;		// temp
      t=grupa; 				// ustawiamy grupe
      t=t<<4;  				// przesuwamy id
      t=index; 				// ustawiamy 2 polowe bajtu
      if((grupa <<4)!=0)	// jesli dlugi id
      	addExeOp(0x80); 	// ustawiamy long id
      _item[0]=t;				// ustawaimy item	
};
void addExeOp(unsigned char exe)						//ustawimy Exe opcje
{
	_item[3]=_item[3]|exe;	//ustawiemy exe opcje
};

void addIncOpt(unsigned char opt)						//usawimy ainced / zestawowe opcje
{
	_item[4]=_item[4]|opt;	//ustawimy ain opcje
};


void Item(unsigned char*b)								//ustawiamy item z hexa
{
	_item[0]=b[0];	
	_item[1]=b[1];
	_item[2]=b[2];
	_item[3]=b[3];
};

void make5BItem(int pos,unsigned char *b)			//tworzymy5 bitowy item
{
	b[0]=pos;				//ustawiamy pozycje
	b[1]=_item[0];			//poprostu kopjujemy bity :p
	b[2]=_item[1];
	b[3]=_item[2];
	b[4]=_item[3];	
};
void get4BItem(unsigned char *i)
{
	i[0]=_item[0];
	i[1]=_item[1];
	i[2]=_item[2];
	i[3]=_item[3];
};

void setDur(unsigned char dur)
{
    _item[1]=dur;
};

void mItem(int gr,int ind,int dur,char op,char ain)
{
	mBItem(gr,ind);
	setDur(dur);
	addExeOp(op);
	addIncOpt(ain);
};

};

class MuItemBase
{
protected:
int _dura;					//wytrzymalosc
int _mdura;					//maxymalan wytrzymalosc
int _lvl;					//lvl itemu

unsigned char _item[4];		//ITEM
public:
MuItemBase()
{
	_item[0]=_item[1]=_item[2]=_item[3]=_item[4]=0x00;
};
~MuItemBase(){};
void setBItem(int grup,int index)
{
	unsigned char t=0x00;		// temp
      t=grup; 				// ustawiamy grupe
      t=t<<4;  				// przesuwamy id
      t=index; 				// ustawiamy 2 polowe bajtu
      if((grup <<4)!=0)	// jesli dlugi id
      	_item[3]=_item[3]|0x80; 	// ustawiamy long id
      _item[0]=t;				// ustawaimy item	
};
void setDura(int dura){_item[1]=dura;};  //ustawia wytrzymalosc
void setLvl(int lvl){_item[2]=_item[2]|((unsigned char)lvl>>4);};		//ustawia lvl itemu
void setOpt(int opt){_item[2]=_item[2]|(unsigned char)opt;};		//ustawia opcjeitemu like +4+8+12 itp
void resetOpt(){_item[2]=0x00;};
void setEOpt(int op){_item[3]=_item[3]|(unsigned char)op;};		//ustawia n'ta exe opcje like +exe dmg itp
void resetEOpt(){_item[3]=0x00;};
void setAOpt(int op){_item[4]=_item[4]|(unsigned char)op;};		//ustawia n'ta opcje aincedu
void resetAOpt(){_item[4]=0x00;};
void setSkill(){_item[2]=_item[2]|0x04;};			//ustawia skil
void setLuck(){_item[2]=_item[2]|0x80;};			//ustawia luck

int getIndex(){return 0;};	//pobiera index itemu
int getGrup(){return 0;};	//pobier grupe itemu
int getDura(){return _item[1];};   // pobiera wytrzymalosc
int getLvl(){return 0;};	// pobiera lvl itemu
int getOpt(){return 0;};	//pobiera opcje
bool getEOpt(int nr){return false;};
bool getAOpt(int nr){return false;};
bool getSkill(){return false;};
bool getLuck(){return false;};

void getHexItem(unsigned char * t)
{
	t[0]=_item[0];
	t[1]=_item[1];
	t[2]=_item[2];
	t[3]=_item[3];
	t[4]=_item[4];
};

void setHexItem(unsigned char * t)
{
	_item[0]=t[0];
	_item[1]=t[1];
	_item[2]=t[2];
	_item[3]=t[3];
	_item[4]=t[4];
};

void InsertInBuff(HexBuff* b , int pos)		//wstawianei iemu w hexbuff
{
	(*b)[pos].writeAC(_item,4);
};

};
class MuItemInInwentory:public MuItemBase
{
	protected:
	int _dbItemId;	//id w bd itemu 
	int _slot;		//slot w inw
	public:
	MuItemInInwentory(){};
	int getSlot(){return _slot;};
	int getDbItemId(){return _dbItemId;};

	void setSlot(int slot){_slot=slot;};
	void setDbItemId(int id){_dbItemId=id;};
	
	void resave(){};						//aktualizuje item w bd;
	void remove(){};						//usuwa item z bd;
	
};
#endif /*MUITEMT_H_*/
