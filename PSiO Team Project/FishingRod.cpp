#include "FishingRod.h"


FishingRod::FishingRod(ResourceManager* resources, sf::Vector2f tadziuPos)
{
	bait.setTexture(*resources->getTexture("bait1"));
	bait.setOrigin(bait.getLocalBounds().width / 2, 0);
	bait.setPosition(tadziuPos);
}

FishingRod::~FishingRod()
{

}

void FishingRod::fixedUpdate(sf::Time time){
	float t = time.asSeconds();

	bait.move(0,gForce);
}

void FishingRod::setLineOrigin(sf::Vector2f baitOrigin, sf::Vector2f tadziuScale)
{
	if (tadziuScale.x < 0) {
		baitOrigin.x -= 30;
	}
	else{
		baitOrigin.x += 30;
	}
	baitOrigin.y -= 36;
	fishingRodPosition = baitOrigin;

	bait.setPosition(baitOrigin.x, bait.getPosition().y);
}

void FishingRod::draw(sf::RenderTarget& target)
{
	sf::Vertex line[] =	{fishingRodPosition, bait.getPosition()};
	target.draw(line, 2, sf::Lines);
	target.draw(bait);
}
