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
#include <random>
#include <iostream>

class Fish : public AnimatedSprite
{
private:
	int type; // fish type

	sf::Vector2f cycleRangeX; // will be randomized

	// STATS
	float swimmingDepth; // depending on fish type
	float strength;		 // depending on fish type
	float speed;		 // depending of fish type
	float price;		 // depending of fish type

	// MOVING
	int dir = 1;
	bool zigZag = 0;

	bool isCaught;

public:
	Fish(ResourceManager* resources, int type, float startingY, sf::IntRect mapBounds);
	~Fish();

	void draw(sf::RenderTarget& target);
	void update(sf::Time time);		 // logic EXCEPT physics take place here!
	void fixedUpdate(sf::Time time); // physics takes place here!

	// fish type stats
	static const int maxType = 6;
	static inline const sf::Vector2f spawnRangesY[maxType] = { {0, 75}, {25, 90}, {150, 250}, {220, 400}, {600, 700}, {350, 500} };
	static inline float fishSpeeds[maxType] = { 30.f, 80.f, 50.f, 40.f, 10.f, 60.f };
	static inline float fishStrengths[maxType] = { 5.f, 10.f, 30.f, 20.f, 40.f, 50.f };
	static inline float fishPrices[maxType] = { 9.f, 14.f, 21.f, 49.f, 250.f, 200.f };

	void followBait(sf::Time time, sf::Vector2f target);

};
