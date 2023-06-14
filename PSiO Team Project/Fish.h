#pragma once

/* ---------- INCLUDES ---------- */
// SFML libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// RESOURCES
#include "ResourceManager.h"

// BASE
#include "AnimatedSprite.h"

// COMPONENTS
#include "FishingRod.h"

class Fish : public AnimatedSprite
{
private:
	sf::Vector2f fishPosition = {0,swimmingDepth};
	float swimmingDepth; // depending on fish type
	float fishSpeed;	 // depending of fish type
	float acceleration;  // depending on fish type

	bool isCaught;

public:
	Fish(ResourceManager* resources);
	~Fish();

	void draw(sf::RenderTarget& target);
	void update(sf::Time time);		 // logic EXCEPT physics take place here!
	void fixedUpdate(sf::Time time); // physics takes place here!
	void boundsCollision();
	void baitCollision();

};
