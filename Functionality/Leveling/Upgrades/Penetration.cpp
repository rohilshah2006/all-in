// first upgrade, projectiles will pierce 1 extra enemy
//final upgrade, projectiles will infinitely pierce enemies, shoot crossmap
// lag issue maybe, despawns projectiles once out of user pov, and enemy spawn
#ifndef PENETRATIONUPGRADE_H
#define PENETRATIONUPGRADE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PenetrationUpgrade {
public:
    PenetrationUpgrade();
    void upgrade();
    int getMaxPierceCount() const;
    bool shouldDespawnProjectile(const sf::Vector2f& position, const sf::FloatRect& playerFOV, const sf::FloatRect& enemySpawnArea) const;
    std::string getDescription() const;

private:
    int level;
    int maxLevel;
    int maxPierceCount;

    void updatePierceCount();
};

#endif

// Implementation

#include "PenetrationUpgrade.h"
#include <sstream>

PenetrationUpgrade::PenetrationUpgrade() : level(1), maxLevel(5) {
    updatePierceCount();
}

void PenetrationUpgrade::upgrade() {
    if (level < maxLevel) {
        level++;
        updatePierceCount();
    }
}

int PenetrationUpgrade::getMaxPierceCount() const {
    return maxPierceCount;
}

bool PenetrationUpgrade::shouldDespawnProjectile(const sf::Vector2f& position, const sf::FloatRect& playerFOV, const sf::FloatRect& enemySpawnArea) const {
    return !playerFOV.contains(position) && !enemySpawnArea.contains(position); // Despawn if outside both FOV and spawn area
}

std::string PenetrationUpgrade::getDescription() const {
    std::ostringstream desc;
    if (level < maxLevel) {
        desc << "Penetration Upgrade Level " << level << ": Projectiles pierce up to " << maxPierceCount << " enemies";
    } else {
        desc << "Penetration Upgrade Max Level: Projectiles infinitely pierce and shoot across the map";
    }
    return desc.str();
}

void PenetrationUpgrade::updatePierceCount() {
    if (level < maxLevel) {
        maxPierceCount = level; // Level 1 pierces 1 enemy, Level 2 pierces 2, etc.
    } else {
        maxPierceCount = -1; // -1 for infinite piercing at max level
    }
}
/*Piercing Levels:

Levels 1-4: Incrementally increases the number of enemies projectiles can pierce, matching the level.
Level 5 (Max): Allows projectiles to pierce infinitely.
Projectile Despawning:

shouldDespawnProjectile() checks if a projectile is outside both the player’s FOV and the enemy spawn area, despawning it to prevent lag.
Description:

getDescription() provides the current pierce count, updating to reflect the infinite pierce ability at max level.
*/