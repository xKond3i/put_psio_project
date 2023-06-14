#pragma once

/* ---------- INCLUDES ---------- */
// SFML libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// RESOURCES
#include "..\ResourceManager.h"

#include <iostream>

class Button : public sf::Sprite
{
private:
	bool disabled = false;
	bool toggleable = false;

	bool hovered = false;

	int state = 0;
	sf::Texture* states[2];

	float initialScale = .5f;

	// animation
	sf::Time animTime = sf::Time::Zero;
	sf::Time animTimeEnd = sf::seconds(.25);

public:
	Button(ResourceManager* resources, std::string texName,     sf::Vector2f pos, bool originCenter = true, bool disabled_ = false);
	Button(ResourceManager* resources, std::string texNames[2], sf::Vector2f pos, bool originCenter = true, bool disabled_ = false);
	~Button();

	void handleEvents(sf::Event event);

	void draw(sf::RenderTarget& target);

	void animate(sf::Time time);

	void setHovered(bool hovered_);

	void setScale(float factor);

};
