#include "ACommandT.h"
#if defined (HAVE_CONFIG_H)
#include "config.h"
#endif
#include <sstream>
#if defined(HAVE_BOOST_PYTHON)

//boost python 
#include <boost/python.hpp>
using namespace boost::python;
#endif
class ARunPy:public ACommandT
{
  std::string file;
public:
  ARunPy()
  {
    _command="runPy";
    _decs="Run python scrypt from location\n";
  };
  void ParseArgs(std::string arg)
  {
    istringstream str1(arg);
    str1>>file;
  }

  void Run()
  {
#if defined (HAVE_BOOST_PYTHON)
    try{

      object main= import("__main__");
      object global=main.attr("__dict__");
      exec_file(file.c_str(),global,global);

      std::cout << "PYTHON MODULE IS TURNED OFF \n";

      
    }
    catch(error_already_set const &)
      {

	PyErr_Print();

      }
    catch (...)
      {
	
    
      }
#else
    std::cout << "PUTHON IS NOT AVALIBLE (INSTALL PTHON2.5 and Boost_python library and recompile !! \n";
#endif
  }
};
