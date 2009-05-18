#ifndef _BASESTRUCT_H_
#define _BASESTRUCT_H_


/* Get the low byte of a word.                      */
#if !defined(LOBYTE)
#define LOBYTE(w)       ((unsigned char)(w))
     
 /* Get the high byte of a word.                     */
#define HIBYTE(w)       ((unsigned char)((unsigned short)(w) >> 8))

#endif



typedef struct PMSG_HEADA
{
  unsigned char m_uHeader; //c1 ...c4
  unsigned char m_uLen; //lengh of package
  unsigned char m_uProtocolId;
  void set(unsigned char head, unsigned char len , unsigned char id)
  {
    m_uHeader = head;
    m_uLen= len;
    m_uProtocolId= id;
  }

  unsigned short getLen()
  {
    return m_uLen;
  };
  
}*PPMSG_HEADA;

typedef struct PMSG_HEADB{
  unsigned char m_uHeader;
  unsigned char m_uLenHi;
  unsigned char m_uLenLo;
  unsigned char m_uProtocolId;
  void set(unsigned char head, unsigned short len , unsigned char id)
  {
    m_uHeader=head;
    m_uLenHi=HIBYTE(len);
    m_uLenLo=LOBYTE(len);
    m_uProtocolId= id;
  };
  unsigned short getLen()
  {
    unsigned short len = m_uLenLo + (m_uLenHi >>8);
    return len;
  }
}*PPMSG_HEADB;

inline void HeadSetA(PPMSG_HEADA pHead, unsigned char uHeader, unsigned char uLen,unsigned char uProtocolId)
{
  pHead->m_uHeader = uHeader;
  pHead->m_uLen=     uLen;
  pHead->m_uProtocolId=uProtocolId;
};

inline void HeadSetB(PPMSG_HEADB pHead, unsigned char uHeader, unsigned short uLen, unsigned char uProtocolId)
{
  pHead->m_uHeader = uHeader;
  pHead->m_uLenHi= HIBYTE(uLen);
  pHead->m_uLenLo= LOBYTE(uLen);
  pHead->m_uProtocolId= uProtocolId;
};
#endif
