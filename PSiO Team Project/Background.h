#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "ResourceManager.h"

class Background
{
private:
	// layers - as we won't use them anywhere else we don't need pointers
	sf::Sprite sky;
	sf::Sprite clouds;
	sf::Sprite city;

	sf::Sprite moon;

	sf::Sprite water;

	float animationSpeed = 1.0;

public:
	Background(ResourceManager& resources);
	~Background();

	void render(sf::RenderTarget& target);
	void update();  // parallax
	void animate(); // sf::Time will be used here
};
