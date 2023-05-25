#include "Background.h"

Background::Background(ResourceManager& resources, sf::IntRect mapBounds_)
{
	mapBounds = mapBounds_;

	// layers definition
	sf::Texture* texture;
	sf::Vector2u size;
	sf::IntRect bounds;

	// sky
	texture = resources.getTexture("resources/background/sky.png");
	texture->setRepeated(true);
	bounds = mapBounds;
	bounds.height = texture->getSize().y;
	sky.setTexture(*texture);
	sky.setTextureRect(bounds);
	sky.setPosition(0, 0);
	
	// clouds
	texture = resources.getTexture("resources/background/clouds.png");
	texture->setRepeated(true);
	size = texture->getSize();
	bounds = mapBounds;
	bounds.left += -(int)size.x;
	bounds.width += 2 * size.x;
	bounds.height = size.y;
	clouds.setTexture(*texture);
	clouds.setTextureRect(bounds);
	clouds.setOrigin(0, texture->getSize().y);
	clouds.setPosition(0, sky.getGlobalBounds().height);

	// city
	texture = resources.getTexture("resources/background/city.png");
	texture->setRepeated(true);
	size = texture->getSize();
	bounds = mapBounds;
	bounds.left += -(int)size.x;
	bounds.width += 2 * size.x;
	bounds.height = size.y;
	city.setTexture(*texture);
	city.setTextureRect(bounds);
	city.setOrigin(0, texture->getSize().y);
	city.setPosition(0, sky.getGlobalBounds().height + 128);

	// moon
	texture = resources.getTexture("resources/background/moon.png");
	moon.setTexture(*texture);
	moon.setPosition(3200 - texture->getSize().x - 128, 128);

	// water
	texture = resources.getTexture("resources/background/water.png");
	texture->setRepeated(true);
	size = texture->getSize();
	bounds = mapBounds;
	bounds.left += -(int)size.x;
	bounds.width += 2 * size.x;
	bounds.height = size.y;
	water.setTexture(*texture);
	water.setTextureRect(bounds);
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

void Background::update(sf::Time time, sf::RenderTarget& target)
{
	float t = time.asMilliseconds() / 1000.0;

	moon.setPosition(target.getView().getCenter().x + target.getView().getSize().x / 2 - 256 - moon.getGlobalBounds().width, 256);
}

void Background::animate(sf::Time time)
{
	float t = time.asMilliseconds() / 1000.0;

	clouds.move(animationSpeed * t * 10, 0);
	sf::Vector2f cloudsPos = clouds.getPosition();
	int cloudsWidth = clouds.getTexture()->getSize().x;
	if (cloudsPos.x >= 0) clouds.setPosition(-cloudsWidth, cloudsPos.y);

	water.move(animationSpeed * t * 25, 0);
	sf::Vector2f waterPos = water.getPosition();
	int waterWidth = water.getTexture()->getSize().x;
	if (waterPos.x >= 0) water.setPosition(-waterWidth, waterPos.y);
}
