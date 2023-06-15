#include "Fish.h"

Fish::Fish(ResourceManager* resources, int type, float startingY_, sf::IntRect mapBounds_)
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

    setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);

    startingY = startingY_;
    mapBounds = mapBounds_;

    // STATS
    type -= 1;

    swimmingDepth = startingY + (rand() % (int)(spawnRangesY[type].y - spawnRangesY[type].x) + spawnRangesY[type].x); // randomize
    strength = fishStrengths[type];
    speed = fishSpeeds[type];
    price = fishPrices[type];

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

void Fish::followBait(sf::Time time, sf::Vector2f target)
{
    float t = time.asSeconds();

    sf::Vector2f pos = getPosition();
    sf::Vector2f dest = pos + (target - pos) * t * speed; // destination

    float d = hypot(dest.x - pos.x, dest.y - pos.y);

    if (d < .4f && abs(getRotation() - (dir < 0 ? 90.f : 270.f)) > 5.f) {
        rotate(t * 30);
    }

    setPosition(dest);
}

float Fish::fight(sf::Time time)
{
    float t = time.asSeconds();
    if (stamina > 1) {
        if (abs(getRotation() - (dir < 0 ? 270.f : 90.f)) > 10.f) {
            rotate(-t * 60);
        }
        stamina -= stamina * t;
        return strength * t;
    }
    return 0.0f;
}

void Fish::setFree()
{
    setRotation(0);
}

int Fish::respawn()
{
    swimmingDepth = startingY + (rand() % (int)(spawnRangesY[type].y - spawnRangesY[type].x) + spawnRangesY[type].x); // randomize

    float width = rand() % 256 + 64;
    float startingX = rand() % (int)(mapBounds.width - 64 - width) + 32;
    cycleRangeX = { startingX, startingX + width }; // randomize

    setPosition(cycleRangeX.x, swimmingDepth);
    setRotation(0);

    return price;
}
