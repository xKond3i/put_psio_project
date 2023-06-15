#include "FishingRod.h"


FishingRod::FishingRod(ResourceManager* resources, SoundManager* sm, sf::Vector2f tadziuPos)
{
	bait.setTexture(*resources->getTexture("bait1"));
	bait.setOrigin(bait.getLocalBounds().width / 2, 0);
	tadziuPos.y -= 28;
	bait.setPosition(tadziuPos);
	baitMaxPosUP = tadziuPos.y;

	baitMaxPosDOWN = upgradesLW[currentLineWidth];
	speed = upgradesS[currentSpeed];

	// SM
	SM = sm;
}

FishingRod::~FishingRod()
{
	
}

void FishingRod::fixedUpdate(sf::Time time)
{
	float t = time.asSeconds();
	std::cout << baitGoingUp << std::endl;

	if (verticalDir == 1 && baitInAction && baitMaxPosUP + baitMaxPosDOWN >= bait.getPosition().y) {
		bait.move(0, speed * t);
	}
	
	if ((verticalDir == -1 && baitMaxPosUP < bait.getPosition().y)
		|| (!baitInAction && baitMaxPosUP < bait.getPosition().y && verticalDir != -1)) {		
		baitGoingUp = true;
		bait.move(0, -speed * t);
	}
	if (baitMaxPosUP == bait.getPosition().y) {
		baitInAction = false;
		soundPlayed = false;
		baitGoingUp = false;
	}
	if (bait.getPosition().y > baitMaxPosUP + 16 && !soundPlayed) {
		SM->playSound("splash",1);
		soundPlayed = true;
		baitGoingUp = false;
	}
	if (!baitGoingUp) {
		SM->playSound("reel",2);
	}
	
	
	
}

void FishingRod::setLineOrigin(sf::Vector2f baitOrigin, sf::Vector2f tadziuScale)
{
	if (tadziuScale.x < 0) {
		baitOrigin.x -= 29;
	}
	else{
		baitOrigin.x += 29;
	}
	baitOrigin.y -= 36;
	fishingRodPosition = baitOrigin;

	bait.setPosition(baitOrigin.x, bait.getPosition().y);
}

void FishingRod::handleEvents(sf::Event event)
{

	// KeyPressed
	
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::W:
		case sf::Keyboard::Up:
			verticalDir = -1; // -1 means UP
			break;
		case sf::Keyboard::S:
		case sf::Keyboard::Down:
			if (!baitInAction) verticalDir = 1; // 1 means DOWN
			baitInAction = true;
			break;
		}
	}
	if (event.type == sf::Event::KeyReleased) {
		switch (event.key.code) {
		case sf::Keyboard::W:
		case sf::Keyboard::Up:
			verticalDir = 0;
			break;
		case sf::Keyboard::S:
		case sf::Keyboard::Down:
			verticalDir = 0;
			break;
		}
	}
}

sf::Vector2f FishingRod::getBaitPos()
{
	return bait.getPosition();
}

void FishingRod::draw(sf::RenderTarget& target)
{
	sf::Vertex line[] =	{fishingRodPosition, bait.getPosition()};
	target.draw(line, 2, sf::Lines);
	target.draw(bait);
}



void FishingRod::setInAction(bool baitInAction_)
{
	baitInAction = baitInAction_;
}

bool FishingRod::getInAction()
{
	return baitInAction;
}
