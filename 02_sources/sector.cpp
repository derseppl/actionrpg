#include <string>
#include "../01_includes/sector.h"
#include "../01_includes/funcs.h"
using namespace std ;

Sector::Sector(int xp, int yp, int sectorSize)
{	
	// x und y sind noch keine Sektorangaben, sondern absolut !
	x = xp ;
	y = yp ;

	// Sektor ausfindig machen
	if (x < 0) {
		x -= (sectorSize + (x % sectorSize)) ;
	} else {
		x -= (x % sectorSize) ;
	}
	
	if (y < 0) {
		y -= (sectorSize + (y % sectorSize)) ;
	} else {
		y -= (y % sectorSize) ;
	}
}

string Sector::toString()
{
	string retVal = "" ;

	retVal = intToStr(x) + "_" + intToStr(y) ;

	return retVal ;
}

int Sector::getX()
{
	return x ;
}

int Sector::getY()
{
	return y ;
}
