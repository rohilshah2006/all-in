//will spawn right outside of player FOV
//each enemy will drop a base exp count like 5exp gems/variable icon, 
// enemy has a chance of dropping a rarer, higher exp gem like 10exp per rare-er gem

//variety of enemies, some will shoot projectiles towards you, your attacks can break these projectiles

/*Enemy Class: Manages the properties of enemies, including spawning and experience drop logic.
Experience Drops: Each enemy drops EXP based on a random chance, with values of 5, 10, or 20.
Spawn Logic: Enemies spawn just outside the player's FOV, either to the left or right side of the screen.
*/

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>

class Enemy {
public:
    Enemy(const sf::Vector2f& spawnPosition);
    void update(float deltaTime);
    void shoot();
    void dropEXP(std::vector<sf::Sprite>& expDrops);

    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    void setPosition(const sf::Vector2f& position) { sprite.setPosition(position); }

private:
    sf::Sprite sprite;
    sf::Texture texture; // Replace with actual enemy texture path
    float speed;
    int expDropAmount; // Base EXP amount for this enemy
};

#endif
#include "Enemy.h"
#include <cstdlib> // For rand()
#include <ctime>   // For time()

Enemy::Enemy(const sf::Vector2f& spawnPosition) : speed(100.0f), expDropAmount(5) {
    texture.loadFromFile("enemy.png"); // Replace with actual texture path
    sprite.setTexture(texture);
    sprite.setPosition(spawnPosition);
}

void Enemy::update(float deltaTime) {
    // Update enemy behavior, movement, etc.
    // Example: Move towards the player or a specific direction
}

void Enemy::shoot() {
    // Logic for shooting projectiles toward the player
}

void Enemy::dropEXP(std::vector<sf::Sprite>& expDrops) {
    int randomValue = rand() % 100; // Random value for determining drop type
    if (randomValue < 5) {
        expDropAmount = 20; // Rare drop
    } else if (randomValue < 20) {
        expDropAmount = 10; // Uncommon drop
    } else {
        expDropAmount = 5; // Common drop
    }

    // Create the EXP sprite
    sf::Sprite expDrop;
    // Set the texture for the EXP drop based on the amount (you'll need to manage textures)
    // Example: expDrop.setTexture(expTexture); 
    expDrops.push_back(expDrop);
}

void WaveSystem::spawnEnemies() {
    for (int i = 0; i < enemyCount; ++i) {
        // Calculate a position outside the player's FOV (example logic)
        sf::Vector2f spawnPosition;
        spawnPosition.x = (rand() % 2 == 0) ? -100 : 800; // Spawn to the left or right of the screen
        spawnPosition.y = rand() % 600; // Random vertical position within screen height

        Enemy* enemy = new Enemy(spawnPosition); // Create and spawn enemy instances
        enemies.push_back(enemy);
    }
}
