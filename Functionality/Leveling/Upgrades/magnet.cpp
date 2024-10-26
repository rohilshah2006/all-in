//pulls nearby exp in
//max lvl 5 uprade will pull everything in the FOV of the player
#ifndef MAGNETUPGRADE_H
#define MAGNETUPGRADE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MagnetUpgrade {
public:
    MagnetUpgrade();
    void upgrade();
    void applyMagnetEffect(std::vector<class ExpItem*>& expItems, const sf::Vector2f& playerPosition, const sf::FloatRect& playerFOV);
    std::string getDescription() const;

private:
    int level;
    int maxLevel;
    float baseRadius;
    float radiusIncrease;
    float currentRadius;

    void updateRadius();
};

#endif

// Implementation

#include "MagnetUpgrade.h"
#include "ExpItem.h"
#include <cmath>
#include <sstream>

MagnetUpgrade::MagnetUpgrade() : level(1), maxLevel(5), baseRadius(100.0f), radiusIncrease(50.0f) {
    updateRadius();
}

void MagnetUpgrade::upgrade() {
    if (level < maxLevel) {
        level++;
        updateRadius();
    }
}

void MagnetUpgrade::applyMagnetEffect(std::vector<ExpItem*>& expItems, const sf::Vector2f& playerPosition, const sf::FloatRect& playerFOV) {
    for (auto& exp : expItems) {
        float distance = std::hypot(exp->getPosition().x - playerPosition.x, exp->getPosition().y - playerPosition.y);
        
        if ((level < maxLevel && distance <= currentRadius) || 
            (level == maxLevel && playerFOV.contains(exp->getPosition()))) {
            exp->moveTo(playerPosition); // Pulls the EXP item to the player (assuming ExpItem has moveTo)
        }
    }
}

std::string MagnetUpgrade::getDescription() const {
    std::ostringstream desc;
    desc << "Magnet Upgrade Level " << level << ": Collection radius " << currentRadius << " units";
    if (level == maxLevel) {
        desc << " (entire FOV)";
    }
    return desc.str();
}

void MagnetUpgrade::updateRadius() {
    currentRadius = baseRadius + (level - 1) * radiusIncrease; // Increase radius with each level
}
/*Level-Based Collection Radius:

Level 1: Starts with a base radius of 100 units.
Levels 2-4: Increase radius by 50 units per level.
Level 5: Collects all EXP items within the player’s FOV.
Magnet Effect Application:

applyMagnetEffect() iterates over all EXP items, pulling in those within the collection radius or FOV (at max level). This assumes each ExpItem has a moveTo() method to pull it to the player.
Description:

getDescription() returns a summary with the current level and radius, marking max level with the FOV-wide effect.*/