#pragma once

/* ---------- INCLUDES ---------- */
// SFML libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// OTHER libraries
#include <windows.h> // for maximizing window

#include <string>

// RESOURCES
#include "ResourceManager.h"
#include "SoundManager.h"
#include "SplashScreen.h"

// GAME contructs
#include "Camera.h"

// COMPONENTS
#include "Background.h"
#include "Player.h"



// --- DEBUG libraries
#include <iostream>

class Game
{
private:
	/* ---------- VARIABLES ---------- */
	// --- GLOBAL settings
	const std::string  title = "Tadziu's Fishing Adventure";
	const unsigned int fps = 90;

	float timeScale = 1.f;
	bool  paused = false;

	bool cooldownFlag = false;
	sf::Time cooldown = sf::Time::Zero;
	sf::Time cooldownDuration = sf::seconds(2);

	//sf::VideoMode windowSize = { 1920, 1080 };
	sf::VideoMode windowSize = { 1280, 720 };

	sf::Image icon;



	// --- GAME settings
	sf::IntRect mapBounds = sf::IntRect(0, 0, 1024, 4096);
	sf::Color fillColor = sf::Color(19, 31, 65);


	// --- GAME constructs
	sf::RenderWindow* window;
	sf::Event event;

	ResourceManager* resources;
	SoundManager* soundManager;

	Camera* camera;

	// --- COMPONENTS
	Background* background;
	Player* player;

	/* ---------- METHODS ---------- */
	void load();
	void pause();
	void unpause();

public:
	Game();
	~Game();

	/* ---------- METHODS ---------- */
	void run();

	

	void handleEvents();

	void update(sf::Time time);		 // logic EXCEPT physics take place here!
	void fixedUpdate(sf::Time time); // physics take place here.

	void draw();
};
