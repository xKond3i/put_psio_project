#include "Game.h"

Game::Game()
{
    // --- INITIALIZE VARIABLES
    // --- GAME constructs
    window = new sf::RenderWindow(windowSize, title); // sf::VideoMode::getDesktopMode() could be used for fullscreen
    //window = new sf::RenderWindow(windowSize, title, sf::Style::Titlebar | sf::Style::Close); // sf::VideoMode::getDesktopMode() could be used for fullscreen
    event  = sf::Event();
    
    resources    = new ResourceManager();
    soundManager = new SoundManager();
    camera       = new Camera(windowSize);

    // --- components that NEED resource manager will be created in load method
    background = nullptr;
    player     = nullptr;

    // --- ADDITIONAL CONFIGURATION
    //ShowWindow(window->getSystemHandle(), SW_MAXIMIZE); // maximize window
    icon.loadFromFile("resources/textures/icon.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // SPLASH SCREEN
    dimm.setSize({ (float)windowSize.width, (float)windowSize.height });
    dimm.setPosition({ 0, 0 });

    logo.setPosition({ (float)windowSize.width / 2, (float)windowSize.height / 2 });
}

Game::~Game()
{
    // objects first
    delete background;
    delete player;



    // more important constructs last
    delete camera;
    delete soundManager;
    delete resources;
    delete window;
}



void Game::run()
{
    // --- TIME
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time timePerFrame  = sf::seconds(1.f / fps);

    load(); // load resources

    while (window->isOpen()) {
        sf::Time time = clock.restart();
        timeSinceLastUpdate += time;

        // EVENTS
        handleEvents();
        
        // UPDATE
        update(time);

        // FIXED UPDATE
        while (timeSinceLastUpdate > timePerFrame)
        {
            handleEvents();                      // EVENTS per FIXED frame
            fixedUpdate(timePerFrame);           // FIXED UPDATE
            timeSinceLastUpdate -= timePerFrame;
        }

        // DRAW
        draw();
    }
}



void Game::update(sf::Time time)
{
    time = time * timeScale;

    // ...
}

void Game::fixedUpdate(sf::Time time)
{
    sf::Time timeScaled = time * timeScale;

    background->fixedUpdate(time);
    background->moveMoon(camera->getView(Camera::GAME));

    player->fixedUpdate(timeScaled);

    sf::Vector2f pos = player->getPosition();
    pos.y -= 100;
    if (!paused) camera->moveTo(pos);

    camera->fixedUpdate(time);
    camera->fixToBounds(mapBounds);

    // ...

    splashScreen(time);
}



void Game::draw()
{
    window->clear(fillColor); // clear previous frame // sf::Color(3, 4, 94, 255)

    // --- Game View
    window->setView(*camera->getView(Camera::GAME));

    // draw things here...
    background->draw(*window);
    window->draw(*player);

    // --- UI View
    window->setView(*camera->getView(Camera::UI));

    // SPLASH SCREEN
    window->draw(dimm);
    window->draw(logo);

    window->display(); // show current frame
}



void Game::handleEvents()
{
    while (window->pollEvent(event)) {
        // Close Button
        if (event.type == sf::Event::Closed)
            window->close();

        // KeyPressed
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
            {
                paused = !paused;
                timeScale = paused ? 0.f : 1.f;

                camera->moveTo({ player->getPosition().x, 0 });
                splashTime = sf::Time::Zero;

                splashFadingOut = !paused;
            }
        }

        // Window Resized
        if (event.type == sf::Event::Resized)
        {
            windowSize = { event.size.width, event.size.height };
            
            // SPLASH SCREEN
            dimm.setSize({ (float)windowSize.width, (float)windowSize.height });
            logo.setPosition({ (float)windowSize.width / 2, (float)windowSize.height / 2 });
        }

        //if (event.type == sf::Event::MouseMoved) {
        //    window->setView(*camera->getView(Camera::GAME));
        //    sf::Vector2f coords = window->mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
        //    std::cout << "[" << coords.x << ", " << coords.y << "]\n";
        //}

        camera -> handleEvents(event);
    }
}



void Game::load()
{
    /* ---------- TEXTURES ---------- */
    try {
        // splash screen
        resources->loadTexture("logo", "resources/textures/UI/logo.png", false);

        // background textures
        resources->loadTexture("bg/sky",      "resources/textures/background/sky.png",         true);
        resources->loadTexture("bg/clouds",   "resources/textures/background/clouds.png",      true);
        resources->loadTexture("bg/city_far", "resources/textures/background/city_far.png",    true);
        resources->loadTexture("bg/city",     "resources/textures/background/city.png",        true);
        resources->loadTexture("bg/nature",   "resources/textures/background/nature.png",      true);
        resources->loadTexture("bg/lilies",   "resources/textures/background/lilies.png",      true);
        resources->loadTexture("bg/water",    "resources/textures/background/water.png",       true);
        resources->loadTexture("bg/waves",    "resources/textures/background/water_waves.png", true);

        resources->loadTexture("bg/moon", "resources/textures/background/moon.png", true);
        resources->loadTexture("bg/map_border", "resources/textures/background/map_border.png", true);

        // player
        resources->loadTexture("player", "resources/textures/player/player.png", false);
    }
    catch (std::exception e) {
        std::cout << e.what() << "\n";
    }

    /* ---------- SOUNDS ---------- */
    try {
        // background
        // ...
    }
    catch (std::exception e) {
        std::cout << e.what() << "\n";
    }

    // --- components that need resources
    background = new Background(resources, mapBounds);
    player = new Player(resources);

    // SPLASH SCREEN
    logo.setTexture(*resources->getTexture("logo"));
    auto bounds = logo.getLocalBounds();
    logo.setOrigin(bounds.width / 2, bounds.height / 2);
}



void Game::splashScreen(sf::Time time)
{
    if (splashTime > splashTimeEnd) {
        if (splashFirstTime) splashFirstTime = false;
        return;
    }
    
    splashTime += time;

    float progress = splashTime / splashTimeEnd;
    if (splashFadingOut) progress = 1.f - progress;
    
    sf::Uint8 alpha = (int)(255 * progress);
    dimm.setFillColor({ 0, 0, 0, (splashFirstTime ? alpha : sf::Uint8(alpha / 2)) });
    logo.setColor({ 255, 255, 255, alpha });
}
