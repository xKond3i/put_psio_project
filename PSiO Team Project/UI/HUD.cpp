#include "HUD.h"

HUD::HUD(ResourceManager* resources, sf::RenderWindow& window)
{
	text.setFont(*resources->getFont("pixel_font"));
	//text.setOrigin(0, -text.getLocalBounds().height/2);
	text.setString("$ " + std::to_string(money));
	text.setFillColor(sf::Color(0, 188, 76));
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(2);
	//text.setCharacterSize(32);
	//text.setScale(scale * 2, scale * 2);
	text.setCharacterSize(64);
	text.setScale(scale / 2, scale / 2);

	//text.setPosition(window.mapPixelToCoords({100, 20}));
	//text.setScale(0.5, 0.5);

	//moneysprite
	moneySprite.setTexture(*resources->getTexture("money"));
	moneySprite.setOrigin({ 0,0 });
	moneySprite.setScale(scale, scale);

	//moneySprite.setPosition(window.mapPixelToCoords({ 20, 20 }));


	
	baitUpgrade.setTexture(*resources->getTexture("bait_upgrade"));
	baitUpgrade.setOrigin({ baitUpgrade.getLocalBounds().width, baitUpgrade.getLocalBounds().height });
	baitUpgrade.setScale(scale, scale);
	//baitUpgrade.setPosition(window.mapPixelToCoords({ 1180,680 }));

	lengthUpgrade.setTexture(*resources->getTexture("length_upgrade"));
	lengthUpgrade.setOrigin({ lengthUpgrade.getLocalBounds().width, lengthUpgrade.getLocalBounds().width });
	lengthUpgrade.setScale(scale, scale);
	//lengthUpgrade.setPosition(window.mapPixelToCoords({ 1245, 680 }));

	resize(window, { window.getSize().x, window.getSize().y });

}

HUD::~HUD()
{
}

void HUD::draw(sf::RenderTarget& target)
{
	text.setString("$ " + std::to_string(money));
	target.draw(text); 
	//target.draw(moneySprite);

	//target.draw(lengthUpgrade);
	//target.draw(baitUpgrade);
}

void HUD::handleEvents(sf::Event event, sf::RenderTarget& window)
{
	if (event.type == sf::Event::Resized)
	{
		sf::VideoMode windowSize = { event.size.width, event.size.height };
		resize(window, windowSize);
	}

	// TBC - NOT FINISHED!
	// TBC - NOT FINISHED!
	// TBC - NOT FINISHED!

	//sf::Vector2f lengthUpgradeCoords = { lengthUpgrade.getLocalBounds().width, lengthUpgrade.getLocalBounds().height };
	//sf::Vector2f baitUpgradeCoords = { baitUpgrade.getLocalBounds().width, baitUpgrade.getLocalBounds().height };

	//if (event.type == sf::Event::MouseMoved)
	//{
	//	sf::Vector2f coords = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
	//	//std::cout << coords.x << " " << coords.y << std::endl;
	//	if (baitUpgrade.getGlobalBounds().contains(coords) || lengthUpgrade.getGlobalBounds().contains(coords))
	//	{
	//		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	//		{
	//			std::cout << "CLICK" << std::endl;
	//		}
	//	}
	//}

}

void HUD::resize(sf::RenderTarget& window, sf::VideoMode windowSize)
{
	//sf::Vector2f center = { (float)window.getSize().x / 2, (float)window.getSize().y / 2 };

	//text.setPosition(window.mapPixelToCoords({64, 64}));
	//moneySprite.setPosition(0, 0);

	sf::Vector2f pos = window.mapPixelToCoords({ (int)(2 * offset), (int)offset });
	pos.x += moneySprite.getGlobalBounds().width;
	text.setPosition(pos);
	text.setPosition(window.mapPixelToCoords({ (int)offset, (int)offset / 4 }));
	moneySprite.setPosition(window.mapPixelToCoords({ (int)offset, (int)offset }));

	baitUpgrade.setPosition(window.mapPixelToCoords({ (int)(windowSize.width - offset), (int)(windowSize.height - offset) }));
	pos = window.mapPixelToCoords({ (int)(windowSize.width - 2 * offset), (int)(windowSize.height - offset) });
	pos.x -= baitUpgrade.getGlobalBounds().width;
	lengthUpgrade.setPosition(pos);
}

int HUD::getMoney()
{
	return money;
}

void HUD::modifyMoney(int value)
{
	money += value;
}
