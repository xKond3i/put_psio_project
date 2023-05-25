#pragma once

// SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// COMPONENTS
#include "ResourceManager.h"

#include "Camera.h"
#include "Menu.h"

#include "Background.h"
#include "Character.h"
#include "Fish.h"

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
	sf::Clock clock;

	ResourceManager* resources;

	Camera* camera;

	Background* background;
	Character* character;

	Menu* menu;

	sf::IntRect mapBounds;

	bool isPaused = false;

	void update(sf::Time time);
	void draw();
	void handleEvents();

	void load();
	
public:
	Game();
	~Game();

	void run();
};
