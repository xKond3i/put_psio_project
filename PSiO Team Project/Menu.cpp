#include "Menu.h"



Menu::Menu(ResourceManager& resources, sf::IntRect mapBounds_)
{
	menu.setPosition(0, 0);
}
Menu::~Menu()
{

}

void Menu::update(sf::Time time, sf::RenderTarget& target)
{
	float t = time.asMilliseconds() / 1000.0;

	menu.setPosition(target.getView().getCenter().x, 0);
}

sf::Vector2f Menu::getPosition()
{
	return menu.getPosition();
}
