#ifndef SKILLFIRERATES_H
#define SKILLFIRERATES_H

// Fire rate definitions (in seconds between actions)
namespace SkillFireRates {
    // Base rates for each skill
    const float MULTISHOT_RATE = 0.5f;
    const float TURRET_FIRE_RATE = 1.0f;
    const float BOMB_FIRE_RATE = 2.0f;
    const float WIPER_ROTATION_RATE = 90.0f; // Degrees per second for rotation
    const float PRISM_FIRE_RATE = 1.2f; // Example rate for Prism skill

    // DoubleFire modifier (100% increase means all rates halve temporarily)
    extern bool isDoubleFireActive;
    inline float getRateMultiplier() {
        return isDoubleFireActive ? 0.5f : 1.0f; // Halves the delay when active
    }
}

// Apply fire rate functions with DoubleFire modification
namespace SkillFireRateManager {
    inline float getMultishotRate() { return SkillFireRates::MULTISHOT_RATE * SkillFireRates::getRateMultiplier(); }
    inline float getTurretFireRate() { return SkillFireRates::TURRET_FIRE_RATE * SkillFireRates::getRateMultiplier(); }
    inline float getBombFireRate() { return SkillFireRates::BOMB_FIRE_RATE * SkillFireRates::getRateMultiplier(); }
    inline float getWiperRotationRate() { return SkillFireRates::WIPER_ROTATION_RATE; }
    inline float getPrismFireRate() { return SkillFireRates::PRISM_FIRE_RATE * SkillFireRates::getRateMultiplier(); }
}

// To activate and deactivate DoubleFire's effect
inline void activateDoubleFire() { SkillFireRates::isDoubleFireActive = true; }
inline void deactivateDoubleFire() { SkillFireRates::isDoubleFireActive = false; }

#endif

/*DoubleFire Toggle:

isDoubleFireActive: A boolean that controls whether DoubleFire’s effect is active.
getRateMultiplier(): Returns 0.5f (halving the rate delay) when DoubleFire is active, doubling the firing speed.
Modified Rate Functions:

Each rate function (e.g., getMultishotRate(), getPrismFireRate()) applies the multiplier based on DoubleFire status.
DoubleFire Activation:

activateDoubleFire() and deactivateDoubleFire() can be called when the item effect starts and ends, adjusting the rates across all skills accordingly.
*/