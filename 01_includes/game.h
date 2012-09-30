#include "window.h"
#include "sector.h"
#include "gameelement.h"
#include "entity.h"
#include <string>
#include <SFML/System.hpp>
using namespace std ;

#ifndef GAME_H
#define GAME_H

namespace arpg {

	class Game {

		private:
			Window* win ;
			sf::Mutex GlobalMutex ;
			vector<Sector> sectorLoaded ;
			vector<Sector> sectorToLoad ;
			vector<Entity> elements ;
			string world ;
			int mapX ;
			int mapY ;
			int sectorSize ;
			int wrapperSize ;
			bool mapIsLoadingThread ;
			int loadSector(string sectorName, string world) ;
			int unloadSector(string sectorName) ;
			static void checkSector(void* UserData) ;

		public:
			Game(Window* app) ;
			int start() ;

	} ;

}

#endif
