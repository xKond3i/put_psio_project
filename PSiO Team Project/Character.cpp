#include "Character.h"
#include <iostream>


Character::Character()
{
	setupCharacter();
}

Character::~Character()
{
}

void Character::setupCharacter()
{
	if (!fisherman_texture.loadFromFile("resources/fisherman.jpg")) { std::cout << "Nie znalazalo tekstury :)" << std::endl; return; }
	fisherman.setTexture(fisherman_texture);
	fisherman.setTextureRect(sf::IntRect(537,422, 664, 770));
	fisherman.setScale(0.2, 0.2);
	fisherman.setPosition(500, 1500);

}

void Character::drawCharacter(sf::RenderTarget& target)
{
	target.draw(fisherman);
}
