#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Background
{
private:
	sf::RectangleShape rectangleCity;
	sf::RectangleShape rectangleWater;
	sf::RectangleShape rectangleSky;
	void setup();
public:

	Background();
	~Background();
	void animate();
	void render(sf::RenderTarget& target);
	void update();


};

