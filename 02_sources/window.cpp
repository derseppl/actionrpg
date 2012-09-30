#include <iostream>
#include <string>
#include "../01_includes/window.h"
#include "../01_includes/debug.h"
using namespace std ;

arpg::Window::Window(int gw, int gh, int gd) : sf::RenderWindow(sf::VideoMode(gw,gh,gd), "ActionRPG", Style::Close)
{
	Debug().message("Fenster erstellt!") ;

	// übergebene Werte übernehmen
	G_WIDTH = gw ;
	G_HEIGHT = gh ;
	G_DEPTH = gd ;
}

void arpg::Window::clear()
{
	// mit OpenGL das Anzeigefenster Cls machen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
}

int arpg::Window::getWidth()
{
	return G_WIDTH ;
}

int arpg::Window::getHeight()
{
	return G_HEIGHT ;
}
