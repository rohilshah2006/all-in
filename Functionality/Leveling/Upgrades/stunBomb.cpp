//upon being hit, will stun enemies nearby for 2 seconds, and increases firerate by 50% lvl 1, and the cooldown is 100 seconds
//lvl 5 stun is 7.5 seconds, firerate increase by 100%, cooldown of 30 seconds
#ifndef STUNBOMBUPGRADE_H
#define STUNBOMBUPGRADE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class StunBombUpgrade {
public:
    StunBombUpgrade();
    void upgrade();
    void activateStun(std::vector<class Enemy*>& enemies, const sf::Vector2f& playerPosition);
    void updateCooldown(float deltaTime);
    bool isReady() const;
    float getFireRateMultiplier() const;
    std::string getDescription() const;

private:
    int level;
    int maxLevel;
    float baseStunDuration;
    float stunIncrement;
    float currentStunDuration;
    float baseFireRateBonus;
    float currentFireRateMultiplier;
    float baseCooldown;
    float cooldownReduction;
    float currentCooldown;
    float cooldownRemaining;

    void updateProperties();
};

#endif

// Implementation

#include "StunBombUpgrade.h"
#include "Enemy.h"
#include <sstream>

StunBombUpgrade::StunBombUpgrade()
    : level(1), maxLevel(5), baseStunDuration(2.0f), stunIncrement(1.375f), baseFireRateBonus(0.5f),
      baseCooldown(100.0f), cooldownReduction(17.5f), cooldownRemaining(0.0f) {
    updateProperties();
}

void StunBombUpgrade::upgrade() {
    if (level < maxLevel) {
        level++;
        updateProperties();
    }
}

void StunBombUpgrade::activateStun(std::vector<Enemy*>& enemies, const sf::Vector2f& playerPosition) {
    if (isReady()) {
        // Stun all enemies within a certain radius (assuming a stun radius of 150 units)
        for (auto& enemy : enemies) {
            float distance = std::hypot(enemy->getPosition().x - playerPosition.x, enemy->getPosition().y - playerPosition.y);
            if (distance <= 150.0f) {
                enemy->stun(currentStunDuration); // Assumes Enemy has a stun method
            }
        }
        cooldownRemaining = currentCooldown; // Reset cooldown after activation
    }
}

void StunBombUpgrade::updateCooldown(float deltaTime) {
    if (cooldownRemaining > 0) {
        cooldownRemaining -= deltaTime;
    }
}

bool StunBombUpgrade::isReady() const {
    return cooldownRemaining <= 0;
}

float StunBombUpgrade::getFireRateMultiplier() const {
    return 1.0f + currentFireRateMultiplier;
}

std::string StunBombUpgrade::getDescription() const {
    std::ostringstream desc;
    desc << "StunBomb Upgrade Level " << level << ": Stuns enemies for " << currentStunDuration
         << " seconds, +" << (currentFireRateMultiplier * 100) << "% fire rate, cooldown " << currentCooldown << " seconds";
    return desc.str();
}

void StunBombUpgrade::updateProperties() {
    currentStunDuration = baseStunDuration + (level - 1) * stunIncrement;
    currentFireRateMultiplier = baseFireRateBonus * level; // Increases fire rate bonus by 50% each level
    currentCooldown = baseCooldown - (level - 1) * cooldownReduction;
}
/*Level-Based Scaling:

Level 1: Stun duration of 2 seconds, fire rate boost of 50%, 100-second cooldown.
Level 5: Stun duration of 7.5 seconds, fire rate boost of 100%, 30-second cooldown.
Stun Activation:

activateStun() stuns all enemies within a certain radius (e.g., 150 units) when the player is hit. This requires each Enemy to have a stun() method.
Cooldown Management:

updateCooldown() decreases cooldown, and isReady() checks if the ability is available.
Description:

getDescription() provides a formatted description for display, showing the current level’s stun duration, fire rate boost, and cooldown.*/