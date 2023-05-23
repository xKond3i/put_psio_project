#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Boat
{
private:
	sf::Sprite boat;
	sf::Texture boat_texture;

public:
	Boat();
	~Boat();
	void draw(sf::RenderTarget& target);
	void setup();


};

