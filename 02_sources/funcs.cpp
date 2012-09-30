#include <string>
#include <sstream>
#include "../01_includes/funcs.h"
using namespace std ;

// Diese Funktion entfernt die Leerzeichen eines String am Ende und am Schluss
string trim(string str)
{
	str = str.erase(0,str.find_first_not_of(" ")); 
	str = str.erase(str.find_last_not_of(" ")+1);

	return str ;
}

string intToStr(int number) 
{
	stringstream ss ;
	ss << number ;
	return ss.str() ;
}

int strToInt(string str)
{
	stringstream ss(str) ;

	int retVal = 0 ;
	ss >> retVal ;

	return retVal ;
}
