#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

// Utility function for collision detection
bool checkCollision(const sf::CircleShape& circle, const sf::ConvexShape& triangle) {
    return circle.getGlobalBounds().intersects(triangle.getGlobalBounds());
}

// HealthSystem class
class HealthSystem {
protected:
    int maxHealth;
    int currentHealth;
    int regenRate;

public:
    HealthSystem(int maxHealth, int regenRate)
        : maxHealth(maxHealth), currentHealth(maxHealth), regenRate(regenRate) {}

    virtual ~HealthSystem() = default;

    void takeDamage(int amount) {
        currentHealth -= amount;
        if (currentHealth < 0) currentHealth = 0;
    }

    void regenerateHealth() {
        currentHealth += regenRate;
        if (currentHealth > maxHealth) currentHealth = maxHealth;
    }

    int getCurrentHealth() const { return currentHealth; }
    bool isAlive() const { return currentHealth > 0; }
};

// Player class with triangular hitbox
class Player : public HealthSystem {
private:
    sf::Sprite sprite;
    sf::ConvexShape hitbox; // Triangular hitbox
    int waveNumber;

public:
    Player(int maxHealth, int regenRate, const sf::Texture& texture)
        : HealthSystem(maxHealth, regenRate), waveNumber(1) {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

        // Define a triangle shape as the player's hitbox
        hitbox.setPointCount(3);
        hitbox.setPoint(0, sf::Vector2f(0, -20));   // Top point of the triangle
        hitbox.setPoint(1, sf::Vector2f(-20, 20));  // Bottom left point
        hitbox.setPoint(2, sf::Vector2f(20, 20));   // Bottom right point
        hitbox.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red for visualization
    }

    void updateWaveHealth() {
        if (waveNumber % 5 == 0) {
            maxHealth += 10;
            currentHealth = maxHealth;
        }
        waveNumber++;
    }

    void update(float deltaTime) {
        regenerateHealth();
    }

    void setPosition(const sf::Vector2f& position) {
        sprite.setPosition(position);
        hitbox.setPosition(position); // Update hitbox position with player
    }

    sf::Sprite& getSprite() { return sprite; }
    sf::ConvexShape& getHitbox() { return hitbox; }
};

// Enemy class with circular hitbox
class Enemy : public HealthSystem {
private:
    sf::Sprite sprite;
    sf::CircleShape hitbox; // Circular hitbox

public:
    Enemy(int maxHealth, int regenRate, const sf::Texture& texture, float radius)
        : HealthSystem(maxHealth, regenRate), hitbox(radius) {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

        // Define the circular hitbox with the given radius
        hitbox.setFillColor(sf::Color(0, 0, 255, 100)); // Semi-transparent blue for visualization
        hitbox.setOrigin(radius, radius); // Center the hitbox
    }

    void takeDamage(int amount) {
        HealthSystem::takeDamage(amount);
    }

    void setPosition(const sf::Vector2f& position) {
        sprite.setPosition(position);
        hitbox.setPosition(position); // Update hitbox position with enemy
    }

    sf::Sprite& getSprite() { return sprite; }
    sf::CircleShape& getHitbox() { return hitbox; }
};


/*Explanation of Changes
Circular Hitbox for Enemy:

The Enemy class now has an sf::CircleShape hitbox.
The radius of the circular hitbox is set in the constructor, with its origin centered.
Triangular Hitbox for Player:

The Player class now has an sf::ConvexShape hitbox with three points, forming a triangle.
The triangle is centered around the player’s position and set to follow the player's position updates.
Collision Detection:

The checkCollision function checks for collision between the enemy’s circular hitbox and the player’s triangular hitbox using their bounding boxes.
If a collision is detected, the player takes damage.
Hitbox Visualization:

Each hitbox has a semi-transparent color for visualization during development.

*/