#pragma once

/* ---------- INCLUDES ---------- */
// SFML libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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

	SplashScreen(sf::RenderWindow);
	~SplashScreen();
	void play(sf::Time time);

};