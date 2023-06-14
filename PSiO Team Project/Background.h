#pragma once

/* ---------- INCLUDES ---------- */
// SFML libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// OTHER libraries
#include <string>
#include <map>
#include <vector>

// RESOURCES
#include "ResourceManager.h"

// COMPONENTS
#include "AnimatedSprite.h"
#include <iostream>

/* ---------- DEPENDENCY CLASS ---------- */
class Layer : public sf::Sprite
{
private:
	int moving;

	bool zigZagDir = false;
	
public:
	Layer(sf::Texture* texture, sf::IntRect size, sf::Vector2f pos, int moving_=Layer::MOVING_NEVER, bool originBottom=true);
	~Layer();

	static int MOVING_ZIGZAG;
	static int MOVING_ALWAYS;
	static int MOVING_NEVER;

	void animate(sf::Time time, float parallaxIndex, float parallaxSpeed, float parallaxModifier);
};



/* ---------- MAIN CLASS ---------- */
class Background
{
private:
	/* ---------- VARIABLES ---------- */
	// LAYERS
	std::map<std::string, Layer*> layers;
	std::vector<std::string> drawingOrder;

	sf::Sprite moon;

	sf::IntRect mapBounds;

	// PARALLAX
	float parallaxSpeed = 5.f;
	float parallaxModifier = 1.5f;

	// MAP BORDERS
	float offset = 32.f;
	bool borderSymbolAnimDir = false;
	AnimatedSprite* borderSymbolLeft;
	AnimatedSprite* borderSymbolRight;

public:
	Background(ResourceManager* resources, sf::IntRect mapBounds_);
	~Background();

	/* ---------- METHODS ---------- */
	void moveMoon(sf::View* view);

	float getOffset();



	void update(sf::Time time);		 // logic EXCEPT physics take place here!
	void fixedUpdate(sf::Time time); // physics take place here.

	void draw(sf::RenderWindow& target);
};
