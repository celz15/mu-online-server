#ifndef BASECONSOLE_H_
#define BASECONSOLE_H_

#include <iostream>
#include <string>

class BaseConsole
{
	protected:

	std::string toSend;		//buffor do wyslania na wyjscie konsoli 
	public:
	BaseConsole(){};
	~BaseConsole(){};

	virtual bool isConnected(){return false;};

	virtual void disconnect(){};

	virtual std::string recvComm()=0;

	virtual void sendRess(std::string)=0;

	virtual void Run()
	{
		while (isConnected())
		{
			
		};
	}
	
	
};

class TestConsole :public BaseConsole
{
	protected:
	public:
	TestConsole(){};
	~TestConsole(){};

	bool isConnected()
	{
		return true;
	};
	
	std::string recvComm()
	{
		return "TestConsole";
	};
	
	void sendRess(std::string s)
	{
		cout << "TestConsole : " << s << "\n";
	};
	
};

class LogOut
{
      vector <LogOut * > VLogOuts;       // wektor wyjsc zarejesttrowanyh 
      
      std::string out ;
      public:
      LogOut(){};
      ~LogOut(){};
      void print(){std::cout << out; out = "":};
      void addToOut(std::strig s){out +=s;};
      void addToOuts(std::string s){
           for (int i= 0; i< VLogOuts.size();i++)
           {
               VlogOuts[i]->addToOut(s);
           };
           }; 
      void clear() {out =" ";};
      void addNewOut(LogOut * l)
      {
           VLogOuts.push_back(l);
      };
      
      std::string getOut(){return out;};
      LogOut& friend operaror << (LogOut &ou,std::string s)
      {
              ou.addToOuts(s); // dodajmey do wszystmich 
              return return a;
      };
      };
      
#endif /*BASECONSOLE_H_*/
