//
// Created by Rohil Shah on 10/25/24.
//

#include <SFML/Graphics.hpp>

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "WASD Movement");

    // Load the player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("triangle.png")) {
        return -1;
    }

    // Create the player sprite
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(400, 300); // Starting position

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movement speed
        float moveSpeed = 5.0f;

        // Handle WASD input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            playerSprite.move(0, -moveSpeed); // Move up
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerSprite.move(-moveSpeed, 0); // Move left
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            playerSprite.move(0, moveSpeed); // Move down
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerSprite.move(moveSpeed, 0); // Move right
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw the player
        window.draw(playerSprite);

        // Display the window contents
        window.display();
    }

    return 0;
}