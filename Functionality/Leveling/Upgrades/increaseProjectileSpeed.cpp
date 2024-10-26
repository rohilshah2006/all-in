//lvl 1 increases player projectile speed by 25 %
//lvl 5 increases speed by 100% total (including cat, making cat run quicker)
//doesn't increase firerate/atk speed but speed at which projectiles of each skill will travel.
#ifndef PROJECTILESPEEDUPGRADE_H
#define PROJECTILESPEEDUPGRADE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class ProjectileSpeedUpgrade {
public:
    ProjectileSpeedUpgrade();
    void upgrade();
    float getProjectileSpeedMultiplier() const;
    std::string getDescription() const;
    void applyToSkillsAndCat(std::vector<class Skill*>& playerSkills, class PetCat* cat);

private:
    int level;
    int maxLevel;
    float baseBonus;
    float levelBonus;
    float projectileSpeedMultiplier;

    void updateMultiplier();
};

#endif

// Implementation

#include "ProjectileSpeedUpgrade.h"
#include "Skill.h"
#include "PetCat.h"
#include <sstream>

ProjectileSpeedUpgrade::ProjectileSpeedUpgrade() : level(1), maxLevel(5), baseBonus(0.25f), levelBonus(0.15f) {
    updateMultiplier();
}

void ProjectileSpeedUpgrade::upgrade() {
    if (level < maxLevel) {
        level++;
        updateMultiplier();
    }
}

float ProjectileSpeedUpgrade::getProjectileSpeedMultiplier() const {
    return 1.0f + projectileSpeedMultiplier;
}

std::string ProjectileSpeedUpgrade::getDescription() const {
    std::ostringstream desc;
    desc << "Projectile Speed Upgrade Level " << level << ": +" << (projectileSpeedMultiplier * 100) << "% projectile speed for all skills and cat";
    return desc.str();
}

void ProjectileSpeedUpgrade::applyToSkillsAndCat(std::vector<Skill*>& playerSkills, PetCat* cat) {
    for (auto& skill : playerSkills) {
        skill->setProjectileSpeedMultiplier(getProjectileSpeedMultiplier()); // Each skill must have setProjectileSpeedMultiplier
    }
    if (cat) {
        cat->setMovementSpeedMultiplier(getProjectileSpeedMultiplier()); // Applies speed multiplier to the cat's movement
    }
}

void ProjectileSpeedUpgrade::updateMultiplier() {
    projectileSpeedMultiplier = baseBonus + (level - 1) * levelBonus; // Increments with each level
}

/*Level Breakdown:

Level 1: +25% projectile speed.
Level 2: +40% (25% + 15% increment).
Level 3: +55% (25% + 15% x 2).
Level 4: +70% (25% + 15% x 3).
Level 5: +100% (final increase for max projectile speed).
Application to Skills and Cat:

applyToSkillsAndCat() sets the speed multiplier across all skills with projectiles and adjusts the cat’s speed at max level.
Description for UI:

getDescription() provides a level-based summary, updating to show the current percentage boost.*/