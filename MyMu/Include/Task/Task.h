#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <cstdio>
#include <queue>
//usingi :)
//using std::sleep

#include "TimeTick.h"
#include "Job.h"

class TimeJob
{
  TimeTick Ticket;
  Job *J;
 public:
 Job * getJob(){return J;};
  TimeJob(Job* j=NULL,int s=0);
  TimeTick GetTicket()const ;
  friend bool operator<(const TimeJob x,const TimeJob y);
  void Run()const ;
  bool Ticketr(){return Ticket.TickEnd();};
  };


class Task
{
  std::priority_queue<TimeJob > jobs;
  // kolejka projetytowa zadan 
  static Task * _instance;
  Task();
public:
 static Task* Instance()
  {
    if (_instance==NULL)
      {
	std::cout << "SYSTEM:> TASKCORE STARTED ...........\n";
	_instance = new Task();
      }
    return _instance;
  };
  void Run();
  void getTaskList()
  {
    std::cout << "its " << jobs.size() << " jobs in taskMng\n";
  }	
   
  //  void AddJob(Job* j,int t)
  // {
  //std::cout << ">TASKCORE REG: "<< j->getDes()<<"za "<< t << "\n";
  //  jobs.push(new TimeJob(j,t));
  //};
  void AddJobA(Job* j,int t);
  ~Task()
  {
    std::cout << "SYSTEM:> TASKCORE STOPED.... \n";
  };
};



#endif

