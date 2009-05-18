#ifndef MUMAP_H_
#define MUMAP_H_
#include <map>
#include <vector>
#include "MuObiects/MuObiect.h"
#include "DB/BDBase.h"
#include <stdlib.h>
#include <string>

class MuViewPortSet;
class MuViewPort;

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
    int dPosOffset = (_ex-_bx) ;
    unsigned char rPosX =_bx;
    if (dPosOffset ==0)
      {
	return rPosX;
      }
    else
      {
	rPosX=(rand()%(dPosOffset/2))+dPosOffset;
      };
    return rPosX;
  };
  int startY(){
    int dPosOffset = (_ey-_by) ;
    unsigned char rPosY =_by;
    if (dPosOffset ==0)
      {
	return rPosY;
      }
    else
      {
	rPosY=(rand()%(dPosOffset/2))+dPosOffset;
      };
    return rPosY;
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
  std::vector<unsigned short>  _allObiectV;
  std::vector<MuSpot*>	_allSpotV;
public:
  MuMap(unsigned char code,std::string name,BDBase * BD){
    printf (">Map: [Name:%s,Indes:%d] init.....\n",name.c_str(),code);   
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
    printf(">MAP: [Name:%s,Index:%d]  init		 		  ---DONE---\n",
	   _name.c_str(),_code);
  };
  void AddNewSpot(MuSpot *s)
  {
    _allSpotV.push_back(s);
    printf(">>MAP: [Name:%s,Index:%d  SPOT[Nb:%d]      					--ADD'ED--\n",
	   _name.c_str(),_code,_allSpotV.size());
  };
  

  void InitMonstersSpot();					//inicjuje spoty potworami
  unsigned char getCode(){return _code;};
  std::string   getName(){return _name;};
  virtual ~MuMap(){};
  
    
  void storeNewObiect(MuObiect * o)
  {
    _allObiectV.push_back(o->getIndex());
    printf("MAP:[%s] Stroe new object[%d] in positon[%d,%d] type[%d]  --ADD'ED--\n",
	   _name.c_str() , o->getIndex(), o->getPosX(),o->getPosY(),o->getType());
  };

  std::vector<unsigned short> getAllObiects()
  {
    return _allObiectV;
  };
  
  
  void updatePortView(MuViewPortSet * view);

  void printAllObjects()
  {
    for (int i =0 ; i<_allObiectV.size();i++)
      {
	MuObiect * o =
	  ObiectPool::getInstance()->getObject(_allObiectV[i]);
	if( o != NULL ) o->PrintMe() ;
      }

  };


  void CheckMapIds()
  {
    for (std::vector<unsigned short>::iterator i = _allObiectV.begin() ; i!= _allObiectV.end();i++)
      {
	if(ObiectPool::getInstance()->getObject((*i))==NULL)
	  {
	    printf ("Found wrong id in map Array [Index:%d] ..... removeIt!!\n",(*i));
	    _allObiectV.erase(i);
	  };
      };
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
   
  };
   
  MuSpot* getSpot(int nr)
  {
    return _allSpotV[nr];
  };
};

#endif /*MUMAP_H_*/
