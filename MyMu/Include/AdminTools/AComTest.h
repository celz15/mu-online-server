#ifndef ACOMTEST_H_
#define ACOMTEST_H_
#include "ACommandT.h"
#include <iostream>
class AComTest: public ACommandT
{
	public:
	
	AComTest()
	{
	 
		std::cout << "Twoze kkomende Test" << "\n";
		up=6;
		_command="test";
_decs = "Test command ";	
	};
	
	
	void Run()
	{
		std::cout << "Test Command Run\n";
	}; 
	
	void ParseArgs(std::string arg)
	{
		std::cout << "Test Command Args: [" << arg << "]\n";
	};
};
#endif /*ACOMTEST_H_*/

