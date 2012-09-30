#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf ;

#ifndef WINDOW_H
#define WINDOW_H

namespace arpg {

	class Window : public RenderWindow {

		private:
			int G_WIDTH ;
			int G_HEIGHT ;
			int G_DEPTH ;

		public:
			Window(int gw, int gh, int gd) ;
			int getWidth() ;
			int getHeight() ;
			void clear() ;
	} ;

}

#endif
