#ifndef MUMAPS_
#define MUMAPS_
#include "MuObiects/MuMap.h"
#include "MuObiects/MuObjectsPool.h"
#include <vector>
#include "DB/BDBase.h"
//using std::vector;

class MuMaps
{
private:
  static MuMaps *_instance ;
protected:
  BDBase * BD;
  vector<MuMap*> mapList; // lista map w grze
public:
  static MuMaps* getInstance()
  {
    if(_instance ==NULL)
      {
	std::cout << "SYSTEM:> MAPS MNG NOT YET STARTED .... ERROR\n";
	exit(1);
      }
    else
      {
	return _instance;
      }
  };

  static MuMaps* InitInstance(BDBase *db)
  {
    if(_instance == NULL)
      {
	_instance = new MuMaps(db);
      }
    else
      {
	std::cout << "SYSTEM|> Starting to restart MuMaps Mng....\n";
	delete _instance;
	_instance =new MuMaps(db);
	std::cout << "SYSTEM:> MuMaps Mng Restarted ...\n";
      };
    return _instance;
  };

private:
  MuMaps(BDBase * db)
  {
    BD=db;
    std::cout << "SYSTEM MAPS MNG INIT						--RUN--\n\n";
    string zap="SELECT * FROM `maps`";
      
    if(!db->isConnected())
      {
	mysql_query(BD->GetDB(), zap.c_str());
	if (mysql_field_count(BD->GetDB())>0){
	  MYSQL_RES *wynik = mysql_store_result(BD->GetDB());
	  if (wynik!=NULL){
	    if (mysql_num_rows(wynik)>0){
	      for (int a=0; a<mysql_num_rows(wynik); a++){
		MYSQL_ROW wiersz = mysql_fetch_row(wynik);
		string opis=wiersz[1];
		int id=atoi(wiersz[2]);
		//adding new map
		AddNew(new MuMap(id,opis,BD));
	      }
	    }
	  }
	  mysql_free_result(wynik);
	}
      }
    else
      {
	printf("No Databasse Connection ... giong  swich to offDatabase\n"); 
	AddNew(new MuMap(0,"Lorencia",BD));
	AddNew(new MuMap(1,"Noria",BD));
      };
    std::cout << "\nTotal map init: " << getNMap()<<".\n";
    std::cout << "SYSTEM MAPS MNG INIT 						--DONE--\n\n";
  }; 
public:
  ~MuMaps(){};

  int getNMap()
  {
    return mapList.size();
  };
  void AddNew(MuMap*m)
  {
    if(m == NULL) std::cout << "FATAL ERROR LOST POINTER\n";
    else
      {
	std::cout <<">MAPSMNG: " << m->getName() << ": 						--ADD'ED--\n\n";  
	mapList.push_back(m);
      }
  };
  MuMap* getMap(int nr)
  {
      
    return mapList[nr];
  }; 
  void initMobs()
  {
    for (int t=0;t<mapList.size();t++)
      mapList[t]->InitMonstersSpot();
    ObiectPool::getInstance()->printUsages();
  };
  
};

extern MuMaps * MapsMng;

#endif /*MUMAPS_*/
