#include <string>
#include <vector>
using namespace std ;

#ifndef XMLNODE_H
#define XMLNODE_H

class XMLNode {
	
	private:
		string value ;
		string fullnode ;
		string tagname ;
		string attributes ;
		vector<XMLNode> nodes ;

	protected:
		int splitMainNodes(string content) ;

	public:
		XMLNode(string nodestr, string tagname) ;
		XMLNode() ;
		string getValue() ;
		string getAttribute(string attr) ;
		XMLNode getNode(string title) ;
		vector<XMLNode> getNodes(string title) ;

		string getTagname() ;
} ;

#endif
