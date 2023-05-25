#include "Character.h"

void Character::move(int dir)
{
    if (dir == 0) {
        moving = false;
        return;
    }

    moving = true;
    float scale = std::abs(character.getScale().x);

    if (dir < 0) {
        character.setScale(-scale, scale);
        speed = -std::abs(speed);

        rod->setScale(-scale, scale);
    } else {
        character.setScale(scale, scale);
        speed = std::abs(speed);

        rod->setScale(scale, scale);
    }
}

void Character::mapBoundsCollision()
{
    float mapBottomEdge = mapBounds.top + mapBounds.height;
    float mapRightEdge = mapBounds.left + mapBounds.width;

    sf::FloatRect characterBounds = character.getGlobalBounds();

    float characterBottomEdge = characterBounds.top + characterBounds.height;
    float characterRightEdge = characterBounds.left + characterBounds.width;

    if (characterBounds.left <= mapBounds.left) {
        character.setPosition(getPosition().x + std::abs(characterBounds.left - mapBounds.left), getPosition().y);
        moving = false;
    } else if (characterRightEdge >= mapRightEdge) {
        character.setPosition(getPosition().x - std::abs(characterRightEdge - mapRightEdge), getPosition().y);
        moving = false;
    }
}

Character::Character(ResourceManager& resources, sf::IntRect mapBounds_)
{
	boat = new Boat(resources);
    rod = new Rod(resources);

	sf::Texture* texture = resources.getTexture("resources/character/character.png");
	character.setTexture(*texture);
    character.setOrigin(character.getLocalBounds().width / 2, 0);

    mapBounds = mapBounds_;
    mapBounds.left += 128;
    mapBounds.top += 128;
    mapBounds.width -= 256;
    mapBounds.height -= 256;

	// [PLACEHOLDER]
	character.setScale(0.5, 0.5);
	character.setPosition(256 + character.getGlobalBounds().width / 2, 1216);
}

Character::~Character()
{
	delete boat;
}

void Character::render(sf::RenderTarget& target)
{
	boat->render(target);
	target.draw(character);
    rod->render(target);
}

void Character::update(sf::Time time)
{
    float t = time.asMilliseconds() / 1000.0;

    if (moving) {
        acceleration = acceleration > 1 ? 1 : acceleration + t;

        character.move(speed * acceleration * t, 0);
    } else {
        acceleration = acceleration < 0 ? 0 : acceleration - t;
    }

    mapBoundsCollision();

    boat->setPosition(character.getPosition());
    rod->setPosition(character.getPosition());
}

void Character::handleEvents(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            move(-1);
            break;
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            move(1);
            break;
        }
    }

    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                move(0);
            }
            break;
        }
    }
}

sf::Vector2f Character::getPosition()
{
    return character.getPosition();
}
