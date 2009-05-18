#ifndef MUOBIECT_H_
#define MUOBIECT_H_
#include <string.h>
#include <vector>
#include <iostream>
#include "Protocol/BaseStruct.h"
#include "MuObiects/MuViewPort.h"
class MuMap;
using std::vector;


enum ObjType
  {
    O_Player=0x00,
    O_NPC=0x01,
    O_Mob=0x02,
    O_Item=0x03,
    O_Unkn=0xFF
  };

class MuObiect
{
protected:
  //object data;
  unsigned short o_Index;        //index in game
  char           o_Name[20];     //name of object
  ObjType        o_Type;         //type of obiect
  //position
  unsigned char  o_PosX;         //x position
  unsigned char  o_PosY;         //y position
  unsigned char  o_PosM;         //on map m position
  unsigned char  o_PosH;         // head look position
  unsigned char  o_PosS;         // status sit etc...
  
  //ViewPort data
  MuViewPortSet  *o_ViewPort;      //viewport data
  
protected:
  MuObiect()
  {
    setPosXY(192,189);
  };
public:


  virtual ~MuObiect(){};

  MuViewPortSet *  getViewPort()
  {
    return o_ViewPort;
  }

  //-------------------------------------------------------------SET/GET-----------------------------------
  std::string getName()
  {
    return std::string(o_Name);
  }

  void setName(char * name)
  {
    strcpy(o_Name,name);
  }
  
  void setIndex(unsigned short id)
  {
    o_Index=id;
  }
  unsigned short getIndex()
  {
    return o_Index;
  }
  void setType(unsigned char t)
  {
    o_Type=(ObjType) t;
  };
  unsigned char getType()
  {
    return o_Type;
  }
  unsigned char getPosHead()
  {
    return o_PosH;
  }

  void setPosX(unsigned char x)
  {
    o_PosX=x;
  }

  void setPosY(unsigned char y)
  {
    o_PosY=y;
  };

  void setPosXY(unsigned char x, unsigned char y)
  {
    o_PosX=x;
    o_PosY=y;
  }
  void setPosition(unsigned char x ,unsigned char y ,unsigned char m ,unsigned char h)
  {
    setPosXY(x,y);
    setPosMapNb(m);
    setPosHead(h);
  }

  void setPositionS(unsigned char x ,unsigned char y , unsigned char m , unsigned char h ,unsigned char s)
  {
    setPosition(x,y,m,h);
    setPosStatus(s);
  };

  void setPosMapNb(unsigned char map)
  {
    o_PosM=map;
  };

  void setPosHead(unsigned char pos)
  {
    o_PosH=pos;
  }
  
  void setPosStatus(unsigned char s)
  {
    o_PosS=s;
  }

  unsigned char getPosX()
  {
    return o_PosX;
  };
  
  unsigned char getPosY()
  {
    return o_PosY;
  };
  
  unsigned char getPosMapNb()
  {
    return o_PosM;
  }

  unsigned char getPosStatus()
  {
    return o_PosS;
  }
  //----------------------------------------------------------------dumping infos ----------------------------------------
  virtual void PrintMe()
  {
    printf("Object[Index:%d,Name:\"%s\",Type:%d] Position[x:%d,y:%d,m:%d,h:%d,s:%d]\n",
	   o_Index,o_Name,o_Type,o_PosX,o_PosY,o_PosM,o_PosH,o_PosS);
  }  

  virtual void PrintViewPort()
  {
    o_ViewPort->printMe();
  };

  void setPortView(MuViewPortSet *s)
  {
    o_ViewPort=s;
  };

  //----------------------------------------------ViewPort staff----------------------------------------  
  
};

#endif /*MUOBIECT_H_*/
