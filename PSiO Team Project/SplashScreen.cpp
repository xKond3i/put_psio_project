#include "SplashScreen.h"

SplashScreen::SplashScreen(ResourceManager* resources, SoundManager* sm, sf::RenderWindow& window) {
    logo.setTexture(*resources->getTexture("logo"));
    auto bounds = logo.getLocalBounds();
    logo.setOrigin(bounds.width / 2, bounds.height / 2);

    dimm.setSize({ (float)window.getSize().x, (float)window.getSize().y });
    dimm.setPosition({ 0, 0 });

    sf::Vector2f center = window.mapPixelToCoords({ (int)window.getSize().x / 2, (int)window.getSize().y / 2 });
    //sf::Vector2f center = { (float)window.getSize().x / 2, (float)window.getSize().y / 2 };
    centerY = window.getSize().y / 2;
    windowHeight = window.getSize().y;
    logo.setPosition(center);

    // BUTTONS
    buttons["play"] = new Button(resources, "btn_play", center);
    center.x += buttonsSpacing;
    buttons["exit"] = new Button(resources, "btn_exit", center);
    center.x -= buttonsSpacing * 2;
    std::string names[2] = {"btn_unmuted", "btn_muted"};
    buttons["sound"] = new Button(resources, names, center);

    buttons["play"]->setScale(0.5);
    buttons["sound"]->setScale(0.5);
    buttons["exit"]->setScale(0.5);

    // ...
    SM = sm;
}

SplashScreen::~SplashScreen()
{
    buttons.clear();
}

void SplashScreen::draw(sf::RenderTarget& target)
{
    target.draw(dimm);
    target.draw(logo);

    if (!splashFirstTime) {
        for (const auto& pair : buttons) {
            auto btn = pair.second;
            target.draw(*btn);
        }
    }

}

void SplashScreen::play(sf::Time time, sf::RenderTarget& window)
{
    float progress = splashTime / splashTimeEnd;

    progress = progress > 1.f ? 1.f : progress < 0.f ? 0.f : progress;
    if (splashFadingOut) progress = 1.f - progress;

    for (const auto& pair : buttons) {
        auto name = pair.first;
        auto btn = pair.second;

        if (progress < 1) break;

        if (name == "exit") btn->animate(time, sf::Color(220, 20, 60));
        else btn->animate(time);
    }



    // FADE IN ANIMATION
    if (splashTime > splashTimeEnd) {
        if (splashFirstTime) splashFirstTime = false;
        return;
    }

    splashTime += time;

    sf::Uint8 alpha = (int)(255 * progress);
    dimm.setFillColor({ 0, 0, 0, (splashFirstTime ? alpha : sf::Uint8(alpha / 2)) });
    logo.setColor({ 255, 255, 255, alpha });

    float height = logo.getGlobalBounds().height + buttons["play"]->getGlobalBounds().height + spacing;
    float borderSpacing = windowHeight - height;

    if (!splashFirstTime) {
        float goal = borderSpacing / 2 + logo.getGlobalBounds().height / 2;
        float diff = abs(goal - centerY);
        sf::Vector2f pos = window.mapPixelToCoords({ (int)window.getSize().x / 2, (int)(centerY) });
        pos.y -= diff * progress;
        logo.setPosition(pos);
    }

    // BUTTONS
    for (const auto& pair : buttons) {
        auto name = pair.first;
        auto btn = pair.second;
        float goal = windowHeight - borderSpacing / 2 - btn->getGlobalBounds().height / 2;
        float diff = abs(goal - centerY);
        btn->setColor({ 255, 255, 255, alpha });
        sf::Vector2f pos = window.mapPixelToCoords({ 0, (int)(centerY) });
        pos.x = btn->getPosition().x;
        pos.y += diff * progress;
        btn->setPosition(pos);
    }
}



void SplashScreen::restart()
{
    splashTime = sf::Time::Zero;
    
    wantToUnpause = false;
}

void SplashScreen::setFading(bool fading)
{
    splashFadingOut = fading;
}



void SplashScreen::handleEvents(sf::Event event, sf::RenderTarget& window, bool paused)
{
    if (event.type == sf::Event::Resized)
    {
        resize(window, { event.size.width, event.size.height });
    }

    if (!paused) return;

    if (event.type == sf::Event::MouseMoved)
    {
        // DON'T CHECK IF ANIMATION PLAYING
        float progress = splashTime / splashTimeEnd;
        if (progress < 1) return;

        sf::Vector2f coords = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });

        // HOVERING EFFECT
        for (const auto& pair : buttons) {
            auto btn = pair.second;
            btn->setHovered(btn->getGlobalBounds().contains(coords));
        }
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        // DON'T CHECK IF ANIMATION PLAYING
        float progress = splashTime / splashTimeEnd;
        if (progress < 1) return;

        // LEFT BUTTON CLICKED
        if (event.mouseButton.button != sf::Mouse::Left) return;

        // BUTTONS ACTIONS
        for (const auto& pair : buttons) {
            auto name = pair.first;
            auto btn = pair.second;

            if (!btn->getHovered()) continue;
            
            if (name == "play") {
                wantToUnpause = true;
            }
            else if (name == "sound") {
                btn->toggle();
                SM->setMuted(btn->getState());
            }
            else if (name == "exit") {
                wantToExit = true;
            }
        }
    }
}



void SplashScreen::resize(sf::RenderTarget& window, sf::VideoMode windowSize)
{
    sf::Vector2f center = window.mapPixelToCoords({ (int)windowSize.width / 2, (int)windowSize.height / 2 });
    //sf::Vector2f center = { (float)window.getSize().x / 2, (float)window.getSize().y / 2 };
    centerY = windowSize.height / 2;
    windowHeight = (float)windowSize.height;

    dimm.setSize({ (float)windowSize.width, (float)windowSize.height });

    logo.setPosition(center);

    buttons["play"]->setPosition(center);
    center.x += buttonsSpacing;
    buttons["exit"]->setPosition(center);
    center.x -= buttonsSpacing * 2;
    buttons["sound"]->setPosition(center);
}



bool SplashScreen::entryFinished()
{
    return !splashFirstTime;
}

bool SplashScreen::getWantToUnpause()
{
    return wantToUnpause;
}

bool SplashScreen::getWantToExit()
{
    return wantToExit;
}
