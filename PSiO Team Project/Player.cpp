#include "Player.h"

Player::Player(ResourceManager* resources)
{
    std::vector<sf::IntRect> frames_;
    for (int i = 0; i < (int)frameCount; ++i) {
        frames_.push_back({ i * frameSize.x, 0, frameSize.x, frameSize.y });
    }

    setFrames(frames_);
    setFPS(frameCount);

    setTexture(*resources->getTexture("player"));
    setOrigin(0, (float)getTexture()->getSize().y);

    setPosition(64, 400);
}

Player::~Player()
{

}
