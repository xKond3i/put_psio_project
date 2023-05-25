#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Boat.h"
#include "Rod.h"
#include "ResourceManager.h"

class Character
{
private:
	sf::Sprite character;
	
	Boat* boat;
	Rod* rod;

	sf::IntRect mapBounds;

	bool moving = false;

	float acceleration = 0;
	float speed = 500;

	void move(int dir);
	void mapBoundsCollision();

public:
	Character(ResourceManager& resources, sf::IntRect mapBounds_);
	~Character();

	void render(sf::RenderTarget& target);
	void update(sf::Time time);
	void handleEvents(sf::Event& event);

	sf::Vector2f getPosition();
};
