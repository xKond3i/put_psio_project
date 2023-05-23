#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <windows.h>

int main() {

    sf::RenderWindow window(sf::VideoMode(1280, 720), "PSiO Team Project"); // sf::VideoMode::getDesktopMode() could be used for fullscreen
    ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close Button
            if (event.type == sf::Event::Closed)
                window.close();

            // KeyPressed
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        // --- DRAW LOOP ---
        // Clear window
        window.clear(sf::Color::Black);

        // Draw things here...
           

        // Show current frame
        window.display();
    }

    return 0;
}
