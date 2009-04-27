#ifndef _PROTOCOL_CORE_H
#define _PROTOCOL_CORE_H_
#include "Protocol/BaseStruct.h"

class ProtocolCore
{
 private:
  unsigned char * _dataPtr;
  PMSG_HEADA *_headAPtr;
  PMSG_HEADB *_headBPtr;
  void (*func[0xff])(unsigned char * buff);
 public:
  ProtocolCore(unsigned char * buff)
    {
      _dataPtr= buff;
      _headAPtr = (PMSG_HEADA *)_dataPtr;
      _headBPtr = (PMSG_HEADB *)_dataPtr;
    };
  
};
#endif
