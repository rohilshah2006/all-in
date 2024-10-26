//small chance to drop from common enemies
// just increases atk speed by 100%, so 100% orig + 100% is 200%, for 10 seconds
/*Drop Chance:

shouldDrop() checks if the item should drop, based on a small chance from common enemies.
Activation and Duration:

activate() doubles the attack speed when picked up, and update() manages the 10-second countdown.
Attack Speed Reset:

resetAttackSpeed() restores the player’s original attack speed after the effect duration ends.*/

#ifndef DOUBLEFIRE_H
#define DOUBLEFIRE_H

#include <SFML/Graphics.hpp>
#include <string>

class DoubleFire {
public:
    DoubleFire();
    bool shouldDrop(int dropChance) const;
    void activate(float& attackSpeed);
    void update(float deltaTime, float& attackSpeed);
    void draw(sf::RenderWindow& window, const sf::Vector2f& position);
    bool isActive() const;

private:
    sf::Texture itemTexture;
    sf::Sprite itemSprite;
    float duration;
    bool active;

    void resetAttackSpeed(float& attackSpeed);
};

#endif

// Implementation

#include "DoubleFire.h"

DoubleFire::DoubleFire() : duration(10.0f), active(false) {
    itemTexture.loadFromFile("doublefire.png"); // Replace with actual path
    itemSprite.setTexture(itemTexture);
    itemSprite.setOrigin(itemTexture.getSize().x / 2, itemTexture.getSize().y / 2);
}

bool DoubleFire::shouldDrop(int dropChance) const {
    return rand() % 100 < dropChance; // Small chance to drop
}

void DoubleFire::activate(float& attackSpeed) {
    if (!active) {
        attackSpeed *= 2.0f; // Double the attack speed
        active = true;
    }
}

void DoubleFire::update(float deltaTime, float& attackSpeed) {
    if (active) {
        duration -= deltaTime;
        if (duration <= 0) {
            resetAttackSpeed(attackSpeed);
            active = false;
        }
    }
}

void DoubleFire::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    itemSprite.setPosition(position);
    window.draw(itemSprite);
}

bool DoubleFire::isActive() const {
    return active;
}

void DoubleFire::resetAttackSpeed(float& attackSpeed) {
    attackSpeed /= 2.0f; // Restore to original attack speed
}
