#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Catchable.h"
#include "ResourceManager.h"
class Fish:public Catchable
{
private:	
	sf::IntRect mapBounds;
	void move(int dir);
	void mapBoundCollision();
public:
	Fish(ResourceManager& resources, sf::IntRect mapBounds_);
	~Fish();

};

