#include "ACommandT.h"
#include <sstream>
using namespace std;

class AComandHelp : public ACommandT
{
  std::string helpOut;
 public:
  AComandHelp()
    {
      _command="help";
      _decs="Show help to specifed command\n"
	"Usage : help <command>    show help about specifed command\n"
	"Usage : help -l           show list of avalibles commans\n";
    };
  
  void ParseArgs(std::string arg)
    {
      istringstream st1(arg);
      std::string s;
      st1 >> s;
      if(s=="-l") helpOut = Mng->getListOfCommands();
      else
	{
	  helpOut= Mng->getHelpFor(s);
	}
    };
  void Run()
    {
      std::cout << helpOut<<"\n";
    };
};
  
