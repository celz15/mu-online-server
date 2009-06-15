#ifndef MUITEMT_H_
#define MUITEMT_H_
#include "HexBuffer/HexBuffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

struct ItemHex
{
  unsigned char index;
  unsigned char options;  
  unsigned char duration; 
  unsigned char eoptions;
  unsigned char aoptions;
  void setIndex(unsigned char _grup,unsigned char _index)
  {
    index = 0x00;
    duration = 0x00;
    options = 0x00;
    eoptions=0x00;
    aoptions=0x00;

    //index=_grup  << 4;
    //index|=_index & 0x0F; 
    //if((_grup <<4)!=0) 
    //  {
    //eoptions|=IT_LONGID;
    // }


    //  if ((_grup > 0x0F) || (_index > 0x0F)) {
    //       return ;
    //   }
    unsigned char t =0x00;
    t |=  _grup<<4;
    t |=  _index;
    index = t;
      

  };
  void  makeItem(unsigned char _grup, unsigned char _index,
	   unsigned char _lvl,
	   unsigned char _duration,
	   unsigned char _options,
	   unsigned char _eoptions,
	   unsigned char _aoptions)
  {
    
    setIndex(_grup,_index);
    duration = _duration;
    options|=(_lvl<<3);
    options|=_options;
    eoptions|=_eoptions;
    aoptions|=_aoptions;
  };
};



class ItemInfoNode
{

public:
  unsigned char i_InfoGrup;
  unsigned char i_InfoIndex;
  //size
  unsigned char i_InfoHight;
  unsigned char i_InfoLenght;
  char i_InfoName[10];
  unsigned char i_InfoSerial0;
  unsigned char i_InfoSerial1;
  unsigned char i_InfoDrop;
  unsigned char i_InfoLvl;

  unsigned char i_InfoBaseDefence;
  unsigned char i_InfoBaseMagicDefence;
  unsigned char i_InfoBaseMinDmg;
  unsigned char i_InfoBaseMaxDmg;
  unsigned char i_InfoBaseSpeed;
  unsigned char i_InfoDuration;
  unsigned char i_InfoMagicDuration;
  unsigned char i_InfoLvlReq;
  unsigned char i_InfoStrReq;
  unsigned char i_InfoAglReq;
  unsigned char i_InfoEnrReq;
  unsigned char i_InfoDk;
  unsigned char i_InfoDw;
  unsigned char i_InfoEl;
  unsigned char i_InfoMg;
  int i_InfoZen;
  ItemHex i_BaseItem;
  
  void MakeBaseItem()
  {
    i_BaseItem.makeItem(i_InfoGrup,i_InfoIndex,0,i_InfoDuration,0,0,0);
  }
};

class ItemInfoMng
{
private:
  int ItemCount;
  static ItemInfoMng * _instance;
  ItemInfoNode * _items[0x0F][0x0f];
  ItemInfoMng()
  {
    ItemCount=0;
    for(int i =0; i<0x0f;i++)
      for (int j = 0 ; j<0x0f;j++)
	_items[i][j]=NULL;
  };
  ~ItemInfoMng(){}
public:
  static ItemInfoMng * getInstance()
  {
    return _instance;
  };

  ItemInfoNode * getInfo(unsigned char itemSection , unsigned char index)
  {
    return _items[itemSection][index];
  };

  static ItemInfoNode * getItemInfo(unsigned char itemSection , unsigned char index)
  {
    return _instance->getInfo(itemSection,index);
  }

  static void Init(std::string _path)
  {
    _instance = new ItemInfoMng();

    FILE * f = NULL;
    f = fopen(_path.c_str(),"rt");
    char line[120]={0};
    int section = -1;
    while(feof(f)==0)
      {
	fgets(line,120,f);
	if(line[0]=='/') continue;
	if(strlen(line)==1) continue;
	if(strlen(line)<4) 
	  {
	    section=atoi(line);
	    continue;
	  };
	if(strlen(line)==4) continue;
	if(section <=5)_instance->addWeapon(section,line);
	if(section ==6)_instance->addSheld(section,line);
	if((section >6) &&(section <12))_instance->addArmur(section,line);
	if(section == 12)_instance->addMisc(section,line);
	if(section ==13) _instance->addMisc1(section,line);
	if(section ==14) _instance->addPottion(section,line);
	if(section ==15) _instance->addScroll(section,line);
      };
  }



