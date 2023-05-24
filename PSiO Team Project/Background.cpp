#include "Background.h"

Background::Background(ResourceManager& resources)
{
	// layers definition
	sf::Texture* texture;
	sf::Vector2u size;

	// sky
	texture = resources.getTexture("resources/background/sky.png");
	texture->setRepeated(true);
	sky.setTexture(*texture);
	sky.setTextureRect(sf::IntRect(0, 0, 3200, texture->getSize().y));
	sky.setPosition(0, 0);
	
	// clouds
	texture = resources.getTexture("resources/background/clouds.png");
	texture->setRepeated(true);
	size = texture->getSize();
	clouds.setTexture(*texture);
	clouds.setTextureRect(sf::IntRect(-(int)size.x, 0, 3200 + 2 * size.x, size.y));
	clouds.setOrigin(0, texture->getSize().y);
	clouds.setPosition(0, sky.getGlobalBounds().height);

	// city
	texture = resources.getTexture("resources/background/city.png");
	texture->setRepeated(true);
	size = texture->getSize();
	city.setTexture(*texture);
	city.setTextureRect(sf::IntRect(-(int)size.x, 0, 3200 + 2 * size.x, size.y));
	city.setOrigin(0, texture->getSize().y);
	city.setPosition(0, sky.getGlobalBounds().height);

	// moon
	texture = resources.getTexture("resources/background/moon.png");
	water.setTexture(*texture);
	water.setPosition(3200 - texture->getSize().x - 128, 128);

	// water
	texture = resources.getTexture("resources/background/water.png");
	water.setTexture(*texture);
	water.setTextureRect(sf::IntRect(0, 0, 3200, texture->getSize().y));
	water.setPosition(0, sky.getGlobalBounds().height);
}

Background::~Background()
{

}

void Background::render(sf::RenderTarget& target)
{
	target.draw(sky);
	target.draw(clouds);
	target.draw(city);

	target.draw(moon);

	target.draw(water);
}

void Background::update()
{
}

void Background::animate()
{
	clouds.move(animationSpeed * 0.25, 0);
	sf::Vector2f cloudsPos = clouds.getPosition();
	int cloudsWidth = clouds.getTexture()->getSize().x;
	if (cloudsPos.x >= 0) clouds.setPosition(-cloudsWidth, cloudsPos.y);
}
