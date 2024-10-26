/*Summary
Bomb: Aims at the nearest enemy upon creation and during detonation.
Prism: Aims at the nearest enemy upon being shot.
Turret: Continuously aims at the nearest enemy while active.*/
#ifndef AUTOAIM_H
#define AUTOAIM_H

#include <SFML/Graphics.hpp>
#include <vector>

// Bomb class
class Bomb {
public:
    Bomb(const sf::Vector2f& position, const std::vector<class Enemy*>& enemies);
    void detonate();

private:
    sf::Sprite bombSprite;
    sf::Texture bombTexture; // Replace with actual bomb texture path
    sf::Vector2f aimDirection;

    void aimAtNearestEnemy(const std::vector<class Enemy*>& enemies);
};

// Prism class
class Prism {
public:
    Prism(const sf::Vector2f& position, const std::vector<class Enemy*>& enemies);
    void shoot();

private:
    sf::Sprite prismSprite;
    sf::Texture prismTexture; // Replace with actual prism texture path
    sf::Vector2f aimDirection;

    void aimAtNearestEnemy(const std::vector<class Enemy*>& enemies);
};

// Turret class
class Turret {
public:
    Turret();
    void upgrade();
    void spawn(const sf::Vector2f& position);
    void update(float deltaTime, const std::vector<class Enemy*>& enemies);
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite turretSprite;
    float activeDuration;
    float cooldown;
    bool isActive;

    void aimAtNearestEnemy(const std::vector<Enemy*>& enemies);
};

#endif

#include "AutoAim.h"
#include "Enemy.h" // Assuming Enemy class exists
#include <limits>

// Bomb implementation
Bomb::Bomb(const sf::Vector2f& position, const std::vector<Enemy*>& enemies) {
    bombTexture.loadFromFile("bomb.png"); // Replace with actual texture path
    bombSprite.setTexture(bombTexture);
    bombSprite.setPosition(position);
    aimAtNearestEnemy(enemies); // Aim at the nearest enemy upon creation
}

void Bomb::detonate() {
    // Logic for detonation effects
    // Example: deal damage to enemies in the area
}

void Bomb::aimAtNearestEnemy(const std::vector<Enemy*>& enemies) {
    float closestDistance = std::numeric_limits<float>::max();
    sf::Vector2f nearestPosition(0, 0);

    for (const auto& enemy : enemies) {
        float distance = std::hypot(enemy->getPosition().x - bombSprite.getPosition().x,
                                    enemy->getPosition().y - bombSprite.getPosition().y);
        if (distance < closestDistance) {
            closestDistance = distance;
            nearestPosition = enemy->getPosition();
        }
    }

    if (closestDistance < std::numeric_limits<float>::max()) {
        aimDirection = nearestPosition - bombSprite.getPosition();
        aimDirection /= std::hypot(aimDirection.x, aimDirection.y); // Normalize direction
    }
}

// Prism implementation
Prism::Prism(const sf::Vector2f& position, const std::vector<Enemy*>& enemies) {
    prismTexture.loadFromFile("prism.png"); // Replace with actual texture path
    prismSprite.setTexture(prismTexture);
    prismSprite.setPosition(position);
    aimAtNearestEnemy(enemies); // Aim at the nearest enemy upon creation
}

void Prism::shoot() {
    // Logic to shoot the prism in the aimed direction
}

void Prism::aimAtNearestEnemy(const std::vector<Enemy*>& enemies) {
    float closestDistance = std::numeric_limits<float>::max();
    sf::Vector2f nearestPosition(0, 0);

    for (const auto& enemy : enemies) {
        float distance = std::hypot(enemy->getPosition().x - prismSprite.getPosition().x,
                                    enemy->getPosition().y - prismSprite.getPosition().y);
        if (distance < closestDistance) {
            closestDistance = distance;
            nearestPosition = enemy->getPosition();
        }
    }

    if (closestDistance < std::numeric_limits<float>::max()) {
        aimDirection = nearestPosition - prismSprite.getPosition();
        aimDirection /= std::hypot(aimDirection.x, aimDirection.y); // Normalize direction
    }
}

// Turret implementation
Turret::Turret() : activeDuration(10.0f), cooldown(20.0f), isActive(false) {
    // Load turret texture and initialize sprite
}

void Turret::spawn(const sf::Vector2f& position) {
    turretSprite.setPosition(position);
    isActive = true;
}

void Turret::update(float deltaTime, const std::vector<Enemy*>& enemies) {
    if (isActive) {
        aimAtNearestEnemy(enemies); // Adjust aim toward the nearest enemy
        // Additional update logic for turret shooting
    }
}

void Turret::draw(sf::RenderWindow& window) {
    if (isActive) {
        window.draw(turretSprite);
    }
}

void Turret::aimAtNearestEnemy(const std::vector<Enemy*>& enemies) {
    float closestDistance = std::numeric_limits<float>::max();
    sf::Vector2f nearestPosition(0, 0);

    for (const auto& enemy : enemies) {
        float distance = std::hypot(enemy->getPosition().x - turretSprite.getPosition().x,
                                    enemy->getPosition().y - turretSprite.getPosition().y);
        if (distance < closestDistance) {
            closestDistance = distance;
            nearestPosition = enemy->getPosition();
        }
    }

    if (closestDistance < std::numeric_limits<float>::max()) {
        // Rotate turret towards the nearest enemy
        sf::Vector2f direction = nearestPosition - turretSprite.getPosition();
        float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159; // Convert to degrees
        turretSprite.setRotation(angle);
    }
}
