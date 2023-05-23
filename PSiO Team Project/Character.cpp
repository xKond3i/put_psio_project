#include "Character.h"
#include <iostream>


Character::Character()
{
	setup();
}

Character::~Character()
{
}

void Character::setup()
{
	if (!fisherman_texture.loadFromFile("Resources/fisherman.jpg")) { std::cout << "Nie znalazalo tekstury :)" << std::endl; return; }
	fisherman.setTexture(fisherman_texture);
	fisherman.setTextureRect(sf::IntRect(537,422, 664, 790));
	fisherman.setPosition(500,1500);
	fisherman.setScale(0.2,0.2);

}
void Character::draw(sf::RenderTarget& target)
{
	target.draw(fisherman);
}