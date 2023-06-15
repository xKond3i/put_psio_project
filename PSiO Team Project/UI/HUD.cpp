#include "HUD.h"

HUD::HUD(ResourceManager* resources, sf::RenderWindow& window)
{
	text.setFont(*resources->getFont("pixel_font"));
	text.setFillColor(sf::Color(0, 188, 76));
	text.setOrigin(0, text.getLocalBounds().left/2);
	text.setString(std::to_string(money)+"$");
	text.setPosition(window.mapPixelToCoords({100,20}));
	text.setScale(0.4, 0.4);

	//moneysprite
	moneySprite.setTexture(*resources->getTexture("money"));
	moneySprite.setOrigin({ 0,0 });
	moneySprite.setScale(0.25, 0.25);
	moneySprite.setPosition(window.mapPixelToCoords({ 20, 20 }));

}

HUD::~HUD()
{
}

void HUD::draw(sf::RenderTarget& target)
{
	text.setString(std::to_string(money) + "$");

	target.draw(text); 
	target.draw(moneySprite);
}

int HUD::getMoney()
{
	return money;
}

void HUD::modifyMoney(int value)
{
	money += value;
}
