#ifndef JOB_H_
#define JOB_H_
#include <string>
class Job
{
	protected:
	std::string opis;		//opis co robi task
 public:
  Job()
  {
  opis="nie ustawiony";
  };
  virtual ~Job(){};
  virtual void Run()=0;
  std::string getDes(){return opis;};
};


#endif
