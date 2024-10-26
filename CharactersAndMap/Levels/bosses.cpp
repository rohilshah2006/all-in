//10 bosses total, designs get a bit more complex 
//first boss can be like base color octogon, 2nd could be a slightly bigger 
//octogon with circles embeded inside, ,later octogons can have mini-player model triangles trapped
//first apperance ever 5 waves, each boss drops 1 guarnteed lvl  for player
#ifndef BOSS_H
#define BOSS_H

#include <SFML/Graphics.hpp>
#include <vector>

class Boss {
public:
    Boss(int bossNumber);
    void update(float deltaTime);
    void dropLevel(std::vector<class Player*>& players);

private:
    sf::Sprite bossSprite;
    sf::Texture bossTexture; // Replace with actual boss texture path
    int levelDrop; // The level this boss drops for the player
    void setBossDesign(int bossNumber);
};

#endif

#include "Boss.h"
#include "Player.h" // Assuming Player class exists
#include <iostream>

Boss::Boss(int bossNumber) : levelDrop(1) {
    setBossDesign(bossNumber); // Set the boss design based on the boss number
}

void Boss::update(float deltaTime) {
    // Update boss behavior, movement, etc.
}

void Boss::dropLevel(std::vector<Player*>& players) {
    // Logic to drop a level for each player
    for (auto& player : players) {
        player->levelUp(levelDrop); // Assuming levelUp is a method in the Player class
    }
}

void Boss::setBossDesign(int bossNumber) {
    // Design logic based on the boss number
    switch (bossNumber) {
        case 1:
            bossTexture.loadFromFile("octagon1.png"); // Replace with actual texture path
            break;
        case 2:
            bossTexture.loadFromFile("octagon2.png"); // Replace with actual texture path
            break;
        // Add additional cases for bosses 3-10 with progressively complex designs
        default:
            std::cout << "Invalid Boss Number" << std::endl;
            break;
    }
    bossSprite.setTexture(bossTexture);
}

