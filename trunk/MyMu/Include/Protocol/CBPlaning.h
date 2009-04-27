#include <iostream>
#include "CBPacket.h"
class CBPlaning:public CBPacket{
std::string _opis;
      public:
             CBPlaning(HexBuff *b,MuClientTheard *t,std::string opis):CBPacket(b,t){_opis=opis;}
             virtual ~CBPlaning(){}
             void debuild(){
				  std::cout << "-= " << _opis <<" =-\n";
                  std::cout <<"UNKNOWN PACKAGE "<< buff->buff2str() << "\n";
                  };
                  };
                   
