#pragma once

/* ---------- INCLUDES ---------- */
// SFML libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// RESOURCES
#include "ResourceManager.h"

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
public:

	FishingRod(ResourceManager*, sf::Vector2f tadziuPos);
	~FishingRod();

	/* ---------- METHODS ---------- */
	void checkFrameCollision(sf::IntRect frame);

	void handleEvents(sf::Event event);

	void update(sf::Time time);		 // logic EXCEPT physics take place here!
	void fixedUpdate(sf::Time time); // physics take place here.
	void setLineOrigin(sf::Vector2f baitOrigin, sf::Vector2f tadziuScale);

	void draw(sf::RenderTarget& target);

};

