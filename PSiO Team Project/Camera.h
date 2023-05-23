#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Camera
{
public:
	sf::View* viewGame;
	sf::View* viewHUD;
	sf::View* viewMenu;
	sf::View* viewPause;

	Camera();
	~Camera();

	void update();
};
