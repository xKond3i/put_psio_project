#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Character
{
private:
	sf::Sprite fisherman;
	sf::Texture fisherman_texture;
public:
	Character();
	~Character();
	void drawCharacter(sf::RenderTarget& target);
	void setupCharacter();
	

};
