#ifndef _OBJECTPOOL_
#define _OBJECTPOOL_
#include <iostream>
#include <list>
#include <stack>
#include <utility>
using std::pair;


class MuMap;
class MuObiect;
class MuMonsterInstance;
class MuPcInstance;
class MuItemInstance;
class MuNpcInstance;
class MuViewPort;
class MuNpcTemplate;
class MuAiProcessor;
typedef pair<MuViewPort * , MuViewPort * > MuViewPortPair;


class ObiectPool{

  static ObiectPool * _instance;
  std::stack<int> _freeCels;                   //free cels
  MuObiect*  _pool[0xFFFF];
  MuAiProcessor *_ai[0xff];
  MuAiProcessor *_DefaultAiProc;
  void initPoolData();

  int sizeOfPointer;

  int sizeOfPcInstance;
  int sizeOfMonsterInstance;
  int sizeOfNpcInstance;
  int sizeOfItemInstance;

  int contOfMonsters;
  int contOfPlayers;
  int contOfNpcs;
  int contOfItems;

  ObiectPool();


public:

  static ObiectPool* getInstance();


  ~ObiectPool();


  MuPcInstance* newMuPcInstance(unsigned short id);
  MuItemInstance * newItemInstance();

  MuNpcInstance * newMuNPCInstance(MuNpcTemplate t,unsigned char _x ,unsigned char _y, unsigned char map);
  MuMonsterInstance* newMuMonsterInstance(MuNpcTemplate t, unsigned char _x,unsigned char _y ,unsigned char map );
  MuObiect * getObject(unsigned short id)
  {
	return _pool[id];
  };

  unsigned short reserveId();
  void returnId(unsigned short id);
  void printUsages()
  {
    long sPool=0xffff * 8;
    long sMonsters = contOfMonsters*sizeOfMonsterInstance;
    long sPlayers  = contOfPlayers*sizeOfPcInstance;
    long sItems = contOfItems*sizeOfItemInstance;
    long sNpcs = contOfNpcs*sizeOfNpcInstance;
    long sTotal=sPool+sMonsters+sPlayers+sItems+sNpcs;

    std::cout <<"SYSTEM:>Memory Usage:\n";
    std::cout <<"   Pool    [" << (int)0xffff    << "] Memory [" << (sPool /256)<<"kb]\n";
    std::cout <<"   Monsters[" << contOfMonsters << "] Memory [" << sMonsters/256 << "kb] \n";
    std::cout <<"   Players [" << contOfPlayers  << "] Memory [" << sPlayers/256<<"kb]\n";
    std::cout <<"   Items   [" << contOfItems    << "] Memory [" << sItems/256<<"kb]\n";
    std::cout <<"   NPC     [" << contOfNpcs     << "] Memory [" << sNpcs/256  <<"kb]\n";
    std::cout <<"   TOTOAL  [" << sTotal/256 << "]kb \n\n";
  }

  MuViewPortPair getDistance(unsigned short id1 , unsigned short id2,unsigned char dist);
  std::list<MuObiect*> toObjList();
  std::list<unsigned short> toIdObjList();
  std::list<MuObiect*> toMonList();
  std::list<unsigned short> toIdMobList();
  std::list<MuObiect*> toPlaList();
  std::list<unsigned short> toIdPlaList();

  void ProcessPool();
  MuAiProcessor * getAiProcById(unsigned char id);
  MuAiProcessor * getDefaultAiProc();
  void setAiProcOnId(unsigned char id,MuAiProcessor * proc);
  void setDevaultAiProc(MuAiProcessor * proc);
};



#endif
