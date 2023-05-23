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
	if (!fisherman_texture.loadFromFile("fisherman.jpg")) { std::cout << "Nie znalazalo tekstury :)" << std::endl; return; }
	fisherman.setTexture(fisherman_texture);
	fisherman.setTextureRect(sf::IntRect(537,422, 664, 790));
	fisherman.setPosition(0,0);

}
void Character::drawCharacter(sf::RenderTarget& target)
{
	target.draw(fisherman);
}