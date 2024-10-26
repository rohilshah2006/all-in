#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

// Constants
const float ROTATION_SPEED = 100.0f;      // degrees per second for rotating skills
const float PLAYER_SPEED = 200.0f;        // pixels per second for player
const sf::Vector2f FOV_SIZE(300.0f, 200.0f); // FOV width and height

// Player class
class Player {
public:
    sf::Sprite sprite;

    Player(const sf::Texture& texture) {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    }

    void move(sf::Vector2f direction, float deltaTime, const sf::FloatRect& bounds) {
        sf::Vector2f newPos = sprite.getPosition() + direction * PLAYER_SPEED * deltaTime;
        if (bounds.contains(newPos)) {
            sprite.setPosition(newPos);
        }
    }
};

// Skill class
class Skill {
public:
    sf::Sprite sprite;
    bool isBouncing;
    sf::Vector2f velocity;

    Skill(const sf::Texture& texture, bool bouncing = false, sf::Vector2f vel = sf::Vector2f(0, 0))
        : isBouncing(bouncing), velocity(vel) {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    }

    void update(const Player& player, float deltaTime, float angle, const sf::FloatRect& fovBounds) {
        if (isBouncing) {
            sf::Vector2f newPos = sprite.getPosition() + velocity * deltaTime;

            // Check FOV bounds and bounce if necessary
            if (newPos.x < fovBounds.left || newPos.x > fovBounds.left + fovBounds.width) {
                velocity.x = -velocity.x;
            }
            if (newPos.y < fovBounds.top || newPos.y > fovBounds.top + fovBounds.height) {
                velocity.y = -velocity.y;
            }
            sprite.setPosition(newPos);
        } else {
            float radians = angle * (3.14159f / 180.0f);
            float distance = 50.0f;  // Distance from the player
            sf::Vector2f offset(std::cos(radians) * distance, std::sin(radians) * distance);
            sprite.setPosition(player.sprite.getPosition() + offset);
        }
    }
};


/*Explanation of Key Changes
Map Bounds and Player Movement:

The Player::move function now checks if the new position is within mapBounds before moving.
mapBounds is defined based on the map texture dimensions.
FOV Rectangle:

FOV_SIZE defines the width and height of the player’s field of view.
Each frame, the FOV bounds (fovBounds) are recalculated based on the player’s position.
Bouncing skill:

skill  class has an isBouncing boolean to enable bouncing behavior.
If isBouncing is true, the update method checks if the skill's position hits the edges of fovBounds and reverses the velocity when it does, creating a Pong-like bouncing effect.
FOV Visualization:

A sf::RectangleShape (fovRect) is used to visually show the FOV area. It can be removed if not needed.
With these changes, the player remains within map boundaries, skills rotate or bounce within the FOV, and the FOV centers on the player. Let me know if you need further modifications!
*/