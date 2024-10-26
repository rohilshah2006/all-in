// inc of 10% atk speed base first pick
// inc of 5% every other to 5 max, 
//e.g lvl1 is 10% bonus atk speed, lvl 2 is 15, lvl3, 20, lvl 4 25, lvl 5 30% max atk speed
// Attack speed is an upgrade that can enhance the speed of a skill like wiper or multishot
#ifndef ATTACKSPEEDUPGRADE_H
#define ATTACKSPEEDUPGRADE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class AttackSpeedUpgrade {
public:
    AttackSpeedUpgrade();
    void upgrade();
    float getAttackSpeedMultiplier() const;
    std::string getDescription() const;
    void applyToSkills(std::vector<class Skill*>& playerSkills);

private:
    int level;
    int maxLevel;
    float baseBonus;
    float additionalBonus;
    float attackSpeedMultiplier;

    void updateMultiplier();
};

#endif

// Implementation

#include "AttackSpeedUpgrade.h"
#include "Skill.h"
#include <sstream>

AttackSpeedUpgrade::AttackSpeedUpgrade() : level(1), maxLevel(5), baseBonus(0.1f), additionalBonus(0.05f) {
    updateMultiplier();
}

void AttackSpeedUpgrade::upgrade() {
    if (level < maxLevel) {
        level++;
        updateMultiplier();
    }
}

float AttackSpeedUpgrade::getAttackSpeedMultiplier() const {
    return 1.0f + attackSpeedMultiplier;
}

std::string AttackSpeedUpgrade::getDescription() const {
    std::ostringstream desc;
    desc << "Attack Speed Upgrade Level " << level << ": +" << (attackSpeedMultiplier * 100) << "% attack speed for all skills";
    return desc.str();
}

void AttackSpeedUpgrade::applyToSkills(std::vector<Skill*>& playerSkills) {
    for (auto& skill : playerSkills) {
        skill->setAttackSpeedMultiplier(getAttackSpeedMultiplier()); // Assuming each skill has a setAttackSpeedMultiplier method
    }
}

void AttackSpeedUpgrade::updateMultiplier() {
    attackSpeedMultiplier = baseBonus + (level - 1) * additionalBonus;
}
/*Skill-Wide Application:

applyToSkills() iterates over the player’s equipped skills and applies the attackSpeedMultiplier to each skill. This method requires each skill to have a setAttackSpeedMultiplier method to adjust its speed dynamically.
Attack Speed Multiplier:

getAttackSpeedMultiplier() returns the total multiplier (e.g., 1.3 at level 5), boosting the rate of all skills equipped.
Player Skills Compatibility:
*/