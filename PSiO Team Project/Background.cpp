#include "Background.h"

Background::Background()
{
	setupBackground();
}

Background::~Background()
{
}

void Background::setupBackground()
{
	float rectangleSkyHeight = 100;
	//Definiowanie t³a
	rectangleSky.setSize(sf::Vector2f(3200,1000));
	rectangleSky.setPosition(0,0);
	rectangleSky.setFillColor(sf::Color(62, 38, 103, 255));
	rectangleCity.setSize(sf::Vector2f(3200, 600.0));
	rectangleCity.setPosition(0, rectangleSky.getGlobalBounds().height);
	rectangleCity.setFillColor(sf::Color(43, 30, 65, 255));
	rectangleWater.setSize(sf::Vector2f(3200, 3200));
	rectangleWater.setPosition(0, rectangleSky.getGlobalBounds().height+rectangleCity.getGlobalBounds().height);
	rectangleWater.setFillColor(sf::Color(75, 81, 223, 255));
}

void Background::renderBackground(sf::RenderTarget& target)
{
	target.draw(rectangleSky);
	target.draw(rectangleWater);
	target.draw(rectangleCity);
}