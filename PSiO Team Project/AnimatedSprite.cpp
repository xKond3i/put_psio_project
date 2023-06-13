#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() {

}

AnimatedSprite::AnimatedSprite(sf::Texture* texture, std::vector<sf::IntRect> frames_, unsigned int fps_) {
	setTexture(*texture);
	setFrames(frames_);
	setFPS(fps_);
}

AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::setFrames(std::vector<sf::IntRect> frames_) {
	frames = frames_;
	if (!frames.empty()) setTextureRect(frames[currentFrame]);
}

void AnimatedSprite::setFPS(unsigned int fps_) {
	fps = fps_;
	timePerFrame = sf::seconds(1. / fps);
}

void AnimatedSprite::fixedUpdate(sf::Time time) {
	if (frames.empty()) return;

	animationTime += time;
	if (animationTime >= timePerFrame) {
		currentFrame = (currentFrame + 1) % (int)frames.size();
		animationTime -= timePerFrame;
		setTextureRect(frames[currentFrame]);
	}
}
