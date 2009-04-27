#include "ACommandT.h"
#include <sstream>
#include "MuObiects/MuMaps.h"
using namespace std;

class AMapsMng : public ACommandT
{
  MuMaps * instance;
  bool t;
public:
  AMapsMng()
  {
    _command="mapsmng";
    _decs="Show information about Maps\n"
      "Usage : mapsmng -l           show list maps\n"
      "Usage : mapsmng -ls <mapid>  show list of all spots setted on specifed map\n"
      "Usage : mapsmng -lo <mapid>  show list of ids on specifed map  \n"
      "Usage : mapsmng -lon <mapid> show list of npc's and monster on \n"
      "                             specifed map\n"
      "Usage : mapsmng -lop <mapid> show list of players on specifed map\n";
    instance=instance->getInstance();
  };
  void listMaps()
  {
    std::cout << "Id     Name\n";
    int maps= instance->getNMap();
    for (int i = 0 ; i<maps;i++)
      {
	MuMap * m=instance->getMap(i);
	std::cout <<(int) m->getCode() << "    " << m->getName()<<"\n";    
      }
  }
  void ShowAllObjects(int mapid)
  {
    MuMap *map=instance->getMap(mapid);
    if (map == NULL)
      std::cout <<"Map with id : " << mapid << "Dosnt exist try mapsmng -l for list of all maps \n";
    else
      map->printAllObjects();
  }

  int getMapId(istringstream & s)
  {
    int mapId=-1;
    if(s.eof())
      {
	std::cout << "Please Enter MapId\n";
	std::cout<< _decs;
      }
    else
      {
	s>>mapId;
      }
    return mapId;
  }
      
  void ParseArgs(std::string arg)
  {
    istringstream st1(arg);
    std::string s;
    st1 >> s;
    int mapId;
    if(s=="-l") 
      {
	listMaps();
      }
    else 
      if(s=="-lo" )
	{
	  mapId=getMapId(st1);
	  if(mapId!= -1)ShowAllObjects(mapId);
	}
      else
	if(s=="-ls")
	  {
	    mapId=getMapId(st1);
	    if(mapId!=-1)  ShowAllSpots(mapId);
	  };
  };
  void ShowAllSpots(int mapid)
  {
      
    MuMap *m = instance->getMap(mapid);
    if ( m == NULL)
      cout << "Map with id " << mapid << " Dosnt exist. Try mapsmng -l for list of all maps\n";
    else
      m->printAllSpots();
  }
  void Run()
  {
  };
};

