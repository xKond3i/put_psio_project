#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

class Camera
{
private:
	// ...

public:
	sf::View* viewGame;
	sf::View* viewHUD;
	sf::View* viewMenu;
	sf::View* viewPause;

	Camera();
	~Camera();

	void update();
	void move(float x, float y);
};
