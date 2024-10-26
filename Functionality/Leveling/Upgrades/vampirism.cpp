//each time enemy is hit, will heal 0.1% of total dmg dealt with that hit.
// max upgrade, each hit will heal 1% of total dmg dealt by hit, e.g. an attack does 100dmg -> your total heal is 1hp
//keep in mind, player will have hundreds of attacks per second, like 500dps is like 5+ hp per sec
//cannot benefit off ignite and only heals half of it's original from elec field
#ifndef VAMPIRISMUPGRADE_H
#define VAMPIRISMUPGRADE_H

#include <SFML/Graphics.hpp>
#include <string>

class VampirismUpgrade {
public:
    VampirismUpgrade();
    void upgrade();
    float calculateHealing(float damageDealt, const std::string& skillName) const;
    std::string getDescription() const;

private:
    int level;
    int maxLevel;
    float baseHealingPercent;
    float healingPercent;

    void updateHealingPercent();
};

#endif

// Implementation

#include "VampirismUpgrade.h"
#include <sstream>

VampirismUpgrade::VampirismUpgrade() : level(1), maxLevel(5), baseHealingPercent(0.001f) {
    updateHealingPercent();
}

void VampirismUpgrade::upgrade() {
    if (level < maxLevel) {
        level++;
        updateHealingPercent();
    }
}

float VampirismUpgrade::calculateHealing(float damageDealt, const std::string& skillName) const {
    // No healing for Ignite, half healing for ElectricField
    if (skillName == "Ignite") {
        return 0.0f;
    } else if (skillName == "ElectricField") {
        return 0.5f * healingPercent * damageDealt;
    }
    return healingPercent * damageDealt;
}

std::string VampirismUpgrade::getDescription() const {
    std::ostringstream desc;
    desc << "Vampirism Upgrade Level " << level << ": Heals " << (healingPercent * 100) << "% of damage dealt per hit";
    return desc.str();
}

void VampirismUpgrade::updateHealingPercent() {
    healingPercent = baseHealingPercent * level; // Increases healing by 0.1% per level, up to 1% at max
}

/*Healing Calculation:

Level Scaling: Healing starts at 0.1% of damage per hit at level 1, reaching 1% at max level.
Skill-Specific Effects:
Ignite: No healing is applied for damage from the "Ignite" skill.
ElectricField: Healing is halved for damage dealt by "ElectricField."
Description:

getDescription() provides the current level’s healing percentage for easy reference.
Usage:

calculateHealing() returns the amount to heal based on damageDealt and the skillName, allowing integration with other combat systems.*/