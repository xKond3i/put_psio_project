#pragma once

// SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// COMPONENTS
#include "ResourceManager.h"

#include "Camera.h"

#include "Background.h"
#include "Character.h"

// OTHER
#include <windows.h> // for maximizing window

#include <string>

// --- DEBUG
#include <iostream>

class Game
{
private:
	std::string title = "Tadziu's Fishing Adventure";
	sf::RenderWindow* window;

	sf::Event* event;

	ResourceManager* resources;

	Camera* camera;

	Background* background;
	//Character* character;

	void update();
	void draw();
	void handleEvents();

	void load();
	
public:
	Game();
	~Game();

	void run();
};
