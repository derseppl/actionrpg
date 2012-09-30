#include <iostream>
#include "01_includes/window.h"
#include "01_includes/game.h"
#include "01_includes/debug.h"
using namespace arpg ;

int main()
{
	// Fenster zur Spieldarstellung erstellen
	arpg::Window* win = new arpg::Window(1600,900,32) ;

	// neues Spiel erstellen
	Game* game = new Game(win) ;

	// Endlosschleife von Spiel starten
	int status = game->start() ;

	// Speicher von game wieder freigeben
	delete game ;
	
	Debug().message("Programmende") ;

	return 0 ;
}
