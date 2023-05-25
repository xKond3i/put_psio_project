#include "Boat.h"

Boat::Boat(ResourceManager& resources)
{
	sf::Texture* texture = resources.getTexture("resources/boats/raft.png");
	boat.setTexture(*texture);
	boat.setOrigin(boat.getLocalBounds().width / 2, -boat.getLocalBounds().height);

	boat.setScale(0.5, 0.5);
	boat.setPosition(256, 1472);
}

Boat::~Boat()
{

}

void Boat::render(sf::RenderTarget& target)
{
	target.draw(boat);
}

void Boat::move(float x, float y)
{
	boat.move(x, y);
}

void Boat::setPosition(sf::Vector2f pos)
{
	boat.setPosition(pos);
}
