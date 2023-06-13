#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

class AnimatedSprite : public sf::Sprite
{
protected:
	unsigned int currentFrame = 0;
	unsigned int fps = 30;
	sf::Time timePerFrame = sf::Time::Zero;
	sf::Time animationTime = sf::Time::Zero;

	std::vector<sf::IntRect> frames;

public:
	AnimatedSprite();
	AnimatedSprite(sf::Texture* texture, std::vector<sf::IntRect> frames_ = {}, unsigned int fps_ = 30);
	~AnimatedSprite();



	void setFrames(std::vector<sf::IntRect> frames_);
	void setFPS(unsigned int fps_);

	void fixedUpdate(sf::Time time);
};
