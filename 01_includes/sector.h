#include <string>
using namespace std ;

#ifndef SEKTOR_H
#define SEKTOR_H

class Sector {

	private:
		int x ;
		int y ;

	public:
		Sector(int xp, int yp, int sectorSize) ;
		string toString() ;
		int getX() ;
		int getY() ;

} ;

#endif
