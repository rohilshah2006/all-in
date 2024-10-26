//will start doing tick damage upon every first attack on enemy, they will take a very 
//small minimal dmg per second, lvl 5 is decent damage, vamp cannot benefit off this
//design can actually be a little fire triangle ontop of player

/*Level-Based Scaling: Ignite starts with minimal tick damage and scales up with each level. At level 5, it applies tick damage more frequently and with greater damage.
Fire Triangle Indicator: A small orange-red triangle is displayed above the player, representing the Ignite skill’s status.
Tick Damage Mechanism: applyTickDamage applies damage over time (DPS) upon the first attack on each enemy, resetting with each tick interval.
This implementation makes it easy to extend tick damage to other skills by calling applyTickDamage when necessary. Let me know if further customization is needed!
*/

#ifndef IGNITE_H
#define IGNITE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Ignite {
public:
    Ignite();
    void upgrade();
    void applyTickDamage(std::vector<class Enemy*>& enemies, float deltaTime);
    void draw(sf::RenderWindow& window, const sf::Vector2f& playerPosition);

private:
    int level;
    int maxLevel;
    float tickDamage;
    float tickInterval;
    float tickCooldown;
    sf::ConvexShape fireTriangle;
    sf::Texture regularTexture;
    sf::Texture finalTexture;

    void updateSkillProperties();
    void updateTexture();
};

#endif

#include "Ignite.h"
#include "Enemy.h" // Assuming Enemy class exists

Ignite::Ignite()
    : level(1), maxLevel(5), tickDamage(1.0f), tickInterval(1.0f), tickCooldown(0.0f) {
    // Load textures for levels 1-4 and level 5
    regularTexture.loadFromFile("ignite_regular.png");
    finalTexture.loadFromFile("ignite_final.png");

    // Initialize the fire triangle and set its initial texture for levels 1-4
    fireTriangle.setPointCount(3);
    fireTriangle.setPoint(0, sf::Vector2f(0, -15));  // Top point of the triangle
    fireTriangle.setPoint(1, sf::Vector2f(-10, 15)); // Bottom-left
    fireTriangle.setPoint(2, sf::Vector2f(10, 15));  // Bottom-right
    fireTriangle.setTexture(&regularTexture);
    fireTriangle.setFillColor(sf::Color(255, 69, 0, 150)); // Orange-red with some transparency
}

void Ignite::upgrade() {
    if (level < maxLevel) {
        level++;
        updateSkillProperties();
    }
}

void Ignite::applyTickDamage(std::vector<Enemy*>& enemies, float deltaTime) {
    tickCooldown -= deltaTime;
    if (tickCooldown <= 0.0f) {
        float damage = tickDamage;

        for (auto& enemy : enemies) {
            if (enemy->isFirstAttack()) { // Assuming isFirstAttack checks if the enemy is freshly attacked
                enemy->takeDamage(damage);
            }
        }
        tickCooldown = tickInterval; // Reset the cooldown
    }
}

void Ignite::draw(sf::RenderWindow& window, const sf::Vector2f& playerPosition) {
    fireTriangle.setPosition(playerPosition.x, playerPosition.y - 50); // Positioned above the player
    window.draw(fireTriangle);
}

void Ignite::updateSkillProperties() {
    tickDamage = 1.0f * level; // Increase tick damage per level
    if (level == maxLevel) {
        tickInterval = 0.5f; // Faster interval at max level
        tickDamage = 5.0f;   // Decent damage at max level
        updateTexture();     // Change texture at max level
    }
}

void Ignite::updateTexture() {
    fireTriangle.setTexture(&finalTexture); // Set level 5 texture
}
