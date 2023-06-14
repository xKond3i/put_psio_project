#include "SplashScreen.h"

SplashScreen::SplashScreen(ResourceManager* resources, sf::RenderWindow& window) {
    logo.setTexture(*resources->getTexture("logo"));
    auto bounds = logo.getLocalBounds();
    logo.setOrigin(bounds.width / 2, bounds.height / 2);

    dimm.setSize({ (float)window.getSize().x, (float)window.getSize().y });
    dimm.setPosition({ 0, 0 });

    logo.setPosition({ (float)window.getSize().x / 2, (float)window.getSize().y / 2 });
}

SplashScreen::~SplashScreen()
{

}

void SplashScreen::draw(sf::RenderTarget& target)
{
    target.draw(dimm);
    target.draw(logo);
}

void SplashScreen::play(sf::Time time){

    if (splashTime > splashTimeEnd) {
        if (splashFirstTime) splashFirstTime = false;
        return;
    }

    splashTime += time;

    float progress = splashTime / splashTimeEnd;
    progress = progress > 1.f ? 1.f : progress < 0.f ? 0.f : progress;
    if (splashFadingOut) {
        progress = 1.f - progress;
    }

    sf::Uint8 alpha = (int)(255 * progress);
    dimm.setFillColor({ 0, 0, 0, (splashFirstTime ? alpha : sf::Uint8(alpha / 2)) });
    logo.setColor({ 255, 255, 255, alpha });
}

void SplashScreen::restart()
{
    splashTime = sf::Time::Zero;
}

void SplashScreen::setFading(bool fading)
{
    splashFadingOut = fading;
}

void SplashScreen::resize(sf::VideoMode windowSize)
{
    dimm.setSize({ (float)windowSize.width, (float)windowSize.height });
    logo.setPosition({ (float)windowSize.width / 2, (float)windowSize.height / 2 });

    logo.setPosition({ (float)windowSize.width / 2, (float)windowSize.height / 2 });
}
