#include "Game.h"

Game::Game()
{
    // --- INITIALIZE VARIABLES
    // --- GAME constructs
    window = new sf::RenderWindow(windowSize, title); // sf::VideoMode::getDesktopMode() could be used for fullscreen
    //window = new sf::RenderWindow(windowSize, title, sf::Style::Titlebar | sf::Style::Close); // sf::VideoMode::getDesktopMode() could be used for fullscreen
    event = sf::Event();

    resources = new ResourceManager();
    soundManager = new SoundManager(resources);
    camera = new Camera(windowSize);

    // --- components that NEED resource manager will be created in load method
    background = nullptr;
    player = nullptr;

    // --- ADDITIONAL CONFIGURATION
    //ShowWindow(window->getSystemHandle(), SW_MAXIMIZE); // maximize window
    //HWND consoleWindow = GetConsoleWindow();
    //ShowWindow(consoleWindow, SW_HIDE);

    icon.loadFromFile("resources/textures/icon.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

Game::~Game()
{
    // objects first
    delete background;
    delete player;

    delete splashScreen;



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
    const sf::Time timePerFrame = sf::seconds(1.f / fps);

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
            handleEvents();            // EVENTS per FIXED frame
            fixedUpdate(timePerFrame); // FIXED UPDATE

            timeSinceLastUpdate -= timePerFrame;
        }

        // DRAW
        draw();
    }
}



void Game::update(sf::Time time)
{
    sf::Time timeScaled = time * timeScale;
}

void Game::fixedUpdate(sf::Time time)
{
    sf::Time timeScaled = time * timeScale;

    background->fixedUpdate(time);
    background->moveMoon(camera->getView(Camera::GAME));

    camera->fixedUpdate(time);
    camera->fixToBounds(mapBounds);

    splashScreen->play(time);



    // Things, that work just when game is not paused
    if (paused) return;

    player->fixedUpdate(timeScaled);
    sf::IntRect boundsWithOffset = mapBounds;
    boundsWithOffset.left += background->getOffset() * 3;
    boundsWithOffset.width -= background->getOffset() * 6;
    player->checkFrameCollision(boundsWithOffset);

    
    if (player->FR->getInAction()) {
        sf::Vector2f pos = player->FR->getBaitPos();    
        camera->moveTo(pos);
    }
    else {
        sf::Vector2f pos = player->getPosition();    
        pos.y -= 100;
        camera->moveTo(pos);
    }
}



void Game::draw()
{
    window->clear(fillColor); // clear previous frame // sf::Color(3, 4, 94, 255)



    // --- Game View
    window->setView(*camera->getView(Camera::GAME));

    background->draw(*window);
    player->draw(*window);



    // --- UI View
    window->setView(*camera->getView(Camera::UI));

    splashScreen->draw(*window);



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
                if (splashScreen->entryFinished()) pause();
            }
        }

        // Window Resized
        if (event.type == sf::Event::Resized)
        {
            windowSize = { event.size.width, event.size.height };
        }

        camera->handleEvents(event);

        player->handleEvents(event);

        splashScreen->handleEvents(event, *window, paused);
    }
}



void Game::pause()
{
    paused = !paused;
    timeScale = paused ? 0.f : 1.f;

    camera->moveTo({ player->getPosition().x, 0 });

    splashScreen->restart();
    splashScreen->setFading(!paused);
}



void Game::load()
{
    /* ---------- TEXTURES ---------- */
    try {
        // splash screen
        resources->loadTexture("logo", "resources/textures/UI/logo.png", false);

        // background textures
        resources->loadTexture("bg/sky", "resources/textures/background/sky.png", true);
        resources->loadTexture("bg/clouds", "resources/textures/background/clouds.png", true);
        resources->loadTexture("bg/city_far", "resources/textures/background/city_far.png", true);
        resources->loadTexture("bg/city", "resources/textures/background/city.png", true);
        resources->loadTexture("bg/nature", "resources/textures/background/nature.png", true);
        resources->loadTexture("bg/lilies", "resources/textures/background/lilies.png", true);
        resources->loadTexture("bg/water", "resources/textures/background/water.png", true);
        resources->loadTexture("bg/waves", "resources/textures/background/water_waves.png", true);

        resources->loadTexture("bg/moon", "resources/textures/background/moon.png", true);
        resources->loadTexture("bg/map_border", "resources/textures/background/map_border.png", true);

        // player
        resources->loadTexture("player", "resources/textures/player/player.png", false);

        // bait
        resources->loadTexture("bait1", "resources/textures/baits/1.png", false);
        resources->loadTexture("bait2", "resources/textures/baits/2.png", false);
        resources->loadTexture("bait3", "resources/textures/baits/3.png", false);

        // UI
        resources->loadTexture("btn_play", "resources/textures/UI/play.png", false);
        resources->loadTexture("btn_exit", "resources/textures/UI/exit.png", false);
        resources->loadTexture("btn_muted", "resources/textures/UI/muted.png", false);
        resources->loadTexture("btn_unmuted", "resources/textures/UI/unmuted.png", false);
    }
    catch (std::exception e) {
        std::cout << e.what() << "\n";
    }

    /* ---------- SOUNDS ---------- */
    try {
        // background
        resources->loadSound("baitSplash", "./resources/sounds/bait_splash.wav");
        // ...
    }
    catch (std::exception e) {
        std::cout << e.what() << "\n";
    }

    // --- components that need resources
    background = new Background(resources, mapBounds);
    player = new Player(resources,soundManager);

    // SPLASH SCREEN
    splashScreen = new SplashScreen(resources, *window);
}
