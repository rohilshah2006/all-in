// inc dmg of every attack by 5% on each level
// capping out at 20% max dmg
#ifndef STRENGTHUPGRADE_H
#define STRENGTHUPGRADE_H

#include <SFML/Graphics.hpp>
#include <string>

class StrengthUpgrade {
public:
    StrengthUpgrade();
    void upgrade();
    float getDamageMultiplier() const;
    std::string getDescription() const;

private:
    int level;
    int maxLevel;
    float baseIncrease;
    float currentDamageMultiplier;

    void updateMultiplier();
};

#endif

// Implementation

#include "StrengthUpgrade.h"
#include <sstream>

StrengthUpgrade::StrengthUpgrade() : level(1), maxLevel(5), baseIncrease(0.05f) {
    updateMultiplier();
}

void StrengthUpgrade::upgrade() {
    if (level < maxLevel) {
        level++;
        updateMultiplier();
    }
}

float StrengthUpgrade::getDamageMultiplier() const {
    return 1.0f + currentDamageMultiplier;
}

std::string StrengthUpgrade::getDescription() const {
    std::ostringstream desc;
    desc << "Strength Upgrade Level " << level << ": +" << (currentDamageMultiplier * 100) << "% damage";
    return desc.str();
}

void StrengthUpgrade::updateMultiplier() {
    currentDamageMultiplier = baseIncrease * level; // Increases by 5% per level, up to 20% at max
}
/*Level-Based Damage Increase:

Level 1: +5% damage.
Level 5: +20% damage.
getDamageMultiplier() returns the cumulative multiplier for easy integration with attack calculations.
Description:

getDescription() provides a UI-friendly summary of the level and current damage bonus.*/

