#include "Rod.h"

Rod::Rod(ResourceManager& resources)
{
	rod.setTexture(*resources.getTexture("resources/fishing_rods/rods/basic.png"));
	bait.setTexture(*resources.getTexture("resources/fishing_rods/baits/basic.png"));

	rod.setOrigin(-rod.getLocalBounds().width / 2, -rod.getLocalBounds().height / 2);

	bait.setOrigin(bait.getLocalBounds().width / 2, 0);
}

Rod::~Rod()
{
}

void Rod::render(sf::RenderTarget& target)
{
	target.draw(rod);
	target.draw(bait);
}

void Rod::update(sf::Time time)
{

}

void Rod::handleEvents(sf::Event& event)
{

}

void Rod::setPosition(sf::Vector2f pos)
{
	rod.setPosition(pos);
	sf::FloatRect rodBounds = rod.getGlobalBounds();
	bait.setPosition(sf::Vector2f(rodBounds.left + (rod.getScale().x > 0 ? rodBounds.width : 0), rodBounds.top + rodBounds.height));
}

void Rod::setScale(float x, float y)
{
	rod.setScale(2 * x, 2 * y);
}
