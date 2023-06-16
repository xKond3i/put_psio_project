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
    
    splashScreen = nullptr;
    background = nullptr;
    player = nullptr;
    hud = nullptr;

    // --- ADDITIONAL CONFIGURATION
    //ShowWindow(window->getSystemHandle(), SW_MAXIMIZE); // maximize window
    //HWND consoleWindow = GetConsoleWindow();
    //ShowWindow(consoleWindow, SW_HIDE);

    icon.loadFromFile("resources/textures/icon.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // RANDOM SEED
    srand(time(NULL));
}

Game::~Game()
{
    // objects first
    delete background;
    delete player;

    for (auto p : fishes) delete p;
    fishes.clear();

    delete splashScreen;

    delete hud;



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

    // ...
}

void Game::fixedUpdate(sf::Time time)
{
    sf::Time timeScaled = time * timeScale;

    background->fixedUpdate(time);
    background->moveMoon(camera->getView(Camera::GAME));

    camera->fixedUpdate(time);
    camera->fixToBounds(mapBounds);

    splashScreen->play(time, *window);



    // Things, that work just when game is not paused
    if (paused) return;

    player->fixedUpdate(timeScaled);
    sf::IntRect boundsWithOffset = mapBounds;
    boundsWithOffset.left += background->getOffset() * 3;
    boundsWithOffset.width -= background->getOffset() * 6;
    player->checkFrameCollision(boundsWithOffset);

    hud->modifyMoney(player->getFR()->getCollectedMoney());
    if (player->getFR()->getInAction()) {
        sf::Vector2f pos = player->getFR()->getBaitPos();    
        camera->moveTo(pos);

        player->getFR()->scanFishes(fishes);
    }
    else {
        sf::Vector2f pos = player->getPosition();    
        pos.y -= 100;
        camera->moveTo(pos);
    }

    // fishes
    for (const auto& f : fishes) {
        f->fixedUpdate(timeScaled);
    }
}



void Game::draw()
{
    window->clear(fillColor); // clear previous frame // sf::Color(3, 4, 94, 255)

    

    // --- Game View
    window->setView(*camera->getView(Camera::GAME));

    background->draw(*window);
    player->draw(*window);


    // fishes
    for (const auto& f : fishes) {
        f->draw(*window);
    }



    // --- UI View
    window->setView(*camera->getView(Camera::UI));

    splashScreen->draw(*window);
    hud->draw(*window);
    


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
        camera->handleEvents(event);

        if (event.type == sf::Event::Resized)
        {
            windowSize = { event.size.width, event.size.height };
        }

        player->handleEvents(event);

        window->setView(*camera->getView(Camera::UI));

        splashScreen->handleEvents(event, *window, paused);
        hud->handleEvents(event, *window);
        
        if (splashScreen->getWantToUnpause()) pause();
        if (splashScreen->getWantToExit()) window->close();
    }
}



void Game::pause()
{
    paused = !paused;
    timeScale = paused ? 0.f : 1.f;

    camera->moveTo({ player->getPosition().x, 0 });

    splashScreen->restart();
    splashScreen->setFading(!paused);

    // RESTART FISHING ROD
    player->getFR()->setInAction(0);
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

        // fishes
        resources->loadTexture("fish1", "resources/textures/catchables/1.png", false);
        resources->loadTexture("fish2", "resources/textures/catchables/2.png", false);
        resources->loadTexture("fish3", "resources/textures/catchables/3.png", false);
        resources->loadTexture("fish4", "resources/textures/catchables/4.png", false);
        resources->loadTexture("fish5", "resources/textures/catchables/5.png", false);
        resources->loadTexture("fish6", "resources/textures/catchables/6.png", false);

        // bait
        resources->loadTexture("bait1", "resources/textures/baits/1.png", false);
        resources->loadTexture("bait2", "resources/textures/baits/2.png", false);
        resources->loadTexture("bait3", "resources/textures/baits/3.png", false);

        // UI
        resources->loadTexture("btn_play", "resources/textures/UI/play.png", false);
        resources->loadTexture("btn_exit", "resources/textures/UI/exit.png", false);
        resources->loadTexture("btn_muted", "resources/textures/UI/muted.png", false);
        resources->loadTexture("btn_unmuted", "resources/textures/UI/unmuted.png", false);

        resources->loadTexture("money", "resources/textures/UI/money.png", false);
        resources->loadTexture("bait_upgrade", "resources/textures/UI/upgrade_hook.png", false);
        resources->loadTexture("length_upgrade", "resources/textures/UI/upgrade_length.png", false);

        
        //FONT
        resources->loadFont("pixel_font", "resources/fonts/pixel_font.ttf");
        resources->loadFont("poppins", "resources/fonts/poppins.ttf");
       
    }
    catch (std::exception e) {
        std::cout << e.what() << "\n";
    }

    /* ---------- SOUNDS ---------- */
    try {
        // background
        resources->loadSound("splash", "./resources/sounds/bait_splash.wav");
        resources->loadSound("reel", "./resources/sounds/fishing_reel_cut.wav");
        // ...
    }
    catch (std::exception e) {
        std::cout << e.what() << "\n";
    }

    // --- components that need resources
    background = new Background(resources, mapBounds);
    player = new Player(resources,soundManager);
    

    // SPLASH SCREEN
    window->setView(*camera->getView(Camera::UI));

    splashScreen = new SplashScreen(resources, soundManager, *window);
    hud = new HUD(resources, *window);

    // SPAWN FISH
    for (int i = 0; i < fishCount; ++i) {
        int type = rand() % Fish::maxType + 1;
        fishes.push_back(new Fish(resources, type, player->getPosition().y + 32, mapBounds));
    }
}
