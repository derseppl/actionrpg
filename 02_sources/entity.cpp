#include <SFML/Graphics.hpp>

#include <string>
#include "../01_includes/gameelement.h"
#include "../01_includes/entity.h"
#include "../01_includes/window.h"
using namespace std ;
using namespace arpg ;

Entity::Entity(int x, int y, string sectorName, int entityClass)
{
	this->x = x ;
	this->y = y ;
	this->sectorName = sectorName ;
	this->entityClass = entityClass ;
}

void Entity::paint(arpg::Window* win, int abs_x, int abs_y)
{
	int drawX = x - abs_x ;
	int drawY = y - abs_y ;

	if(drawX > 0 && drawX < win->getWidth() && drawY > 0 && drawY < win->getHeight()) {
		sf::Shape shape = sf::Shape::Circle(drawX, drawY, 10, sf::Color::Yellow, 10, sf::Color::Blue) ;
		win->Draw(shape) ;
	}
}
