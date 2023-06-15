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

	sf::Sprite moneySprite, speedUpgrade, baitUpgrade, lengthUpgrade;
	sf::Text text;

	int money = 0; 

public:

	HUD(ResourceManager* resources, sf::RenderWindow& window);
	~HUD();

	void draw(sf::RenderTarget& target);
	void handleEvents(sf::Event event, sf::RenderTarget& window);

	int getMoney();
	void modifyMoney(int value);

};
