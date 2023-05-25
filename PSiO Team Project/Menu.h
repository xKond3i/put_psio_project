#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
class Menu
{
private:
	sf::Sprite menu;
public:
	
	Menu(ResourceManager& resources, sf::IntRect mapBounds_);
	~Menu();
	sf::Vector2f getPosition();

};

