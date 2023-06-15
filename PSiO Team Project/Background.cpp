#include "Background.h"

/* ---------- LAYER ---------- */
Layer::Layer(sf::Texture* texture, sf::IntRect size, sf::Vector2f pos, int moving_, bool originBottom)
{
    moving = moving_;
    
    // Texture Size
    sf::Vector2u textureSize = texture->getSize();
    size.height = textureSize.y;
    if (moving > 0) {
        size.left  -= textureSize.x;
        size.width += textureSize.x * 2;

        pos.x -= textureSize.x;
    }

    setTexture(*texture);
    setTextureRect(size);

    // Origin
    if (originBottom) setOrigin(0, (float)size.height);

    setPosition(pos);
}

Layer::~Layer()
{

}

void Layer::animate(sf::Time time, float parallaxIndex, float parallaxSpeed, float parallaxModifier)
{
    if (moving == Layer::MOVING_NEVER) return;

    float t = time.asSeconds();

    // ANIMATION STYLES
    if (moving == Layer::MOVING_ZIGZAG) {
        float step = .25f;
        float maxStep = .5f;
        float currentStep = getPosition().x;
        float textureSize = getTexture()->getSize().x;

        float d = parallaxIndex * parallaxModifier * parallaxSpeed * t * (zigZagDir ? step : -step);
        move({ d, d });

        if (currentStep < -textureSize - maxStep) zigZagDir = true;
        else if (currentStep > -textureSize + maxStep) zigZagDir = false;

    }
    if (moving == Layer::MOVING_ALWAYS) {
        move(parallaxIndex * parallaxModifier * parallaxSpeed * t, 0);
        sf::Vector2f pos = getPosition();
        int width = getTexture()->getSize().x;
        if (pos.x >= 0) setPosition(-width, pos.y);
    }
}



/* ---------- BACKGROUND ---------- */
Background::Background(ResourceManager* resources, sf::IntRect mapBounds_)
{
    mapBounds = mapBounds_;

    drawingOrder = { "sky", "clouds", "city_far", "city", "nature", "water", "waves", "lilies" };

    layers["sky"] = new Layer(resources->getTexture("bg/sky"), mapBounds, { 0, 0 }, Layer::MOVING_NEVER, false);
    float baseLine = layers["sky"]->getGlobalBounds().height;

    // moving in distance
    layers["clouds"] = new Layer(resources->getTexture("bg/clouds"), mapBounds, { 0, baseLine }, Layer::MOVING_ALWAYS, true);

    // moving with player
    layers["city_far"] = new Layer(resources->getTexture("bg/city_far"), mapBounds, { 0, baseLine }, Layer::MOVING_NEVER, true);
    layers["city"] =     new Layer(resources->getTexture("bg/city"),     mapBounds, { 0, baseLine }, Layer::MOVING_NEVER, true);

    // static
    layers["nature"] = new Layer(resources->getTexture("bg/nature"), mapBounds, { 0, baseLine + .5f }, Layer::MOVING_ZIGZAG, true);
    layers["lilies"] = new Layer(resources->getTexture("bg/lilies"), mapBounds, { 0, baseLine },       Layer::MOVING_ZIGZAG, false);

    // water
    layers["water"] = new Layer(resources->getTexture("bg/water"), mapBounds, { 0, baseLine - 2.f }, Layer::MOVING_NEVER,  false);
    layers["waves"] = new Layer(resources->getTexture("bg/waves"), mapBounds, { 0, baseLine },       Layer::MOVING_ALWAYS, false);

    sf::IntRect size = layers["waves"]->getTextureRect();
    size.height = layers["water"]->getTextureRect().height;
    layers["waves"]->setTextureRect(size);

    // moon
    moon.setTexture(*resources->getTexture("bg/moon"));
    moon.setOrigin({ moon.getLocalBounds().width, 0 });

    // MAP BORDERS
    sf::Vector2u textureSize = resources->getTexture("bg/map_border")->getSize();
    std::vector<sf::IntRect> frames = { {0, 0, 32, 32}, {32, 0, 32, 32} };

    borderSymbolLeft = new AnimatedSprite(resources->getTexture("bg/map_border"), frames, 2);
    borderSymbolLeft->setPosition({ offset + textureSize.x / 2, baseLine + offset });
    borderSymbolLeft->setOrigin(textureSize.x / 2, textureSize.y / 2);

    borderSymbolRight = new AnimatedSprite(resources->getTexture("bg/map_border"), frames, 2);
    borderSymbolRight->setPosition({ (float)mapBounds.width - textureSize.x / 2, baseLine + offset });
    borderSymbolRight->setOrigin(textureSize.x / 2, textureSize.y / 2);
}

Background::~Background()
{
    for (auto p : layers) delete p.second;
    layers.clear();

    delete borderSymbolLeft;
    delete borderSymbolRight;
}

void Background::update(sf::Time time)
{

}

void Background::fixedUpdate(sf::Time time)
{
    float t = time.asSeconds();

    int parallaxIndex = 1;
    for (const auto& name : drawingOrder) {
        if (layers.count(name) <= 0) continue;

        Layer* layer = layers[name];
        layer->animate(time, ((float)parallaxIndex / (float)drawingOrder.size()), parallaxSpeed, parallaxModifier);

        parallaxIndex++;
    }

    // MAP BORDER SYMBOL ANIMATION
    borderSymbolLeft->fixedUpdate(time);
    borderSymbolRight->fixedUpdate(time);

    float angle = 3;
    float maxAngle = 10;
    float rotation = borderSymbolLeft->getRotation(); // < 345 || > 15

    borderSymbolLeft->rotate((borderSymbolAnimDir ? angle : -angle) * t);
    borderSymbolRight->rotate((borderSymbolAnimDir ? angle : -angle) * t);

    if (rotation < 360 - maxAngle && rotation > 180) borderSymbolAnimDir = true;
    else if (rotation > maxAngle && rotation < 180) borderSymbolAnimDir = false;
}

void Background::draw(sf::RenderWindow& target)
{
    for (const auto& name : drawingOrder) {
        if (layers.count(name) <= 0) continue;
        target.draw(*layers[name]);
    }

    target.draw(moon);

    target.draw(*borderSymbolLeft);
    target.draw(*borderSymbolRight);
}

float Background::getOffset()
{
    return offset;
}

void Background::moveMoon(sf::View* view)
{
    sf::Vector2f center = view->getCenter();
    sf::Vector2f size = view->getSize();
    float offset = 32;

    moon.setPosition({ center.x + size.x / 2 - offset, offset });
}
