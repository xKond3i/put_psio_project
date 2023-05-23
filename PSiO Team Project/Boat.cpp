#include "Boat.h"
#include <iostream>

Boat::Boat()
{
	setup();
}

Boat::~Boat()
{
}

void Boat::setup()
{
	if (!boat_texture.loadFromFile("Resources/boat.png")) { std::cout << "Nie znalazalo tekstury :)" << std::endl; return; }
	boat.setTexture(boat_texture);
	boat.setPosition(100, 1000);

}
void Boat::draw(sf::RenderTarget& target)
{
	target.draw(boat);
}
