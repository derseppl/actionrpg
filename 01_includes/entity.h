#include <string>
#include "gameelement.h"
#include "window.h"
using namespace std ;

#ifndef ENTITY_H
#define ENTITY_H

class Entity : public GameElement {

	private:
		int entityClass ;

	public:
		Entity(int x, int y, string sectorName, int entityClass) ;
		void paint(arpg::Window* win, int abs_x, int abs_y) ;

} ;

#endif
