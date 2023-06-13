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

class Player : public AnimatedSprite
{
private:
	sf::Vector2i frameSize = {64, 64};
	unsigned int frameCount = 4;

public:
	Player(ResourceManager* resources);
	~Player();

};
