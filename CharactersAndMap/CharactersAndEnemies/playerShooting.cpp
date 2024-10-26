/*Automatic Shooting: The player automatically shoots in the direction of the nearest enemy.
Fire Rate Scaling: The firing rate decreases with each player level, allowing faster shooting.
Damage Scaling: Damage increases based on the player's level.
Direction Calculation: Uses getNearestEnemyDirection() to ensure accurate targeting of enemies.*/
#ifndef AUTOMATICSHOOTING_H
#define AUTOMATICSHOOTING_H

#include <SFML/Graphics.hpp>
#include <vector>

class AutomaticShooting {
public:
    AutomaticShooting();
    void update(float deltaTime, const std::vector<class Enemy*>& enemies);
    void shoot();

private:
    float baseDamage;
    float fireRate; // Base fire rate in seconds
    float timeSinceLastShot;
    float playerLevel; // Current player level for scaling fire rate and damage
    sf::Sprite bulletSprite; // Bullet sprite
    sf::Texture bulletTexture; // Texture for the bullet

    void createBullet(const sf::Vector2f& direction);
    sf::Vector2f getNearestEnemyDirection(const std::vector<class Enemy*>& enemies);
};

#endif

// Implementation

#include "AutomaticShooting.h"
#include "Enemy.h" // Assuming Enemy class exists
#include <cmath>
#include <limits>

AutomaticShooting::AutomaticShooting() : baseDamage(10.0f), fireRate(1.0f), timeSinceLastShot(0.0f), playerLevel(1) {
    bulletTexture.loadFromFile("bullet.png"); // Replace with actual bullet texture path
    bulletSprite.setTexture(bulletTexture);
}

void AutomaticShooting::update(float deltaTime, const std::vector<Enemy*>& enemies) {
    timeSinceLastShot += deltaTime;

    // Scale fire rate and damage by player level
    fireRate = 1.0f / std::pow(1.05f, playerLevel - 1); // Example scaling for faster shooting

    // Check if it's time to shoot
    if (timeSinceLastShot >= fireRate) {
        sf::Vector2f shootDirection = getNearestEnemyDirection(enemies);
        if (shootDirection != sf::Vector2f(0, 0)) {
            shoot();
            timeSinceLastShot = 0.0f; // Reset shot timer
        }
    }
}

void AutomaticShooting::shoot() {
    sf::Vector2f bulletDirection = getNearestEnemyDirection(enemies);
    if (bulletDirection != sf::Vector2f(0, 0)) {
        createBullet(bulletDirection);
    }
}

void AutomaticShooting::createBullet(const sf::Vector2f& direction) {
    // Implement bullet creation and movement logic here
    float damage = baseDamage * (1.0f + 0.05f * (playerLevel - 1)); // Increment damage per level
    // Logic to move the bullet in the direction specified
    // (e.g., update bullet position based on direction)
}

sf::Vector2f AutomaticShooting::getNearestEnemyDirection(const std::vector<Enemy*>& enemies) {
    float closestDistance = std::numeric_limits<float>::max();
    sf::Vector2f nearestDirection(0, 0);

    for (const auto& enemy : enemies) {
        float distance = std::hypot(enemy->getPosition().x - bulletSprite.getPosition().x, 
                                    enemy->getPosition().y - bulletSprite.getPosition().y);
        if (distance < closestDistance) {
            closestDistance = distance;
            nearestDirection = enemy->getPosition() - bulletSprite.getPosition();
            nearestDirection /= std::hypot(nearestDirection.x, nearestDirection.y); // Normalize direction
        }
    }
    return nearestDirection; // Return the direction to the nearest enemy
}
