#ifndef MYPYSCRIPT_H_
#define MYPYSCRIPT_H_
#include <fstream>

class MuPyScrypt
{
	protected:
	std::string _file;		//nazwa scryptu
	std::string _script;     //tresc scryptu
	public:
	MuPyScrypt(std::string folename){name_=name;};
	~MuPyScript(){};
	void Load()
	
	{
	ifstream f(_file.c_str()+".py");
	
	};
	void Run(){PyRun_SimpleString(_script.c_str());};
	
	
#endif /*MYPYSCRIPT_H_*/