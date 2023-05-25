#include "Menu.h"



Menu::Menu(ResourceManager& resources, sf::IntRect mapBounds_)
{
	menu.setPosition(0, 0);
}
Menu::~Menu()
{

}

sf::Vector2f Menu::getPosition()
{
	return menu.getPosition();
}