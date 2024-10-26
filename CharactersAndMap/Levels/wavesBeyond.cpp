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

    if (waveNumber % 5 == 0) { // Every 5th wave spawns a boss
        Boss* boss = new Boss(waveNumber / 5); // Create a new boss based on the wave number
        // Add boss to a boss list or handle it appropriately in the game
        std::cout << "Boss spawned for Wave " << waveNumber << "!" << std::endl;
    }

    std::cout << "Starting Wave " << waveNumber << " with " << enemyCount << " enemies." << std::endl;
}


void WaveSystem::update(float deltaTime) {
    // Logic to update enemies, check if all are defeated, etc.
    // Clean up defeated enemies if necessary
}

void WaveSystem::spawnEnemies() {
    for (int i = 0; i < enemyCount; ++i) {
        // Create and spawn enemy instances
        Enemy* enemy = new Enemy(); // Replace with actual enemy constructor
        enemies.push_back(enemy);
    }
}

void WaveSystem::setupWaveParameters(int waveNumber) {
    // Increase enemy count by 100 and scale by 1.5 for each round
    if (waveNumber == 1) {
        enemyCount = 100; // Base wave with 100 enemies
    } else {
        enemyCount = static_cast<int>(enemyCount * 1.5); // Scale by 1.5x each wave
    }

    // Logic for boss waves
    if (waveNumber % 5 == 0) { // Example: Every 5th wave spawns a boss
        // Logic to spawn a boss
        // Reset enemy count or adjust based on boss mechanics
    }
}
/*Base Enemy Count: The base enemy count is set to 100 for Wave 1.
Scaling Logic: For subsequent waves, the enemy count is scaled by 1.5 times the previous count.
Type Casting: The enemy count is cast to an integer to ensure it remains a whole number.
Example Behavior
Wave 1: 100 enemies
Wave 2: 
100
×
1.5
=
150
100×1.5=150 enemies
Wave 3: 
150
×
1.5
=
225
150×1.5=225 enemies
Wave 4: 
225
×
1.5
=
337.5
→
337
225×1.5=337.5→337 enemies (rounded down)
This setup will create a significant increase in enemy counts, ramping up the challenge as the game progresses. Let me know if you need any further modifications or additional features!*/