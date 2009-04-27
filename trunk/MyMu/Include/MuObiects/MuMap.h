#ifndef MUMAP_H_
#define MUMAP_H_
#include <map>
#include <vector>
#include "MuObiects/MuObiect.h"
#include "DB/BDBase.h"
#include <stdlib.h>
#include <string>
class MuSpot
{
  unsigned char _bx;                      //begin x position of spot
  unsigned char _by;                      //begin y position of spot
  unsigned char _ex;                      //end x position of spot
  unsigned char _ey;                      //end y position of spot
  int _r;			//type of monster/npc on spot
  int _c;			//count of this id on spot
  std::string _name;            //name of the spot (optionaly)
public:
  MuSpot(std::string name,unsigned char bx,
	 unsigned char by,
	 unsigned char ex,unsigned char ey,int r,int c)
  {
    _name=name;
    _bx=bx;
    _by=by;
    _ex=ex;
    _ey=ey;
    _r=r;
    _c=c;
    if(_bx>_ex)
      {
	unsigned char t= _bx;
	_bx=_ex;
	_ex=t;
      }
    if(_by>_ey)
      {
	unsigned char t = _by;
	_by=_ey;
	_ey=t;
      };

    std::cout << ">>MUSPOT: "<<_name << "	:["<<
      _bx << "," << _by << "][" << _ex<< "," <<_ey << "] (r: " 
	      << _r << ",c: "<< _c << ") Init 	--Done--\n";
      
  };
  void PrintInfo()
  {
    std::cout << "Spot[" << _name << "] :[" << _bx << "," << _by << "]"
      "[" << _ex << ","<<_ey << "](r: "<<_r << ",C:" << _c<<")\n";
  }
  ~MuSpot(){};

  int getNewX(int range,int x)
  {
    for(;;)
      {
	int tx=x+(rand() % range)-(range/2); // loujemy wsp
	if ((tx >=_bx)||(tx<=_ex))return tx;
      };
  };
  int getNewY(int range,int y)
  {
    for(;;)
      {
	int ty=y+(rand() % range)-(range/2); // loujemy wsp
	if ((ty >=_by)||(ty<=_ey)) return ty;
      };
  };
  int startX(){
    return (rand()%(_bx-_ex)+_bx);
  };
  int startY(){
    return (rand()%(_by-_ey)+_by);
  };
  unsigned char getBX(){return _bx;};
  unsigned char getBY(){return _by;};
  unsigned char getEX(){return _ex;};
  unsigned char getEY(){return _ey;};
  
  unsigned char getR(){return _r;};
  unsigned char getC(){return _c;};
  std::string getName(){return _name;};
};

class MuMap
{
  unsigned char _code; // kod mapy
  std::string   _name; // nazwa mapy
  std::vector<MuObiect*>  _allObiectV;
  std::vector<MuSpot*>	_allSpotV;
 public:
  MuMap(unsigned char code,std::string name,BDBase * BD){
    std::cout << ">MAP: " << name << " init ...\n";
    _code=code;
    _name=name;
    char tmp2[10];
    sprintf(tmp2, "%d", (int)code);	
    string zap="SELECT * FROM `maps_spots` WHERE `spot_map` =";
    zap+=tmp2;
    
    
    if(!BD->isConnected())
      {
	mysql_query(BD->GetDB(), zap.c_str());
	if (mysql_field_count(BD->GetDB())>0)
	  {
	    MYSQL_RES *wynik = mysql_store_result(BD->GetDB());
	    if (wynik!=NULL)
	      {
		if (mysql_num_rows(wynik)>0)
		  {
		    for (int a=0; a<mysql_num_rows(wynik); a++)
		      {
			MYSQL_ROW wiersz = mysql_fetch_row(wynik);
			string name=wiersz[2];
			int bx=atoi(wiersz[3]);
			int by=atoi(wiersz[4]);
			int ex=atoi(wiersz[5]);
			int ey=atoi(wiersz[6]);
			int r=atoi(wiersz[7]);
			int c=atoi(wiersz[8]);
			AddNewSpot(new MuSpot(name,bx,by,ex,ey,r,c));
		      }
		  }
	      };
	    mysql_free_result(wynik);
	  };
      }
    else
      {
	AddNewSpot(new MuSpot("test1 on "+_name,120,120,10,10,10,10));
	AddNewSpot(new MuSpot("test on "+_name,120,120,10,10,10,10));
      };
    std::cout << ">MAP: " << name << " init		 				---DONE---\n";
  };
  void AddNewSpot(MuSpot *s)
    {
      _allSpotV.push_back(s);
      std::cout <<">>MAP: "<< _name << " SPOT #"
		<< _allSpotV.size() << "						--ADD'ED--\n";
    };
  
