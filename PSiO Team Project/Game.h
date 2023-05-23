#pragma once

// SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// COMPONENTS
#include "Camera.h"

// OTHER
#include <windows.h>

#include <string>

class Game
{
private:
	std::string title = "Tadziu's Fishing Adventure";
	sf::RenderWindow* window;

	sf::Event* event;

	Camera* camera;

	void update();
	void draw();
	void handleEvents();
	
public:
	Game();
	~Game();

	void run();
};
