#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "ResourceManager.h"

#include "Catchable.h"

class Rod
{
private:
	sf::Sprite bait;
	sf::Sprite rod;
	Catchable* catchable = nullptr;

public:
	Rod(ResourceManager& resources);
	~Rod();

	void render(sf::RenderTarget& target);
	void update(sf::Time time);
	void handleEvents(sf::Event& event);

	void setPosition(sf::Vector2f pos);
	void setScale(float x, float y);

};
