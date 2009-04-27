#include "ConfFile/ConfFile.h"
#include <sstream>

ConfFile::ConfFile(string file)
{
cFile.open(file.c_str());
error=false;
parse();
}

ConfFile::~ConfFile()
{
cFile.close();
}

// wyciaga informacje z lini textu z pliku
void ConfFile::parse()
{
  string t;
  while(getline(cFile,t))
  {
  if (t.size()==0) continue;
  
 istringstream st1(t);
 char c;
 st1>>c;
 if (c=='#') continue;
 int t1=t.find("=");
 t.replace(t1,1," ");
 istringstream st2(t);
 string v;
 string lab;
 st2 >> lab >> v;
 mLabels[lab]=v;
};
}

// pobiera int wartosc klucza
int ConfFile::getIntValue(string label)
{
int t=mLabels.count(label);
if (t==0) {error=true;return 0;};
map<string,string>::iterator i=mLabels.find(label);
int v;
 istringstream st2((*i).second);
 st2 >>v;
return v;
}

// pobiera bool wartosc klucza
bool ConfFile::getBoolValue(string label)
{
int t=mLabels.count(label);
if (t==0) {error=true;return 0;};
map<string,string>::iterator i=mLabels.find(label);
bool v;
if( ((*i).second=="true")||
    ((*i).second=="0")||
    ((*i).second=="T")||
    ((*i).second=="Yes")||
    ((*i).second=="Y"))
return true;
else return false;
}

// pobiera wartosc string klucza
string ConfFile::getStringValue(string label)
{
int t=mLabels.count(label);
if (t==0) 
{         error=true;
          return "Blad";};
map<string,string>::iterator i=mLabels.find(label);
return (*i).second;
}
bool ConfFile::enyError()
{
   return error;
};
