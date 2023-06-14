#include "SplashScreen.h"

SplashScreen::SplashScreen(sf::RenderWindow window) {

    dimm.setSize({ (float)window.getSize().x, (float)window.getSize().y });
    dimm.setPosition({ 0, 0 });

    logo.setPosition({ (float)window.getSize().x / 2, (float)window.getSize().y / 2 });
   
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