  void addScroll(unsigned char grup,char *line)
  {
    ItemInfoNode * i = new ItemInfoNode();
    if (strlen(line)<=0) return;
    i->i_InfoGrup=grup;
    i->i_InfoIndex=atoi( strtok(line,"\t"));
    i->i_InfoLenght=atoi( strtok(NULL,"\t"));
    i->i_InfoHight=atoi( strtok(NULL,"\t"));
    i->i_InfoSerial0= atoi( strtok(NULL,"\t"));
    i->i_InfoSerial1=atoi( strtok(NULL,"\t"));
    i->i_InfoDrop=atoi( strtok(NULL,"\t"));
    strcpy(i->i_InfoName,strtok(NULL,"\t"));
    i->i_InfoLvlReq=atoi( strtok(NULL,"\t"));
    unsigned char unk1=atoi( strtok(NULL,"\t"));
    i->i_InfoEnrReq=atoi(strtok(NULL,"\t"));
    i->i_InfoZen =atoi(strtok(NULL,"\t"));
    i->i_InfoDk=atoi( strtok(NULL,"\t"));
    i->i_InfoDw=atoi( strtok(NULL,"\t"));
    i->i_InfoEl=atoi( strtok(NULL,"\t"));
    i->i_InfoMg=atoi( strtok(NULL,"\t"));
    _items[grup][i->i_InfoIndex]=i;
    ItemCount++;
    i->MakeBaseItem();
  }

  void addPottion(unsigned char grup,char *line)
  {
    ItemInfoNode * i = new ItemInfoNode();
    if (strlen(line)<=0) return;
    i->i_InfoGrup=grup;
    i->i_InfoIndex=atoi( strtok(line,"\t"));
    i->i_InfoLenght=atoi( strtok(NULL,"\t"));
    i->i_InfoHight=atoi( strtok(NULL,"\t"));
    i->i_InfoSerial0= atoi( strtok(NULL,"\t"));
    i->i_InfoSerial1=atoi( strtok(NULL,"\t"));
    i->i_InfoDrop=atoi( strtok(NULL,"\t"));
    strcpy(i->i_InfoName,strtok(NULL,"\t"));
    i->i_InfoDuration=atoi( strtok(NULL,"\t"));
    i->i_InfoLvlReq=atoi( strtok(NULL,"\t"));
    _items[grup][i->i_InfoIndex]=i;
    ItemCount++;  
    i->MakeBaseItem();
  }

  void addMisc1(unsigned char grup,char *line)
  {
    ItemInfoNode * i = new ItemInfoNode();
    if (strlen(line)<=0) return;
    i->i_InfoGrup=grup;
    i->i_InfoIndex=atoi( strtok(line,"\t"));
    i->i_InfoLenght=atoi( strtok(NULL,"\t"));
    i->i_InfoHight=atoi( strtok(NULL,"\t"));
    i->i_InfoSerial0= atoi( strtok(NULL,"\t"));
    i->i_InfoSerial1=atoi( strtok(NULL,"\t"));
    i->i_InfoDrop=atoi( strtok(NULL,"\t"));
    strcpy(i->i_InfoName,strtok(NULL,"\t"));
    i->i_InfoLvl=atoi( strtok(NULL,"\t"));
    i->i_InfoDuration=atoi( strtok(NULL,"\t"));
    i->i_InfoLvlReq=atoi( strtok(NULL,"\t"));
    unsigned char unk1=atoi(strtok(NULL,"\t"));
    unsigned char unk2=atoi(strtok(NULL,"\t"));
    unsigned char unk3=atoi(strtok(NULL,"\t"));
    unsigned char unk4=atoi(strtok(NULL,"\t"));
    i->i_InfoDk=atoi( strtok(NULL,"\t"));
    i->i_InfoDw=atoi( strtok(NULL,"\t"));
    i->i_InfoEl=atoi( strtok(NULL,"\t"));
    i->i_InfoMg=atoi( strtok(NULL,"\t"));
    _items[grup][i->i_InfoIndex]=i;
    ItemCount++;  
    i->MakeBaseItem();
  }

