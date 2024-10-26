//a triangle prism that will bounce off the FOV walls of the player, will be shot in a random 360 direction initially
//will break after prism HP is 0, inf pierce already
// lets say base prisomHP is like 100hp, with a base dmg of 20, if it hits 5 enemies it will despawn
//lvl upgrade may, be 5 prisms max on the board, with 1.5x the orig health
/*Skill Levels:

Level 1: Base HP of 100, 5 max hits before despawning.
Max Level: 5 prisms can be on the field, with 1.5x the base HP and up to 8 hits.
Bouncing Logic:

bounceOffWalls() reverses the prism’s direction when it hits the edges of the player’s FOV, creating a bouncing effect.
Randomized Initial Direction:

randomizeDirection() sets a random initial direction for the prism.
Enemy Collision:

checkCollision() deals damage to enemies and counts hits, deactivating the prism when maxHits is reached.
Active State Check:

isActive() returns false when HP is 0, allowing the prism to be removed from the field.*/

#ifndef PRISM_H
#define PRISM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Prism {
public:
    Prism();
    void upgrade();
    void initialize(const sf::Vector2f& startPosition);
    void updatePosition(const sf::FloatRect& playerFOV, float deltaTime);
    void checkCollision(std::vector<class Enemy*>& enemies);
    void draw(sf::RenderWindow& window);
    bool isActive() const;

private:
    int level;
    int maxLevel;
    int prismHP;
    int maxHits;
    int currentHits;
    float moveSpeed;
    float baseDamage;
    sf::Vector2f direction;
    sf::ConvexShape prismShape;

    void updateSkillProperties();
    void bounceOffWalls(const sf::FloatRect& playerFOV);
    void randomizeDirection();
};

#endif

// Implementation

Prism::Prism()
    : level(1), maxLevel(5), prismHP(100), maxHits(5), moveSpeed(150.0f), baseDamage(20.0f) {
    // Initialize the prism shape as a triangle
    prismShape.setPointCount(3);
    prismShape.setPoint(0, sf::Vector2f(0, -15));    // Top
    prismShape.setPoint(1, sf::Vector2f(-10, 15));   // Bottom-left
    prismShape.setPoint(2, sf::Vector2f(10, 15));    // Bottom-right
    prismShape.setFillColor(sf::Color::Cyan);
    prismShape.setOrigin(0, 0);

    randomizeDirection(); // Set initial random direction
    updateSkillProperties();
}

void Prism::upgrade() {
    if (level < maxLevel) {
        level++;
        updateSkillProperties();
    }
}

void Prism::initialize(const sf::Vector2f& startPosition) {
    prismShape.setPosition(startPosition);
    currentHits = 0;
    prismHP = 100 * std::pow(1.5f, level - 1);
}

void Prism::updatePosition(const sf::FloatRect& playerFOV, float deltaTime) {
    bounceOffWalls(playerFOV); // Check for wall collisions
    prismShape.move(direction * moveSpeed * deltaTime); // Move in the current direction
}

void Prism::checkCollision(std::vector<Enemy*>& enemies) {
    for (auto& enemy : enemies) {
        if (prismShape.getGlobalBounds().intersects(enemy->getBounds())) {
            enemy->takeDamage(baseDamage);
            currentHits++;
            if (currentHits >= maxHits) {
                prismHP = 0; // Deactivate after max hits
            }
        }
    }
}

void Prism::draw(sf::RenderWindow& window) {
    if (isActive()) {
        window.draw(prismShape);
    }
}

bool Prism::isActive() const {
    return prismHP > 0;
}

void Prism::updateSkillProperties() {
    maxHits = (level == maxLevel) ? 8 : 5;
    prismHP = static_cast<int>(100 * std::pow(1.5, level - 1));
    prismShape.setScale(1.0f + 0.1f * (level - 1), 1.0f + 0.1f * (level - 1)); // Slightly larger with each level
}

void Prism::bounceOffWalls(const sf::FloatRect& playerFOV) {
    if (prismShape.getPosition().x <= playerFOV.left || 
        prismShape.getPosition().x >= playerFOV.left + playerFOV.width) {
        direction.x = -direction.x; // Reverse horizontal direction
    }
    if (prismShape.getPosition().y <= playerFOV.top || 
        prismShape.getPosition().y >= playerFOV.top + playerFOV.height) {
        direction.y = -direction.y; // Reverse vertical direction
    }
}

void Prism::randomizeDirection() {
    float angle = static_cast<float>(std::rand() % 360) * (3.14159f / 180.0f); // Random angle in radians
    direction = {std::cos(angle), std::sin(angle)};
}
