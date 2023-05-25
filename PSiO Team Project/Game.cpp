#include "Game.h"

Game::Game()
{
    // initialize variables
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), title, sf::Style::Titlebar | sf::Style::Close); // sf::VideoMode::getDesktopMode() could be used for fullscreen
    event = new sf::Event();

    resources = new ResourceManager();

    mapBounds = sf::IntRect(0, 0, 3200, 4800);

    camera = new Camera(mapBounds);


    

    // components that need resource manager will be created in load method
    background = nullptr;
    character = nullptr;
    menu = nullptr;

    // additional configuration
    ShowWindow(window->getSystemHandle(), SW_MAXIMIZE); // maximize window
}

Game::~Game()
{
    delete window;
    delete event;

    delete resources;

    delete camera;

    delete background;
    delete character;

    delete menu;
}



void Game::run()
{
    load();

    while (window->isOpen()) {
        sf::Time time = clock.restart();

        handleEvents();
        update(time);
        draw();
    }
}



void Game::update(sf::Time time)
{
    window->setView(*camera->viewGame);

    if (!isPaused)
    {
        camera->moveTo(character->getPosition());
    }
    camera->update(time);

    background->update(time, *window);
    background->animate(time);

    character->update(time);
}

void Game::draw()
{
    window->clear(sf::Color::Black); // clear previous frame // sf::Color(3, 4, 94, 255)
    
    // draw things here...
    background->render(*window);
    character->render(*window);

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
            {
                isPaused = !isPaused;
                camera->moveTo(menu->getPosition());
            }
        }

        character->handleEvents(*event);
    }
}

void Game::load()
{
    // background textures
    resources->loadTexture("resources/background/sky.png");
    resources->loadTexture("resources/background/clouds.png");
    resources->loadTexture("resources/background/city.png");
    resources->loadTexture("resources/background/moon.png");
    resources->loadTexture("resources/background/water.png");

    // character textures
    resources->loadTexture("resources/character/character.png");

    // boats textures
    resources->loadTexture("resources/boats/raft.png");

    // --- components that need resources
    background = new Background(*resources, mapBounds);
    character = new Character(*resources, mapBounds);
    menu = new Menu(*resources, mapBounds);
}
