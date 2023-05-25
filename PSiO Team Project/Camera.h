#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

class Camera
{
private:
	sf::Vector2f pos;
	sf::Vector2f target;
	float speed = 1;
	
	sf::IntRect mapBounds;

public:
	sf::View* viewGame;
	sf::View* viewHUD;
	sf::View* viewMenu;
	sf::View* viewPause;

	Camera(sf::IntRect bounds_);
	~Camera();

	void update(sf::Time time);

	void moveTo(sf::Vector2f target_);
};
