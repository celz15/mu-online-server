#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif
#if defined(HAVE_BOOST_PYTHON)
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>

#include "MuObiects/MuMaps.h"

using namespace boost::python;

int getMapsCount()
{
  return MapsMng->getInstance()->getNMap();
}
class MuMapsPy
{
  MuMaps * maps;
public:
  MuMapsPy(){}
  ~MuMapsPy(){}
};


BOOST_PYTHON_MODULE(MuMaps)
{
  class_<MuMapsPy>("MapsMng");
    


}

#endif
