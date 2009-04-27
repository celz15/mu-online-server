#include "Task/Task.h"
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
using std::cout;
TimeJob::TimeJob(Job*j,int s):Ticket(s)
{
  J=j;
};

TimeTick TimeJob::GetTicket() const
{
  return Ticket;
};

bool operator<(const TimeJob x,const TimeJob y)
{
 return (x.GetTicket().GetTime() > y.GetTicket().GetTime());
};

Task::Task()
{
cout <<"|>SYSTEM Time events init..Done\n";
};
void TimeJob::Run() const
{	
  J->Run();
  std::cout << ">TASKCORE RUN: " << J->getDes() << "\n";
};

void Task::AddJobA(Job* j,int t)
  {
  //std::cout << ">TASKCORE REG: "<< j->getDes()<<"za "<< t << "\n";
  jobs.push(TimeJob(j,t));
};
void Task::Run() 
{
   for (;;)
   
    {
    if(!jobs.empty())
      while ((jobs.top().GetTicket().TickEnd())&&(!jobs.empty()))
	{
		std::cout << "in task " << jobs.size() << " quene\n";
		//std::cout << "in task run\n";
	  jobs.top().Run();
	  
	  jobs.pop();
	};         
	sleep(1);
	 
  };
};

Task * Task::_instance=NULL;


;
