#ifndef TIME_TICK_H
#define TIME_TICK_H

#ifdef TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#else
# include <time.h>
# endif
#endif


class TimeTick
{
  time_t tick;
 public:
  TimeTick(int s);
  bool operator ()();
  bool TickEnd();
  time_t GetTime();
  //  bool friend operator <(const TimeTick &x,const TimeTick &y);
};

#endif 
