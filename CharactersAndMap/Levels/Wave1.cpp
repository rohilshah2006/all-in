// This is going to be Wave 1
// We can build on this wave with the following. Enemies and distraction will increase in difficulty and qualtity from this wave
// This is like a base wave

//higher waves, like wave 30 will have lower bosses spawn frequently, without a boss drop
//lower bosses eventually replace the base "enemyTracker", in further waves
#ifndef WAVESYSTEM_H
#define WAVESYSTEM_H

#include <SFML/Graphics.hpp>
#include <vector>

class WaveSystem {
public:
    WaveSystem();
    void startWave(int waveNumber);
    void update(float deltaTime);
    void spawnEnemies();

private:
    int currentWave;
    int enemyCount;
    std::vector<class Enemy*> enemies; // Assume an Enemy class exists
    void setupWaveParameters(int waveNumber);
};

#endif
#include "WaveSystem.h"
#include "Enemy.h" // Assuming Enemy class exists
#include <iostream>

WaveSystem::WaveSystem() : currentWave(1), enemyCount(0) {
    // Start with the first wave
    startWave(currentWave);
}

void WaveSystem::startWave(int waveNumber) {
    setupWaveParameters(waveNumber);
    spawnEnemies();
    std::cout << "Starting Wave " << waveNumber << " with " << enemyCount << " enemies." << std::endl;
}

void WaveSystem::update(float deltaTime) {
    // Logic to update enemies, check if all are defeated, etc.
}

void WaveSystem::spawnEnemies() {
    for (int i = 0; i < enemyCount; ++i) {
        // Create and spawn enemy instances
        Enemy* enemy = new Enemy(); // Replace with actual enemy constructor
        enemies.push_back(enemy);
    }
}

void WaveSystem::setupWaveParameters(int waveNumber) {
    // Set up parameters based on wave number
    if (waveNumber == 1) {
        enemyCount = 5; // Base wave with 5 enemies
    } else {
        enemyCount = waveNumber * 2; // Example: increase enemy count for subsequent waves
    }

    // Add logic for lower bosses in higher waves if needed
    if (waveNumber % 5 == 0) { // Example: Every 5th wave spawns a boss
        // Logic to spawn a boss
    }
}
