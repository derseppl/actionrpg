#include <string>
#include "../01_includes/debug.h"
#include "../01_includes/xmlnode.h"
#include "../01_includes/funcs.h"
using namespace arpg ;
using namespace std ;

XMLNode::XMLNode()
{
	// Falls der Konstruktor ohne Werte aufgerufen wird, alle Werte auf leer setzen
	// -> dies ist nur der Fall, wenn es vom Konstruktor von XMLParser aufgerufen wird
	value = " " ;
	tagname = "" ;
	fullnode = "" ;
	attributes = "" ;
}

XMLNode::XMLNode(string nodestr, string tagname) 
{
	value = "" ;
	attributes = "" ;
	this->tagname = tagname ;
	fullnode = trim(nodestr) ;

	// nach den Hauptnodes aufteilen
	splitMainNodes(getValue()) ;
}

string XMLNode::getTagname() {
	return tagname ;
}

vector<XMLNode> XMLNode::getNodes(string title)
{
	// Liefert sämtliche direkten Unternodes dieses Nodes zurück welche den Tagnamen == title haben
	vector<XMLNode> v ;
	
	for (int i = 0; i < nodes.size() ; i++) {
		if(nodes[i].getTagname() == title) {
			v.push_back( nodes[i] ) ;
		}
	}
	
	return v ;
}

// Dies liefert nur den ersten gefundenen Node mit diesem Tagnamen zurück
XMLNode XMLNode::getNode(string title)
{
	for (int i = 0; i < nodes.size() ; i++) {
		if(nodes[i].getTagname() == title) {
			return nodes[i] ;
		}
	}

	return XMLNode() ;	
}

// den Inhalt eines Nodes zurückliefern
// Bsp:		<x>10</x>		-> 10
// Bsp:		<world>
//				<x>10</x>	-> <x>10</x>
//			</world>
// Es werden nur Anfangs- und Endtag weggeparst
string XMLNode::getValue()
{
	string retVal = "" ;
	if(value!="") {
		retVal = value ;	
	} else {
		// Anfangs- und Endtag wegparsen
		int found = fullnode.find(">") ;
		int endfound = fullnode.find("</" + tagname + ">") ;
		endfound = endfound - 2 - tagname.length() ;

		retVal = fullnode.substr( found+1 ) ;
		retVal = retVal.substr( 0, retVal.length() - 3 - tagname.length() ) ;

		value = retVal ;
	}

	return retVal ;
}

// Liefert den Inhalt eines Attributs in diesem Node zurück
// Bsp:		<world id="10"></world>		getAttribute("id")		->	10 als String
string XMLNode::getAttribute(string attr)
{
	string retVal = "" ;

	int found ;

	if (attributes == "" ) {	
		found = fullnode.find(">") ;
		string titleRow = fullnode.substr(0, found) ;
		titleRow = titleRow.substr(2 + tagname.length()) ;
		attributes = titleRow ;
	}
	
	string temp_str = attributes ;
	found = temp_str.find(attr)	;

	if (found != temp_str.npos) {
		temp_str = temp_str.substr(found + attr.length() + 2) ;
		found = temp_str.find("\"") ;
		if (found != temp_str.npos) {
			temp_str = temp_str.substr(0, found) ;
			retVal = temp_str ;
		}
	}

	return retVal ;
}

int XMLNode::splitMainNodes(string content)
{
	int anzNodes = 0 ;
	int found = -1 ;
	int endfound = -1 ;
	string tagname ;
	string nodestr ;

	while(content.find("<") != content.npos) {

		anzNodes++ ;

		// erstes < finden und evt. Kommentare etc. am Anfang wegschneiden
		found = content.find("<") ;
		content = content.substr(found) ;

		// Tagname finden
		found = content.find(">") ;
		tagname = content.substr(1, found-1) ; // liefert den gesamten Tagnamen zurück z.B. 'world class="1"'

		if (tagname.find(" ",1)>1) {
			tagname = tagname.substr(0, tagname.find(" ",1)) ; // world herausfinden
		}

		// Endtag finden
		endfound = content.find("</"+tagname+">") ;
		endfound = endfound + 3 + tagname.length() ;
		
		nodestr = content.substr(0, endfound) ;

		// Der gefundene Node wird erstellt und zu dem Vektor hinzugefügt
		XMLNode* node = new XMLNode(nodestr, tagname) ;
	
		nodes.push_back(*node) ;

		delete node ;

		content = content.substr(endfound) ;
	}

	return anzNodes ;
}
