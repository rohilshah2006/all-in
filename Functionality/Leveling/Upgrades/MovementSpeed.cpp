//move faster by 5% each time picked, you know the max level
#ifndef MOVEMENTSPEEDUPGRADE_H
#define MOVEMENTSPEEDUPGRADE_H

#include <SFML/Graphics.hpp>
#include <string>

class MovementSpeedUpgrade {
public:
    MovementSpeedUpgrade();
    void upgrade();
    float getSpeedMultiplier() const;
    std::string getDescription() const;

private:
    int level;
    int maxLevel;
    float baseIncrease;
    float speedMultiplier;

    void updateMultiplier();
};

#endif

// Implementation

#include "MovementSpeedUpgrade.h"
#include <sstream>

MovementSpeedUpgrade::MovementSpeedUpgrade() : level(1), maxLevel(5), baseIncrease(0.05f) {
    updateMultiplier();
}

void MovementSpeedUpgrade::upgrade() {
    if (level < maxLevel) {
        level++;
        updateMultiplier();
    }
}

float MovementSpeedUpgrade::getSpeedMultiplier() const {
    return 1.0f + speedMultiplier;
}

std::string MovementSpeedUpgrade::getDescription() const {
    std::ostringstream desc;
    desc << "Movement Speed Upgrade Level " << level << ": +" << (speedMultiplier * 100) << "% movement speed";
    return desc.str();
}

void MovementSpeedUpgrade::updateMultiplier() {
    speedMultiplier = level * baseIncrease; // Increases by 5% per level
}
/*Speed Multiplier:

Level 1: +5% movement speed.
Level 5: +25% movement speed.
getSpeedMultiplier() returns the multiplier to adjust the player’s speed accordingly.
Description:

getDescription() updates to display the current movement speed bonus.*/