#include <fstream>
#include <string>
#include <vector>

#include <iostream>

#include "../01_includes/xmlparser.h"
#include "../01_includes/debug.h"
#include "../01_includes/xmlnode.h"
using namespace std ;
using namespace arpg ;

// -> XMLParser erbt von XMLNode

XMLParser::XMLParser(string path) 
{
	// Debug-Objekt erstellen, so dass Dateiname und eventuelle Fehlermeldung gleiche Nummer haben
	Debug dbg = Debug() ;
	dbg.message("Parse XML-File: " + path) ;

	filepath = path ;

	file.open(filepath.c_str(), ios_base::in) ;

	// überprüfen, ob die Datei existiert
	if (!file) {
		dbg.message("Datei '" + path + "' nicht gefunden") ;
	} else {
		string filecontent ;
		char character ;
		while(!file.eof()) {
			file.get(character) ;
			filecontent += character ;
		}

		// Mainnodes herausfinden und gesamte Datei in Nodes aufsplitten
		splitMainNodes(filecontent) ;
	}

	file.close() ;
}
