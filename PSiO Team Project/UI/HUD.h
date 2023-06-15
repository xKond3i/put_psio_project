#pragma once

/* ---------- INCLUDES ---------- */
// SFML libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../ResourceManager.h"

#include <iostream>

class HUD 
{

private:

	sf::Sprite moneySprite;
	sf::Text text;
	int money = 0; 

public:

	HUD(ResourceManager* resources, sf::RenderWindow& window);
	~HUD();
	void draw(sf::RenderTarget& target);

};
