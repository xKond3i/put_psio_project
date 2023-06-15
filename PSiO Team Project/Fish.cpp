#include "Fish.h"

Fish::Fish(ResourceManager* resources, int type, float startingY)
{
    int frameCount = 2;
    std::vector<sf::IntRect> frames_;

    sf::Texture* tex = resources->getTexture("fish" + std::to_string(type));
    sf::Vector2u texSize = tex->getSize();

    for (int i = 0; i < frameCount; ++i) {
        frames_.push_back({ i * ((int)texSize.x / frameCount), 0, (int)texSize.x / frameCount, (int)texSize.y });
    }

    setFrames(frames_);
    setFPS(frameCount);

    setTexture(*tex);

    // STATS
    swimmingDepth = startingY + 50; // randomize
    strength = fishStrengths[type];
    speed = fishSpeeds[type];

    cycleRangeX = { 25, 100 }; // randomize

    setPosition(cycleRangeX.x, swimmingDepth);
}

Fish::~Fish()
{

}

void Fish::draw(sf::RenderTarget& target)
{
    target.draw(*this);
}

void Fish::update(sf::Time time)
{

}

void Fish::fixedUpdate(sf::Time time)
{
    AnimatedSprite::fixedUpdate(time);
}

void Fish::baitCollision()
{

}

void Fish::boundsCollision()
{

}
