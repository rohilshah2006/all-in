// a pet cat that runs around and attacks things for you
//lvl 1 dmg is like, 20, base movespeed is like the player speed
//lvl 5 is more base dmg and faster than player
//if player FOV can no longer see the cat, it will start running to player at 2x it's movespeed
//cat will not have health, and it will not attack projectiles, just enemies

/*Skill Levels:

Level 1: Base 20 damage, moves at the player’s speed.
Levels 2-4: Gradual increases in base damage and speed.
Level 5: Base 40 damage, 1.5x the player’s speed.
Out-of-FOV Behavior:

If the cat moves outside the player’s FOV, it returns to the player at returnSpeed (2x its regular speed).
Enemy Attacks:

attackEnemies() applies damage to enemies within 30 units of the cat’s position.*/

#ifndef PETCAT_H
#define PETCAT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

class PetCat {
public:
    PetCat(float playerSpeed);
    void upgrade();
    void updatePosition(const sf::Vector2f& playerPosition, const sf::FloatRect& playerFOV, float deltaTime);
    void attackEnemies(std::vector<class Enemy*>& enemies);
    void draw(sf::RenderWindow& window);

private:
    int level;
    int maxLevel;
    float baseDamage;
    float moveSpeed;
    float returnSpeed;
    sf::Sprite catSprite;
    sf::Texture regularTexture;
    sf::Texture maxLevelTexture;

    void updateSkillProperties();
    void updateTexture();
};

#endif

// Implementation

PetCat::PetCat(float playerSpeed)
    : level(1), maxLevel(5), baseDamage(20.0f), moveSpeed(playerSpeed), returnSpeed(2 * playerSpeed) {
    // Load textures for levels 1-4 and level 5 (max level)
    if (!regularTexture.loadFromFile("pet_cat_regular.png")) {
        std::cerr << "Failed to load pet_cat_regular.png\n";
    }
    if (!maxLevelTexture.loadFromFile("pet_cat_max.png")) {
        std::cerr << "Failed to load pet_cat_max.png\n";
    }

    catSprite.setTexture(regularTexture);
    catSprite.setOrigin(regularTexture.getSize().x / 2, regularTexture.getSize().y / 2);

    updateSkillProperties();
}

void PetCat::upgrade() {
    if (level < maxLevel) {
        level++;
        updateSkillProperties();
    }
}

void PetCat::updatePosition(const sf::Vector2f& playerPosition, const sf::FloatRect& playerFOV, float deltaTime) {
    sf::Vector2f direction = playerPosition - catSprite.getPosition();
    float distance = std::hypot(direction.x, direction.y);

    if (!playerFOV.contains(catSprite.getPosition())) {
        direction /= distance;
        catSprite.move(direction * returnSpeed * deltaTime); // Moves at 2x speed outside FOV
    } else {
        direction /= distance;
        catSprite.move(direction * moveSpeed * deltaTime); // Normal movement speed
    }
}

void PetCat::attackEnemies(std::vector<class Enemy*>& enemies) {
    for (auto& enemy : enemies) {
        float distance = std::hypot(enemy->getPosition().x - catSprite.getPosition().x,
                                    enemy->getPosition().y - catSprite.getPosition().y);
        
        if (distance < 30.0f) { // Attack range
            enemy->takeDamage(baseDamage);
        }
    }
}

void PetCat::draw(sf::RenderWindow& window) {
    window.draw(catSprite);
}

void PetCat::updateSkillProperties() {
    switch (level) {
        case 1:
            baseDamage = 20.0f;
            moveSpeed *= 1.0f;
            break;
        case 2:
            baseDamage = 25.0f;
            moveSpeed *= 1.1f;
            break;
        case 3:
            baseDamage = 30.0f;
            moveSpeed *= 1.2f;
            break;
        case 4:
            baseDamage = 35.0f;
            moveSpeed *= 1.3f;
            break;
        case 5:
            baseDamage = 40.0f;
            moveSpeed *= 1.5f;
            updateTexture(); // Apply max-level texture
            break;
    }
}

void PetCat::updateTexture() {
    catSprite.setTexture(maxLevelTexture); // Use unique texture at level 5
}
