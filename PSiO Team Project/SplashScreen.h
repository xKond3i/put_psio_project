#pragma once

/* ---------- INCLUDES ---------- */
// SFML libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// RESOURCES
#include "ResourceManager.h"

// SOUNDS
#include "SoundManager.h"

// COMPONENTS
#include "UI/Button.h"

// OTHER
#include <map>

class SplashScreen
{
private:	
	sf::RectangleShape dimm;
	sf::Sprite logo;
	sf::Time splashTime = sf::Time::Zero;
	sf::Time splashTimeEnd = sf::seconds(2);

	bool splashFadingOut = true;
	bool splashFirstTime = true;

	float windowHeight;
	float centerY;
	float spacing = 16;

	std::map<std::string, Button*> buttons;
	float buttonsSpacing = 64;

	// button actions to forward
	bool wantToUnpause = false;
	bool wantToExit = false;

	SoundManager* SM;

public:
	SplashScreen(ResourceManager* resources, SoundManager* sm, sf::RenderWindow& window);
	~SplashScreen();

	void draw(sf::RenderTarget& target);

	void handleEvents(sf::Event event, sf::RenderTarget& window, bool paused);

	void play(sf::Time time);
	void restart();
	void setFading(bool fading);

	void resize(sf::VideoMode windowSize);

	bool entryFinished();

	// button actions to forward
	bool getWantToUnpause();
	bool getWantToExit();

};
