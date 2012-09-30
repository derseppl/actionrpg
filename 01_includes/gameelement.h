#include <string>
#include "window.h"
using namespace std ;

#ifndef GAMEELEMENT_H
#define GAMEELEMENT_H

class GameElement {

	protected:
		int x ;
		int y ;
		string sectorName ;

	public:
		virtual void paint(arpg::Window* win, int, int) = 0 ;
		string getSectorName() ;

} ;

#endif
