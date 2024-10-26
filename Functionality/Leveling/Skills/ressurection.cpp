//will revive the player if killed, but this upgrade is never usable again, sacrificies random other upgrade
//clears all enemies in the area, 
//if rerolled off, then rolled back again, it's usable. 
//not upgradable, just stays at a lvl-less skill
/*One-Time Activation:

activate() revives the player, clears enemies, sacrifices a random upgrade, and sets the skill to unusable.
Reset for Reroll:

reset() makes the skill usable again if it’s rerolled away and later obtained again.
Clear Enemies and Sacrifice Upgrade:

clearEnemies() removes all enemies in the area.
sacrificeRandomUpgrade() randomly removes one upgrade from the player’s list of upgrades.*/
#ifndef RESURRECTION_H
#define RESURRECTION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Resurrection {
public:
    Resurrection();
    bool canActivate() const;
    void activate(std::vector<class Enemy*>& enemies, std::vector<std::string>& upgrades);
    void draw(sf::RenderWindow& window, const sf::Vector2f& position);
    void reset(); // Resets skill to usable if rerolled back

private:
    sf::Texture skillTexture;
    sf::Sprite skillIcon;
    bool usable;

    void clearEnemies(std::vector<class Enemy*>& enemies);
    void sacrificeRandomUpgrade(std::vector<std::string>& upgrades);
};

#endif

// Implementation

#include "Resurrection.h"
#include "Enemy.h"
#include <algorithm>
#include <random>
#include <iostream>

Resurrection::Resurrection() : usable(true) {
    skillTexture.loadFromFile("resurrection.png"); // Replace with actual texture path
    skillIcon.setTexture(skillTexture);
    skillIcon.setOrigin(skillTexture.getSize().x / 2, skillTexture.getSize().y / 2);
}

bool Resurrection::canActivate() const {
    return usable;
}

void Resurrection::activate(std::vector<Enemy*>& enemies, std::vector<std::string>& upgrades) {
    if (usable) {
        clearEnemies(enemies);
        sacrificeRandomUpgrade(upgrades);
        usable = false; // One-time use until rerolled back
    }
}

void Resurrection::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    skillIcon.setPosition(position);
    window.draw(skillIcon);
}

void Resurrection::reset() {
    usable = true;
}

void Resurrection::clearEnemies(std::vector<Enemy*>& enemies) {
    enemies.clear(); // Remove all enemies from the area
}

void Resurrection::sacrificeRandomUpgrade(std::vector<std::string>& upgrades) {
    if (!upgrades.empty()) {
        int randomIndex = rand() % upgrades.size();
        std::cout << "Sacrificing upgrade: " << upgrades[randomIndex] << "\n";
        upgrades.erase(upgrades.begin() + randomIndex);
    }
}

