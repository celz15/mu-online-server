#include "ACommandT.h"
#include <sstream>
using namespace std;

class AInfo : public ACommandT
{
bool t;
 public:
  AInfo()
    {
      _command="info";
      _decs="Show information about server\n"
	"Usage : info -d           show list of developers\n"
	"Usage : help              show information about server\n";
    };
  
  void ParseArgs(std::string arg)
    {
      istringstream st1(arg);
      std::string s;
      st1 >> s;
      if(s=="-d") t = true;
      else
	{
	t = false;
	}
    };
  void Run()
    {
      if (t) 
      {
      std::cout << "MiKiOnE    mikiones@gmail.com    Michal Kinasiewicz\n"
      "Lardux	lardux@gmail.com   \n";
      }
      else
      std::cout << "Not jet... :( \n";
    };
};
  
