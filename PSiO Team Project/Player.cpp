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
    sf::FloatRect bounds = getLocalBounds();
    setOrigin(bounds.width / 2, bounds.height);

    setPosition(96 + bounds.width / 2, 400);

    //Fishing Rod
    FR = new FishingRod(resources);
}

Player::~Player()
{

}

void Player::checkFrameCollision(sf::IntRect frame)
{
    sf::FloatRect bounds = getGlobalBounds();

    float left = bounds.left;
    float right = bounds.left + bounds.width;

    if (left < frame.left) setPosition(frame.left + bounds.width / 2, getPosition().y);
    else if (right > frame.left + frame.width) setPosition(frame.left + frame.width - bounds.width / 2, getPosition().y);
}

void Player::handleEvents(sf::Event event)
{
    // KeyPressed
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            dir = -1;
            holdingLeft = true;
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            dir = 1;
            holdingRight = true;
            break;
        }
    }

    // KeyReleased
    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            holdingLeft = false;
            slideDir = dir;
            dir = holdingRight ? 1 : 0;
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            holdingRight = false;
            slideDir = dir;
            dir = holdingLeft ? -1 : 0;
            break;
        }
    }
}

void Player::update(sf::Time time)
{

}

void Player::fixedUpdate(sf::Time time)
{
    AnimatedSprite::fixedUpdate(time);

    float t = time.asSeconds();

    if (dir != 0) setScale({ (float)dir, (float)abs(dir) });

    if (dir == 0 && speed <= 0) {
        speed = 0;
        slideDir = 0;
        return;
    }
    
    // handle speed and acceleration
    if (dir == 0) speed -= acceleration;
    else speed += acceleration;
    speed = speed > maxSpeed ? maxSpeed : speed;
    
    // move
    if (dir == 0) move({ speed * slideDir * t, 0 });
    else move({ speed * dir * t, 0 });
}

void Player::draw(sf::RenderTarget& target)
{
    target.draw(*this);
}
