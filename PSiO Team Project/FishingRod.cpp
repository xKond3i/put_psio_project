#include "FishingRod.h"


FishingRod::FishingRod(ResourceManager* resources, SoundManager* sm, sf::Vector2f tadziuPos)
{
	bait.setTexture(*resources->getTexture("bait" + std::to_string(currentFishAttentionRadius + 1)));
	bait.setOrigin(bait.getLocalBounds().width / 2, 0);
	tadziuPos.y -= 28;
	bait.setPosition(tadziuPos);
	baitMaxPosUP = tadziuPos.y;

	baitMaxPosDOWN = upgradesLL[currentLineLength];
	speed = upgradesS[currentSpeed];
	lineLength = upgradesS[currentLineLength];
	fishAttentionRadius = upgradesFAR[currentFishAttentionRadius];

	// SM
	SM = sm;

}

FishingRod::~FishingRod()
{
	
}

void FishingRod::fixedUpdate(sf::Time time)
{
	float t = time.asSeconds();

	if (caught != nullptr) caught->followBait(time, bait.getPosition());

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

	if (bait.getPosition().y > baitMaxPosUP + waterOffset && !soundPlayed) {
		SM->playSound("splash", 1);
		soundPlayed = true;
		baitGoingUp = false;
	}

	if (baitGoingUp) {
		SM->setSound("reel", 2);
		SM->unpauseSound(2);
	}
	else {
		SM->pauseSound(2);
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
			if (baitMaxPosUP + waterOffset >= bait.getPosition().y) verticalDir = -1;
			baitGoingUp = false;
			break;
		case sf::Keyboard::S:
		case sf::Keyboard::Down:
			verticalDir = 0;
			if (baitMaxPosUP + waterOffset >= bait.getPosition().y) verticalDir = -1;
			break;
		}
	}
}

void FishingRod::scanFishes(std::vector<Fish*>& fishes)
{
	if (caught != nullptr) return;

	for (const auto f : fishes) {
		sf::Vector2f fPos = f->getPosition();
		sf::Vector2f baitPos = bait.getPosition();

		float d = hypot(baitPos.x - fPos.x, baitPos.y - fPos.y);

		if (d > fishAttentionRadius) continue;

		caught = f;
	}
}

sf::Vector2f FishingRod::getBaitPos()
{
	return bait.getPosition();
}

void FishingRod::draw(sf::RenderTarget& target)
{
	sf::Vertex line[] =	{fishingRodPosition, bait.getPosition()};

	sf::Color stressColor = sf::Color(220, 20, 60);
	sf::Color defaultColor = sf::Color::White;
	sf::Color stateColor;
	// color interpolation = (color2 - color1) * fraction + color1
	stateColor.r = (stressColor.r - defaultColor.r) * stress + defaultColor.r;
	stateColor.g = (stressColor.g - defaultColor.g) * stress + defaultColor.g;
	stateColor.b = (stressColor.b - defaultColor.b) * stress + defaultColor.b;

	line[1].color = stateColor;

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
