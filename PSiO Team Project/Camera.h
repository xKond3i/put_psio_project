#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

class Camera
{
private:
	sf::IntRect bounds; // [left, top, right, bottom]

public:
	sf::View* viewGame;
	sf::View* viewHUD;
	sf::View* viewMenu;
	sf::View* viewPause;

	Camera(sf::IntRect bounds_);
	~Camera();

	void update();
	void move(float x, float y);
};
