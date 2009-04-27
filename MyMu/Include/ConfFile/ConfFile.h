#include <string>
#include <fstream>
#include <map>
#include <iostream>

using namespace std;
class ConfFile
{
      protected:        
        //zmiennr
        string fN; // fieleName
        map<string ,string> mLabels;
        ifstream cFile;
        bool error;
		// wyciaga informacje z lini textu z pliku
		void parse();
	public:
        ConfFile(string file);
        virtual ~ConfFile();
		// pobiera wartosc string klucza
		string getStringValue(string labej);
		// pobiera bool wartosc klucza
		bool getBoolValue(string label);
		// pobiera int wartosc klucza
		int getIntValue(string label);  
        bool enyError();     
};
