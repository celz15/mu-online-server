#include <iostream>
#include "CBPacket.h"
class CBUnknown:public CBPacket{
      public:
             CBUnknown(HexBuff *b,MuClientTheard *t):CBPacket(b,t){}
             virtual ~CBUnknown(){}
             void debuild(){
                  std::cout <<"UNKNOWN PACKAGE "<< buff->buff2str() << "\n";
                  };
                  };
                   
