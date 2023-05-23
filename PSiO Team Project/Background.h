#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Background
{
private:
	sf::RectangleShape rectangleCity;
	sf::RectangleShape rectangleWater;
	sf::RectangleShape rectangleSky;
	void setupBackground();
public:

	Background();
	~Background();
	void animateBackground();
	void renderBackground(sf::RenderTarget& target);
	void updateView();


};

