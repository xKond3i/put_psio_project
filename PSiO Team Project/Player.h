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

class Player : public AnimatedSprite
{
private:
	sf::Vector2i frameSize = {64, 64};
	unsigned int frameCount = 4;

	// moving
	int dir = 0;
	int slideDir = 0;
	float speed = 0;
	float maxSpeed = .25f;
	float acceleration = .1f;

	bool holdingLeft = false;
	bool holdingRight = false;

public:
	Player(ResourceManager* resources);
	~Player();

	/* ---------- METHODS ---------- */
	void checkFrameCollision(sf::IntRect frame);

	void handleEvents(sf::Event event);

	void update(sf::Time time);		 // logic EXCEPT physics take place here!
	void fixedUpdate(sf::Time time); // physics take place here.

	void draw(sf::RenderTarget& target);
};