  void addMisc(unsigned char grup,char * line)
  {
    ItemInfoNode * i = new ItemInfoNode();
    if (strlen(line)<=0) return;
    i->i_InfoGrup=grup;
    i->i_InfoIndex=atoi( strtok(line,"\t"));
    i->i_InfoLenght=atoi( strtok(NULL,"\t"));
    i->i_InfoHight=atoi( strtok(NULL,"\t"));
    i->i_InfoSerial0= atoi( strtok(NULL,"\t"));
    i->i_InfoSerial1=atoi( strtok(NULL,"\t"));
    i->i_InfoDrop=atoi( strtok(NULL,"\t"));
    strcmp(i->i_InfoName,strtok(NULL,"\t"));
    i->i_InfoLvl=atoi( strtok(NULL,"\t"));
    i->i_InfoBaseDefence=atoi( strtok(NULL,"\t"));
    i->i_InfoDuration=atoi( strtok(NULL,"\t"));
    i->i_InfoLvlReq=atoi( strtok(NULL,"\t"));
    i->i_InfoEnrReq=atoi(strtok(NULL,"\t"));
    i->i_InfoStrReq=atoi( strtok(NULL,"\t"));
    i->i_InfoAglReq=atoi( strtok(NULL,"\t"));
    i->i_InfoZen =atoi(strtok(NULL,"\t"));
    i->i_InfoDk=atoi( strtok(NULL,"\t"));
    i->i_InfoDw=atoi( strtok(NULL,"\t"));
    i->i_InfoEl=atoi( strtok(NULL,"\t"));
    i->i_InfoMg=atoi( strtok(NULL,"\t"));
    _items[grup][i->i_InfoIndex]=i;
    ItemCount++; 
    i->MakeBaseItem();
  }

  void addArmur(unsigned char grup,char * line)
  {
    ItemInfoNode * i = new ItemInfoNode();
    if (strlen(line)<=0) return;
    i->i_InfoGrup=grup;
    i->i_InfoIndex=atoi( strtok(line,"\t"));
    i->i_InfoLenght=atoi( strtok(NULL,"\t"));
    i->i_InfoHight=atoi( strtok(NULL,"\t"));
    i->i_InfoSerial0= atoi( strtok(NULL,"\t"));
    i->i_InfoSerial1=atoi( strtok(NULL,"\t"));
    i->i_InfoDrop=atoi( strtok(NULL,"\t"));
    strcmp(i->i_InfoName,strtok(NULL,"\t"));
    i->i_InfoLvl=atoi( strtok(NULL,"\t"));
    i->i_InfoBaseDefence=atoi( strtok(NULL,"\t"));
    i->i_InfoBaseMagicDefence=atoi( strtok(NULL,"\t"));
    i->i_InfoDuration=atoi( strtok(NULL,"\t"));
    i->i_InfoStrReq=atoi( strtok(NULL,"\t"));
    i->i_InfoAglReq=atoi( strtok(NULL,"\t"));
    i->i_InfoDk=atoi( strtok(NULL,"\t"));
    i->i_InfoDw=atoi( strtok(NULL,"\t"));
    i->i_InfoEl=atoi( strtok(NULL,"\t"));
    i->i_InfoMg=atoi( strtok(NULL,"\t"));
    _items[grup][i->i_InfoIndex]=i;
    ItemCount++;
    i->MakeBaseItem();
  }

