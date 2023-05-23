#include "Game.h"


Game::Game()
{
    // initialize variables
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), title); // sf::VideoMode::getDesktopMode() could be used for fullscreen
    event = new sf::Event();

    camera = new Camera();

    background = new Background();
    character = new Character();

    // additional configuration
    ShowWindow(window->getSystemHandle(), SW_MAXIMIZE); // maximize window
}

Game::~Game()
{
    delete window;
    delete event;

    delete camera;

    delete background;
    delete character;
}

void Game::run()
{
    while (window->isOpen()) {
        handleEvents();
        update();
        draw();
    }
}

void Game::update()
{
    camera->update();
}

void Game::draw()
{
    window->clear(sf::Color(3, 4, 94, 255)); // clear previous frame
    
    // draw things here...
    background->renderBackground(*window);
    character->drawCharacter(*window);
    


    window->display(); // show current frame
    
}

void Game::handleEvents()
{
    while (window->pollEvent(*event)) {
        // Close Button
        if (event->type == sf::Event::Closed)
            window->close();

        // KeyPressed
        if (event->type == sf::Event::KeyPressed) {
            if (event->key.code == sf::Keyboard::Escape)
                window->close();
        }
    }
}
