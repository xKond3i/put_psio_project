#pragma once

/* ---------- INCLUDES ---------- */
// SFML libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// RESOURCES
#include "ResourceManager.h"
#include "SoundManager.h"

// BASE
#include "AnimatedSprite.h"

// COMPONENTS
#include "Fish.h"

// OTHER
#include <vector>
#include <iostream>

class FishingRod
{

private:
	float gForce = 9.81f;

	sf::Sprite bait;
	sf::Vector2f fishingRodPosition;

	float baitMaxPosUP;
	float baitMaxPosDOWN;

	float waterOffset = 16;

	int verticalDir = 0;

	float speed;
	float fishAttentionRadius;
	float lineLength;

	bool baitInAction = false;
	bool soundPlayed = false;
	bool baitGoingUp = false;

	// CATCHING MECHANICS
	float stress = 0; // 0.f - 1.f
	float fightY = 0;
	float maxFightDistance = 50; // 25
	bool lineBroke = false;
	Fish* caught = nullptr;

	int collectedMoney = 0;

	// UPGARDES
	int currentLineLength = FishingRod::maxUpgrades - 1;
	int currentSpeed = 0;
	int currentFishAttentionRadius = 0;

	// IMPORTANT
	SoundManager *SM;

public:

	FishingRod(ResourceManager*, SoundManager* sm, sf::Vector2f tadziuPos);
	~FishingRod();

	/* ---------- METHODS ---------- */
	void draw(sf::RenderTarget& target);

	void update(sf::Time time);		 // logic EXCEPT physics take place here!
	void fixedUpdate(sf::Time time); // physics take place here.

	void handleEvents(sf::Event event);


	void scanFishes(std::vector<Fish*>& fishes);


	sf::Vector2f getBaitPos();

	void setLineOrigin(sf::Vector2f baitOrigin, sf::Vector2f tadziuScale);

	void setInAction(bool baitInAction_);
	bool getInAction();

	int getCollectedMoney();



	static inline const int maxUpgrades = 3;

	static inline const int upgradesLL[maxUpgrades] = { 200, 450, 768 };
	static inline int upgradesS[maxUpgrades] = { 50, 75, 110 };
	static inline float upgradesFAR[maxUpgrades] = { 10, 25, 50 };

};
