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

#include <random>

class Fish : public AnimatedSprite
{
private:
	int type; // fish type

	// fish type stats
	static const int maxType = 6;
	sf::Vector2f spawnRangesY[maxType] = { {0, 75}, {25, 90}, {150, 250}, {220, 400}, {600, 700}, {350, 500} };
	float fishSpeeds[maxType] = { 30.f, 80.f, 50.f, 40.f, 10.f, 60.f };
	float fishStrengths[maxType] = { 5.f, 10.f, 30.f, 20.f, 40.f, 50.f };

	sf::Vector2f cycleRangeX; // will be randomized

	// STATS
	float swimmingDepth; // depending on fish type
	float strength;		 // depending on fish type
	float speed;		 // depending of fish type

	float acceleration;  // depending on fish type

	bool isCaught;

public:
	Fish(ResourceManager* resources, int type, float startingY);
	~Fish();

	void draw(sf::RenderTarget& target);
	void update(sf::Time time);		 // logic EXCEPT physics take place here!
	void fixedUpdate(sf::Time time); // physics takes place here!
	void boundsCollision();
	void baitCollision();

};
