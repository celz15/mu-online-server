#ifndef IDFACTORY_STD
#define IDFACTORY_STD
#include <set>
#include <time.h>
#include <cstdlib>

class UrandGen{
    std::set<int> used;
    int limit;
public:
    UrandGen(int lim=65535):limit(lim){srand(time(0));}
    
    int operator () ()
    {
		while(true)
		{
	   	 int i=int(rand()) % limit;
	   	 if(used.find(i)==used.end())
	   	 {
			used.insert(i);
			return i;
		};
	  };	
	};
	void operator()(int i){
		used.erase(i);    
	};
};


extern UrandGen IdFactory;
#endif
