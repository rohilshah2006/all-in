//increased regeneration, base regen is 1% per second, max regen per second is 10% 
#ifndef REGENERATIONUPGRADE_H
#define REGENERATIONUPGRADE_H

#include <SFML/Graphics.hpp>
#include <string>

class RegenerationUpgrade {
public:
    RegenerationUpgrade();
    void upgrade();
    float getRegenerationRate() const;
    std::string getDescription() const;

private:
    int level;
    int maxLevel;
    float baseRegenRate;
    float incrementRate;
    float currentRegenRate;

    void updateRegenRate();
};

#endif

// Implementation

#include "RegenerationUpgrade.h"
#include <sstream>

RegenerationUpgrade::RegenerationUpgrade() : level(1), maxLevel(5), baseRegenRate(0.01f), incrementRate(0.02f) {
    updateRegenRate();
}

void RegenerationUpgrade::upgrade() {
    if (level < maxLevel) {
        level++;
        updateRegenRate();
    }
}

float RegenerationUpgrade::getRegenerationRate() const {
    return currentRegenRate;
}

std::string RegenerationUpgrade::getDescription() const {
    std::ostringstream desc;
    desc << "Regeneration Upgrade Level " << level << ": " << (currentRegenRate * 100) << "% health regen per second";
    return desc.str();
}

void RegenerationUpgrade::updateRegenRate() {
    currentRegenRate = baseRegenRate + (level - 1) * incrementRate;
    if (currentRegenRate > 0.10f) { // Cap regeneration at 10%
        currentRegenRate = 0.10f;
    }
}
/*Regeneration Scaling:

Level 1: Starts at 1% health regeneration per second.
Levels 2-4: Increases by 2% per level, reaching up to 10% at max level.
Health Regen Rate Calculation:

getRegenerationRate() provides the current rate for application in the player’s health regeneration logic.
Description:

getDescription() returns a formatted string of the level and current regeneration rate for UI display.
*/