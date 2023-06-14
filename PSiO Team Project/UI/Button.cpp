#include "Button.h"

Button::Button(ResourceManager* resources, std::string texName, sf::Vector2f pos, bool originCenter, bool disabled_)
{
	disabled = disabled_;
	toggleable = false;

	states[0] = resources->getTexture(texName);
	setTexture(*states[state]);

	setPosition(pos);



	if (!originCenter) return;

	sf::FloatRect bounds = getLocalBounds();
	setOrigin(bounds.width / 2, bounds.height / 2);
}

Button::Button(ResourceManager* resources, std::string texNames[2], sf::Vector2f pos, bool originCenter, bool disabled_)
{
	disabled = disabled_;
	toggleable = true;

	states[0] = resources->getTexture(texNames[0]);
	states[1] = resources->getTexture(texNames[1]);
	setTexture(*states[state]);

	setPosition(pos);



	if (!originCenter) return;

	sf::FloatRect bounds = getLocalBounds();
	setOrigin(bounds.width / 2, bounds.height / 2);
}

Button::~Button()
{
	delete[] states;
}

void Button::handleEvents(sf::Event event)
{

}

void Button::draw(sf::RenderTarget& target)
{
	target.draw(*this);
}

void Button::animate(sf::Time time)
{
	if (animTime > animTimeEnd) return;

	animTime += time;

	float progress = animTime / animTimeEnd;
	progress = progress > 1.f ? 1.f : progress < 0.f ? 0.f : progress;
	if (hovered) progress = 1.f - progress;

	float scale = .5f + .1f * progress;
	setScale(scale);
}

void Button::setHovered(bool hovered_)
{
	if (hovered_ == hovered) return;
	hovered = hovered_;
	animTime = sf::Time::Zero;
}

void Button::setScale(float factor)
{
	initialScale = factor;
	sf::Sprite::setScale(factor, factor);
}
