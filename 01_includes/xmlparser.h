#include <fstream>
#include <string>
#include "xmlnode.h"
using namespace std ;

#ifndef XMLPARSER_H
#define XMLPARSER_H

class XMLParser : public XMLNode {

	private:
		string filepath ;
		ifstream file ;


	public:
		XMLParser(string file) ;

} ;

#endif
