#include <string>
#include <cstdlib>
#include "../01_includes/window.h"
#include "../01_includes/game.h"
#include "../01_includes/xmlparser.h"
#include "../01_includes/debug.h"
#include "../01_includes/funcs.h"
#include "../01_includes/gameelement.h"
#include "../01_includes/entity.h"
using namespace std ;
using namespace arpg ;

arpg::Game::Game(Window* app)
{
	win = app ;

	// Startposition bei 0 : 0
	mapX = 0 ;
	mapY = 0 ;

	// Sektorgrösse ist standartmässig bei 2000
	sectorSize = 2000 ;
	
	wrapperSize = 100 ;

	mapIsLoadingThread = false ;

	win->EnableKeyRepeat(true) ;

	world = "world_01" ;
}

void arpg::Game::checkSector(void* UserData)
{
	//TODO:	-	Thread schlanker machen
	//			-	diese Methode nicht als Thread benützen, sondern nur
	//				die loadSector und unloadSecotor-Methoden in Threads laufen lassen

	Game* game = static_cast<Game*>(UserData) ;

	// Zu ladende Sektoren löschen
	game->sectorToLoad.clear() ;

	// Sektoren ausfindig machen -> können evt. doppelt eingetragen werden !
	Sector pSector = Sector(game->mapX-game->wrapperSize, game->mapY-game->wrapperSize, game->sectorSize) ;
	game->sectorToLoad.push_back(pSector) ;
	
	Sector sSector1 = Sector(game->mapX+game->win->getWidth()+game->wrapperSize, game->mapY-game->wrapperSize, game->sectorSize) ;
	game->sectorToLoad.push_back(sSector1) ;

	Sector sSector2 = Sector(game->mapX+game->win->getWidth()+game->wrapperSize, game->mapY+game->win->getHeight()+game->wrapperSize, game->sectorSize) ;
	game->sectorToLoad.push_back(sSector2) ;

	Sector sSector3 = Sector(game->mapX-game->wrapperSize, game->mapY+game->win->getHeight()+game->wrapperSize, game->sectorSize) ;
	game->sectorToLoad.push_back(sSector3) ;

	// noch nicht geladenene Sektoren nachladen
	bool found ;
	for(int i = 0; i<game->sectorToLoad.size(); i++) {
		found = false ;
		
		for(int j = 0; j<game->sectorLoaded.size(); j++) {
			if(game->sectorLoaded[j].toString() == game->sectorToLoad[i].toString()) {
				found = true ;
			}
		}

		if (found == false) {
			// WICHTIG: Beim Hinzufügen muss zum Sektor x + 1 gerechnet werden, ansonsten wird der falsche Sektor angenommen
			game->sectorLoaded.push_back(Sector(game->sectorToLoad[i].getX()+1, game->sectorToLoad[i].getY()+1, game->sectorSize)) ;
			game->loadSector(Sector(game->sectorToLoad[i].getX()+1, game->sectorToLoad[i].getY()+1, game->sectorSize), game->world) ;
		}
	}

	// nicht mehr benötigte Sektoren löschen
	for(int i = 0; i < game->sectorLoaded.size(); i++) {
		found = false ;
		for(int j = 0; j < game->sectorToLoad.size(); j++) {
			if(game->sectorLoaded[i].toString() == game->sectorToLoad[j].toString()) {
				found = true ;
			}
		}

		if(found == false) {
			game->unloadSector(game->sectorLoaded[i].toString()) ;
			game->sectorLoaded.erase(game->sectorLoaded.begin() + i) ;
		}
	}

	game->mapIsLoadingThread = false ;
}

int arpg::Game::unloadSector(string sectorName)
{
	Debug dbg ;

	for(int i = 0; i < elements.size(); i++) {
		if(elements[i].getSectorName() == sectorName) {
			elements.erase(elements.begin() + i) ;
			dbg.message("Sektor gelöscht") ;
		}
	}

	return true ;
}

int arpg::Game::loadSector(Sector sector, string world)
{
	string sectorName = sector.toString() ;

	// Die Map-Informationen werden aus einer xml-Datei eingelesen
	string filepath = "./03_maps/" + world + "/" + sectorName + ".xml" ;

	// XML-Datei mit Levelinformationen laden
	XMLParser* xml = new XMLParser(filepath) ;

	vector<XMLNode> entities ;
	entities = xml->getNode("world").getNodes("entity") ; // es wird davon ausgegangen, dass pro Level-File nur ein world-Block existiert !

	// sämtliche Entities des Sektors durchgehen
	for(int i = 0; i < entities.size(); i++) {
		elements.push_back(Entity( strToInt(entities[i].getNode("x").getValue())+sector.getX(), strToInt(entities[i].getNode("y").getValue())+sector.getY(), sectorName, strToInt(entities[i].getAttribute("class")) )) ;
//		Debug().message( entities[i].getNode("x").getValue() ) ;
	}

//	xml->getNode("world").getAttribute("test") ;	

	// TODO: speichern, welcher Sektor bereits geladen wurde

	// XML-Objekt wird nicht mehr benötigt
	delete xml ;

	return true ;
}

int arpg::Game::start()
{
	Debug().message("Endlosschleife gestartet") ;

	sf::Image background ;
	background.LoadFromFile("04_images/gras.png") ;

	sf::Sprite bSprite ;
	bSprite.SetImage(background) ;

	sf::Thread thread(&arpg::Game::checkSector, this) ;

	// TODO: Position von Hintergrund unabängiger machen
	int bX ;
	int bY ;

	// Hauptschleife für das Spiel -> solange das Fenster geöffnet ist !
	while(win->IsOpened()) {

		// Bildschirm leeren
		win->clear() ;

		win->Draw(bSprite) ;

		// prüfen, ob Sektor nachzuladen sind
		// checkSector() ;
		if(mapIsLoadingThread == false) {
			mapIsLoadingThread = true ;
			thread.Launch() ;
		}

		// Elemente zeichnen
		for(int i = 0; i < elements.size(); i++) {
			elements[i].paint(win, mapX, mapY) ;
		}

		sf::Event event ;

		// Schleife mit Events jedes Mal abarbeiten
		while(win->GetEvent(event)) {
			if(event.Type == sf::Event::Closed) {
				win->Close() ;
			}	

			switch(event.Type) {
				case Event::KeyPressed:
					if(event.Key.Code==256) {
						win->Close() ;
					}

					if(event.Key.Code=='d') {
						mapX += 10;
					}

					if(event.Key.Code=='s') {
						mapY += 10 ;
					}

					if(event.Key.Code=='w') {
						mapY -= 10 ;
					}

					if(event.Key.Code=='a') {
						mapX -= 10 ;
					}

					break ;
			}
		}

		// Flip
		win->Display() ;
	}

	Debug().message("Endlosschleife verlassen") ;

	return 0 ;
}
