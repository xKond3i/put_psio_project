#pragma once

/* ---------- INCLUDES ---------- */
// SFML libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// RESOURCES
#include "ResourceManager.h"

// COMPONENTS
#include "UI/Button.h"

// OTHER
#include <vector>

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

	std::vector<Button*> buttons;
	float buttonsSpacing = 64;

public:
	SplashScreen(ResourceManager* resources, sf::RenderWindow& window);
	~SplashScreen();

	void draw(sf::RenderTarget& target);

	void handleEvents(sf::Event event, sf::RenderTarget& window, bool paused);

	void play(sf::Time time);
	void restart();
	void setFading(bool fading);

	void resize(sf::VideoMode windowSize);

	bool entryFinished();

};
