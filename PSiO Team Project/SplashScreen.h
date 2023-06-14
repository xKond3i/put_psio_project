#pragma once

/* ---------- INCLUDES ---------- */
// SFML libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// RESOURCES
#include "ResourceManager.h"

class SplashScreen
{
private:	
	sf::RectangleShape dimm;
	sf::Sprite logo;
	sf::Time splashTime = sf::Time::Zero;
	sf::Time splashTimeEnd = sf::seconds(2);

	bool splashFadingOut = true;
	bool splashFirstTime = true;

public:
	SplashScreen(ResourceManager* resources, sf::RenderWindow& window);
	~SplashScreen();

	void draw(sf::RenderTarget& target);

	void play(sf::Time time);
	void restart();
	void setFading(bool fading);

	void resize(sf::VideoMode windowSize);

};

