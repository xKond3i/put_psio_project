#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "ResourceManager.h"

class Boat
{
private:
	sf::Sprite boat;

public:
	Boat(ResourceManager& resources);
	~Boat();

	void render(sf::RenderTarget& target);

	void move(float x, float y);
	void setPosition(sf::Vector2f pos);
};
