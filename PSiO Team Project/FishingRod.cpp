//#include "FishingRod.h"
//
//
//FishingRod::FishingRod(ResourceManager* resources)
//{
//	bait.setTexture(*resources->getTexture("bait"));
//	bait.setOrigin(bait.getLocalBounds().top / 2, 0);
//}
//
//FishingRod::~FishingRod()
//{
//
//}
//
//void FishingRod::fixedUpdate(sf::Time time){
//	float t = time.asSeconds();
//
//	bait.move(0,gForce);
//	line[0].position = player.getPosition() + sf::Vector2f(rod.getSize().x, rod.getSize().y);
//	line[1].position = bait.getPosition() + sf::Vector2f(bait.getSize().x, rod.getSize().y);
//
//}
//
//void FishingRod::setLineOrigin()
//{
//
//}
