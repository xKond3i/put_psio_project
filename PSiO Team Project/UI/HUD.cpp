#include "HUD.h"

HUD::HUD(ResourceManager* resources, sf::RenderWindow& window)
{

	//text.setFont(*resources->getFont("pixel_font"));
	//text.setPosition(0, 0);
	//auto bounds = text.getLocalBounds();
	//text.setOrigin(bounds.width / 2, bounds.height / 2);
	//text.setString(std::to_string(money));

	//moneysprite
	moneySprite.setTexture(*resources->getTexture("money"));
	moneySprite.setOrigin({ moneySprite.getLocalBounds().width / 2, moneySprite.getLocalBounds().height / 2 });
	moneySprite.setPosition(window.mapPixelToCoords({ 0, 0 }));
}

HUD::~HUD()
{
}

void HUD::draw(sf::RenderTarget& target)
{
	//target.draw(text); 
	//target.draw(shop);
	target.draw(moneySprite);
}
