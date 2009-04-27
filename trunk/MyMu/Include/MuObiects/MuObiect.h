#ifndef MUOBIECT_H_
#define MUOBIECT_H_
#include <vector>
#include <iostream>
#include "Protocol/BaseStruct.h"
class MuMap;
using std::vector;

typedef struct GObjIndex
{
  
  unsigned char m_uIndexHi;
  unsigned char m_uIndexLo;
  GObjIndex(unsigned short id)
  {
    m_uIndexHi=HIBYTE(id);
    m_uIndexLo=LOBYTE(id);
  }
} *PObjIndex;

class MuObiect
{
protected:

  //pollozenie stan
  unsigned char w_x; // wsp x
  unsigned char w_y; // wsp y
  MuMap *w_m; // na mapie
  unsigned char w_f;  // flaga -zawera  stan[np emoty]
  unsigned char w_d;  //  direction - kierunek patrzenia
  std::string GObjName;  //name of obiect ? in pcinstance replace by character name
  int GObjId; // id of obiect for characters -i for npc/monsters spercifed model in game
  //oiect id 
  int o_id;
  unsigned char m_typ; // muj typ : 0 gracz,  1 innapostc 2 npc 3 plapki 4 moby 5 nieznany 
  
protected:
  vector<MuObiect *> knowsObiectList;
  
protected:
  MuObiect(){w_x=142,w_y=136;};
public:
  virtual ~MuObiect(){};
  std::string getObjName(){return GObjName;}
  int getObjId(){return GObjId;}
  void setObjId(int objId){GObjId=objId;}
  void setName(std::string name){GObjName=name;}
  //metody: wsp i mapa
  void setX(unsigned char x){w_x=x;};
  void setY(unsigned char y){w_y=y;};
  void setM(MuMap *m){w_m=m;};
  void setF(unsigned char f){w_f=f;};
  void setD(unsigned char d){w_d=d;};
  
  unsigned char getX(){return w_x;};
  unsigned char getY(){return w_y;};
  MuMap* getM(){return w_m;};
  unsigned char getF(){return w_f;};
  unsigned char getD(){return w_d;};
  virtual void printInfo()
  {
    std::cout << (int)o_id <<"   ["<<(int)w_x<<","<<(int)w_y<<"] \n";  
  }
  //metody obiect id
  void setOId(int id){o_id=id;};
  int getMType(){return m_typ;};
  int getOId(){return o_id;};
  void setMType(int t){m_typ=t;};
  //set/get GObj id
  void setGObjId(short id) { GObjId = id;};
  short getGObjId() { return GObjId;};
  
  
  vector<MuObiect *>::iterator _searchID(int id)
  { 
    vector<MuObiect *>::iterator ite;	
    for (ite=knowsObiectList.begin();ite!=knowsObiectList.end();ite++)
      if((*ite)->getOId()==id) return ite;
  };
  
  bool searchID(int id)
  { 
    vector<MuObiect *>::iterator ite;	
    for (ite=knowsObiectList.begin();ite!=knowsObiectList.end();ite++)
      if((*ite)->getOId()==id) return true;
    return false;
  };
	
	
  vector<MuObiect *> getKnowsObiects(){return knowsObiectList;}
  void addKnownObiect(MuObiect*o)
  {
    knowsObiectList.push_back(o);
    //std::cout << "O:" << getOId() << "new Know " << o->getOId() << 
    //" na ["<< (int)o->getX()<<","<<(int)o->getY()<<"\n";
  };
  void removeKnownObiect(MuObiect*o)
  {
    knowsObiectList.erase(_searchID(o->getOId()));
  };
   void CheckStatus(){};
};

#endif /*MUOBIECT_H_*/
