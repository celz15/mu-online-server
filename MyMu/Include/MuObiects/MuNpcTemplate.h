#pragma once
#include "DB/BDBase.h"

class MuNpcTemplate
{
public:
  unsigned char n_Class  ;
  unsigned char n_MonsterRate;  
  unsigned short n_Lvl;  
  char n_Name[20];        
  unsigned short n_StatMaxHp  ;
  unsigned short n_StatMaxMp  ;
  unsigned short n_DmgMax  ;
  unsigned short n_DmgMin;  
  unsigned short n_Devence  ;
  unsigned short n_MagicDevense;  
  unsigned char n_AttackRating;  
  unsigned char n_SuccesFullBLocking ; 
  unsigned char n_MoveRange;  
  unsigned char n_AttackType ;  
  unsigned char n_AttackRange;  
  unsigned char n_MoveSpeed;  
  unsigned char n_AttackSpeed;  
  unsigned char n_RegerenTime;  
  unsigned char n_Atrbution;  
  unsigned char n_ItemRate;  
  unsigned char n_MonyRate;  
  unsigned char n_MaxItemLvl;  
  unsigned char n_Skill1;  
  unsigned char n_Skill2  ;
  unsigned char n_Skill3  ;
  unsigned char n_Skill4;  
  unsigned char n_Skill5 ;
  unsigned char n_ViewRange;


};

class MuNpcTempMng
{
  BDBase * db_con;
  MuNpcTempMng(BDBase * db)
  {
    db_con = db;
  };
  static  MuNpcTempMng *_instance;
public:
  BDBase * getDB()
  {
    return db_con;
  };
  static MuNpcTempMng * getInstance()
  {
    return _instance;
  };
  static void Init(BDBase * db)
  {
    _instance = new MuNpcTempMng(db);
  };
  static MuNpcTemplate getNpcTempl(unsigned char id) 
  {
    MuNpcTemplate temp;
    char t[30]={0x00};
    sprintf(t,"select * from npcdata where n_Class = %d" , id);
    mysql_query(_instance->getDB()->GetDB(),t);
    MYSQL_RES * wynik = mysql_use_result(_instance->getDB()->GetDB());
    if(wynik!=NULL)
      {
	MYSQL_ROW w=mysql_fetch_row(wynik);
	temp.n_Class=atoi(w[0]);  
	temp.n_MonsterRate=atoi(w[1]);    
	temp.n_Lvl=atoi(w[2]);    
	strcpy(temp.n_Name,w[3]);        
	temp.n_StatMaxHp=atoi(w[4]);      
	temp.n_StatMaxMp=atoi(w[5]);        
	temp.n_DmgMax =atoi(w[6]);       
	temp.n_DmgMin  =atoi(w[7]);      
	temp.n_Devence  =atoi(w[8]);      
	temp.n_MagicDevense  =atoi(w[9]);      
	temp.n_AttackRating  =atoi(w[10]);      
	temp.n_SuccesFullBLocking  =atoi(w[11]);      
	temp.n_MoveRange  =atoi(w[12]);      
	temp.n_AttackType  =atoi(w[13]);      
	temp.n_AttackRange  =atoi(w[14]);
	temp.n_ViewRange  =atoi(w[15]);
	temp.n_MoveSpeed  =atoi(w[16]);      
	temp.n_AttackSpeed  =atoi(w[17]);      
	temp.n_RegerenTime  =atoi(w[18]);
	temp.n_Atrbution  =atoi(w[19]);      
	temp.n_ItemRate  =atoi(w[20]);      
	temp.n_MonyRate  =atoi(w[21]);      
	temp.n_MaxItemLvl  =atoi(w[22]);      
	temp.n_Skill1  =atoi(w[23]);      
	temp.n_Skill2  =atoi(w[24]);      
	temp.n_Skill3  =atoi(w[25]);      
	temp.n_Skill4  =atoi(w[26]);      
	temp.n_Skill5 =atoi(w[27]);      
	mysql_free_result(wynik);
      }else
      printf("error in DB:[%s]\n",t);
    return temp;
  };
};


