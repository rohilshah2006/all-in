//
// Created by Rohil Shah on 10/25/24.
//

#include <SFML/Graphics.hpp>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Move Triangle with WASD");

    // Load the texture
    sf::Texture texture;
    if (!texture.loadFromFile("triangle.png")) {
        return -1; // Error loading the image
    }

    // Create a sprite and set its texture
    sf::Sprite triangle;
    triangle.setTexture(texture);

    // Set initial position
    triangle.setPosition(400, 300);

    // Movement speed
    float speed = 200.0f; // pixels per second

    // Clock for timing
    sf::Clock clock;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the time elapsed since the last frame
        float deltaTime = clock.restart().asSeconds();

        // Move the triangle using WASD
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            triangle.move(0, -speed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            triangle.move(-speed * deltaTime, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            triangle.move(0, speed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            triangle.move(speed * deltaTime, 0);
        }

        // Clear the window
        window.clear();

        // Draw the triangle
        window.draw(triangle);

        // Display the window contents
        window.display();
    }

    return 0;
}
