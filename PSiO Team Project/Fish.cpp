#include "Fish.h"

Fish::Fish(ResourceManager* resources, int type, float startingY, sf::IntRect mapBounds)
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

    setOrigin(0, getLocalBounds().height / 2);

    // STATS
    type -= 1;

    swimmingDepth = startingY + (rand() % (int)(spawnRangesY[type].y - spawnRangesY[type].x) + spawnRangesY[type].x); // randomize
    strength = fishStrengths[type];
    speed = fishSpeeds[type];

    float width = rand() % 256 + 64;
    float startingX = rand() % (int)(mapBounds.width - 64 - width) + 32;
    cycleRangeX = { startingX, startingX + width }; // randomize

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

    float t = time.asSeconds();

    if (getPosition().x < cycleRangeX.x) {
        dir = 1;
        setScale({ (float)dir, (float)abs(dir) });
    }
    else if (getPosition().x > cycleRangeX.y) {
        dir = -1;
        setScale({ (float)dir, (float)abs(dir) });
    }

    float step = 10.f;
    float maxStep = 2.f;

    if (getPosition().y < swimmingDepth - maxStep) zigZag = true;
    else if (getPosition().y > swimmingDepth + maxStep) zigZag = false;

    float randomFactor = (float)(rand() % 11 + 5) / 10.f;

    // move
    move({ speed * dir * t * randomFactor, (zigZag ? step : -step) * t });
}

void Fish::baitCollision()
{

}

void Fish::boundsCollision()
{

}
