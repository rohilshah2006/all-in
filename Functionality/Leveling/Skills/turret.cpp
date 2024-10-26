//a turret that will spawn below the player, despawns after 10 seconds, cooldown of 20 sec
//lvl 5 max upgrde possibily, change turret designs a bit, and change, and they will last like 5 secs longer
#ifndef TURRET_H
#define TURRET_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Turret {
public:
    Turret();
    void upgrade();
    void spawn(const sf::Vector2f& position);
    void update(float deltaTime, std::vector<class Enemy*>& enemies);
    void draw(sf::RenderWindow& window);
    bool isReadyToSpawn() const;

private:
    int level;
    int maxLevel;
    float baseDamage;
    float activeDuration;
    float cooldown;
    float cooldownRemaining;
    float activeTimeRemaining;
    bool isActive;
    sf::Texture regularTexture;
    sf::Texture maxLevelTexture;
    sf::Sprite turretSprite;

    void updateSkillProperties();
    void resetCooldown();
};

#endif

// Implementation

#include "Turret.h"
#include "Enemy.h"

Turret::Turret() : level(1), maxLevel(5), baseDamage(10.0f), activeDuration(10.0f), cooldown(20.0f), cooldownRemaining(0.0f), activeTimeRemaining(0.0f), isActive(false) {
    regularTexture.loadFromFile("turret_regular.png"); // Path to regular texture
    maxLevelTexture.loadFromFile("turret_max.png");    // Path to max-level texture
    turretSprite.setTexture(regularTexture);
    turretSprite.setOrigin(regularTexture.getSize().x / 2, regularTexture.getSize().y / 2);

    updateSkillProperties();
}

void Turret::upgrade() {
    if (level < maxLevel) {
        level++;
        updateSkillProperties();
    }
}

void Turret::spawn(const sf::Vector2f& position) {
    if (cooldownRemaining <= 0 && !isActive) {
        turretSprite.setPosition(position);
        activeTimeRemaining = activeDuration;
        isActive = true;
        resetCooldown();
    }
}

void Turret::update(float deltaTime, std::vector<Enemy*>& enemies) {
    if (isActive) {
        activeTimeRemaining -= deltaTime;
        if (activeTimeRemaining <= 0) {
            isActive = false;
        } else {
            for (auto& enemy : enemies) {
                if (std::hypot(enemy->getPosition().x - turretSprite.getPosition().x, enemy->getPosition().y - turretSprite.getPosition().y) < 100.0f) {
                    enemy->takeDamage(baseDamage); // Apply base damage based on level
                }
            }
        }
    } else {
        cooldownRemaining -= deltaTime;
    }
}

void Turret::draw(sf::RenderWindow& window) {
    if (isActive) {
        window.draw(turretSprite);
    }
}

bool Turret::isReadyToSpawn() const {
    return cooldownRemaining <= 0 && !isActive;
}

void Turret::updateSkillProperties() {
    switch (level) {
        case 1:
            baseDamage = 10.0f;
            activeDuration = 10.0f;
            cooldown = 20.0f;
            break;
        case 2:
            baseDamage = 12.0f;
            cooldown = 18.0f;
            break;
        case 3:
            baseDamage = 15.0f;
            cooldown = 16.0f;
            break;
        case 4:
            baseDamage = 18.0f;
            cooldown = 14.0f;
            break;
        case 5:
            baseDamage = 25.0f;
            activeDuration = 15.0f; // Max level duration
            cooldown = 12.0f;
            turretSprite.setTexture(maxLevelTexture); // Switch to max-level texture
            break;
    }
}

void Turret::resetCooldown() {
    cooldownRemaining = cooldown;
}
/*Skill Level Scaling:

Level 1: Base damage of 10, cooldown of 20 seconds.
Level 2: Base damage of 12, cooldown reduced to 18 seconds.
Level 3: Base damage of 15, cooldown reduced to 16 seconds.
Level 4: Base damage of 18, cooldown reduced to 14 seconds.
Level 5: Base damage of 25, extended duration (15 seconds), cooldown of 12 seconds, and unique design.
Upgrade Adjustments:

updateSkillProperties() sets specific base damage, cooldown, and duration values according to the current level.
*/