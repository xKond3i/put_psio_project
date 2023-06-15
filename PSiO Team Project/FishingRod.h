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

	int verticalDir = 0;
	float speed = 50;

	bool baitInAction = false;
	bool soundPlayed = false;

	SoundManager *SM;

public:

	FishingRod(ResourceManager*, SoundManager* sm, sf::Vector2f tadziuPos);
	~FishingRod();

	/* ---------- METHODS ---------- */
	void draw(sf::RenderTarget& target);

	void update(sf::Time time);		 // logic EXCEPT physics take place here!
	void fixedUpdate(sf::Time time); // physics take place here.

	void handleEvents(sf::Event event);

	sf::Vector2f getBaitPos();

	void setLineOrigin(sf::Vector2f baitOrigin, sf::Vector2f tadziuScale);

	void setInAction(bool baitInAction_);
	bool getInAction();

};