  void addSheld(unsigned char grup,char * line)
  {
    ItemInfoNode * i = new ItemInfoNode();
    if (strlen(line)<=0) return;
    i->i_InfoGrup=grup;
    i->i_InfoIndex=atoi( strtok(line,"\t"));
    i->i_InfoLenght=atoi( strtok(NULL,"\t"));
    i->i_InfoHight=atoi( strtok(NULL,"\t"));
    i->i_InfoSerial0= atoi( strtok(NULL,"\t"));
    i->i_InfoSerial1=atoi( strtok(NULL,"\t"));
    i->i_InfoDrop=atoi( strtok(NULL,"\t"));
    strcmp(i->i_InfoName,strtok(NULL,"\t"));
    i->i_InfoLvl=atoi( strtok(NULL,"\t"));
    i->i_InfoBaseDefence=atoi(strtok(NULL,"\t"));
    i->i_InfoDuration=atoi( strtok(NULL,"\t"));
    i->i_InfoStrReq=atoi( strtok(NULL,"\t"));
    i->i_InfoAglReq=atoi( strtok(NULL,"\t"));
    i->i_InfoDk=atoi( strtok(NULL,"\t"));
    i->i_InfoDw=atoi( strtok(NULL,"\t"));
    i->i_InfoEl=atoi( strtok(NULL,"\t"));
    i->i_InfoMg=atoi( strtok(NULL,"\t"));
    _items[grup][i->i_InfoIndex]=i;
    ItemCount++;  
    i->MakeBaseItem();
  }



  void addWeapon(unsigned char grup , char * line)
  {
    if (strlen(line)<=0) return;
    ItemInfoNode * i = new ItemInfoNode();
    
    i->i_InfoGrup=grup;
    i->i_InfoIndex=atoi( strtok(line,"\t"));
    i->i_InfoLenght=atoi( strtok(NULL,"\t"));
    i->i_InfoHight=atoi( strtok(NULL,"\t"));
    i->i_InfoSerial0=atoi( strtok(NULL,"\t"));
    i->i_InfoSerial1=atoi( strtok(NULL,"\t"));
    i->i_InfoDrop=atoi( strtok(NULL,"\t"));
    strcpy(i->i_InfoName, strtok(NULL,"\t"));
    i->i_InfoLvl=atoi( strtok(NULL,"\t"));
    i->i_InfoBaseMinDmg=atoi( strtok(NULL,"\t"));
    i->i_InfoBaseMaxDmg=atoi( strtok(NULL,"\t"));
    i->i_InfoBaseSpeed=atoi( strtok(NULL,"\t"));
    i->i_InfoDuration=atoi( strtok(NULL,"\t"));
    i->i_InfoMagicDuration=atoi( strtok(NULL,"\t"));
    i->i_InfoStrReq=atoi( strtok(NULL,"\t"));
    i->i_InfoAglReq=atoi( strtok(NULL,"\t"));
    i->i_InfoDk=atoi( strtok(NULL,"\t"));
    i->i_InfoDw=atoi( strtok(NULL,"\t"));
    i->i_InfoEl=atoi( strtok(NULL,"\t"));
    i->i_InfoMg=atoi( strtok(NULL,"\t"));
    _items[grup][i->i_InfoIndex]=i;
    ItemCount++; 
    i->MakeBaseItem();
  };

  void PrintMe(){
    printf("ItemsInfoMng: [%d] Items Info storge\n",ItemCount);
  }
};
class ItemInInwentory
{

public:
  ItemInfoNode * inw_ItemInfo;
  unsigned long  inw_ItemSerial;
  unsigned char  inw_slot;
  unsigned char  inw_windowId;
  ItemHex        inw_ItemHex;

  void PrintMe()
  {
    printf("Item[grup:%d,Index:%d] [%s] in window[%d] at slot[%d] has DataBase id[%d]\n",inw_ItemInfo->i_InfoGrup,inw_ItemInfo->i_InfoIndex,
	   inw_ItemInfo->i_InfoName,inw_windowId,inw_slot,inw_ItemSerial);
  };
};




 
 
#endif /*MUITEMT_H_*/
