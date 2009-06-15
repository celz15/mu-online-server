#include "Task/TimeTick.h"
TimeTick::TimeTick(int s)
{
  tick=time(0)+s;
}

bool TimeTick::operator ()()
{
  return  tick <=time(0);
}

bool TimeTick::TickEnd()
{
  return  tick <time(0);
}

time_t TimeTick::GetTime()
{
  return tick;
}

bool  operator <( TimeTick &x, TimeTick &y)
{
  return x.GetTime() < y.GetTime();
}