  void InitMonstersSpot();					//inicjuje spoty potworami
  unsigned char getCode(){return _code;};
  std::string   getName(){return _name;};
  virtual ~MuMap(){};
  
  void addVisibleObject(MuObiect *obiect)
    {
      std::vector<MuObiect*> vList = getVisibleObjects(obiect,20); // szukamy w odleglosci 20
      for(int i=0;i<vList.size();i++)
	{
	  obiect->addKnownObiect(vList[i]);
	  vList[i]->addKnownObiect(obiect);
	}
      
      
    };
  
  void storeNewObiect(MuObiect * o)
    {
      _allObiectV.push_back(o);
      std::cout <<">MAP:"<< _name << " new Obiect id:" << o->getOId() << "	 na [" << (int)o->getX() <<","
		<<(int)o->getY()<<"]	 typ:"<<o->getMType()<<"	--ADD'ED--\n";
    };
  
  std::vector<MuObiect*> getAllObiects(){return _allObiectV;};
  
  //pobieramy obiety w pewnej odlegosci od obiektu o;
  std::vector<MuObiect*> getVisibleObjects(MuObiect *o,int rad)
    {
      std::vector<MuObiect*> nList;
      int sqRadius = rad*rad;
      int x=o->getX();
      int y=o->getY();
      
      for (int i=0;i<_allObiectV.size();i++)
	{
	  if(_allObiectV[i]->getOId()==o->getOId())continue; // jesli znalazlem siebie to nastepny
	  
	  int x1=_allObiectV[i]->getX();
	  int y1=_allObiectV[i]->getY();
	  
	  int dx=x1-x;
	  int dy=y1-y;
	  int sqDist = dx*dx + dy*dy;		
	  if (sqDist < sqRadius)
	    {
	      nList.push_back(_allObiectV[i]);
	    }	
	};
      return nList;	
    };
  void printAllObjects()
    {
      for (int i =0 ; i<_allObiectV.size();i++)
	{
	  _allObiectV[i]->printInfo() ;
	}

    };
  void printAllSpots()
    {
      std::cout << "Spot Id : Spot Data\n";
      for (int i = 0 ; i<_allSpotV.size();i++)
    {
      std::cout << i << " :";
      _allSpotV[i]->PrintInfo();
    }
};
  
  void removeVisibleObject(MuObiect *object)
    {	
      //update known objects
      std::vector<MuObiect*> temp = object->getKnowsObiects();
      for (int i = 0; i < temp.size(); i++)
	{
	  MuObiect *temp1 = temp[i];
	  temp1->removeKnownObiect(object);
	  object->removeKnownObiect(temp1);
	}
    };
  //void SendToAll(SBPacket *p);	
  MuObiect* getId(int id)
    {
      for (int i=0;i<_allObiectV.size();i++)
	if (_allObiectV[i]->getOId()==id)
	  return _allObiectV[i];
      
      return NULL;
    };
  
  MuSpot* getSpot(int nr)
    {
      return _allSpotV[nr];
    };
};

#endif /*MUMAP_H_*/
