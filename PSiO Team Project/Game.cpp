#include "Game.h"

Game::Game()
{
    // initialize variables
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), title, sf::Style::Titlebar | sf::Style::Close); // sf::VideoMode::getDesktopMode() could be used for fullscreen
    event = new sf::Event();

    resources = new ResourceManager();

    camera = new Camera(sf::IntRect(0, 0, 3200, 4800));

    // components that need resource manager will be created in load method
    background = nullptr;
    //character = new Character();

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
    //delete character;
}



void Game::run()
{
    load();

    while (window->isOpen()) {
        handleEvents();
        update();
        draw();
    }
}



void Game::update()
{
    camera->update();
    window->setView(*camera->viewGame);

    background->animate();
}

void Game::draw()
{
    window->clear(sf::Color::Black); // clear previous frame // sf::Color(3, 4, 94, 255)
    
    // draw things here...
    background->render(*window);
    //character->draw(*window);

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
            
            // TO BE REPLACED
            if (event->key.code == sf::Keyboard::A || event->key.code == sf::Keyboard::Left) {
                camera->move(-5, 0);
            } else if (event->key.code == sf::Keyboard::D || event->key.code == sf::Keyboard::Right) {
                camera->move(5, 0);
            }
            if (event->key.code == sf::Keyboard::W || event->key.code == sf::Keyboard::Up) {
                camera->move(0, -5);
            }
            else if (event->key.code == sf::Keyboard::S || event->key.code == sf::Keyboard::Down) {
                camera->move(0, 5);
            }
        }
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
    background = new Background(*resources);
}
