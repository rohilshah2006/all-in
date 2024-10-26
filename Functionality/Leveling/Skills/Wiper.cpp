// like a beam that circles the user, in a 360, up1, 
// 5th pick, could be 5 wipers that circle user, the beams could just change color to purple or smth
#ifndef WIPER_H
#define WIPER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Wiper {
public:
    Wiper();
    void upgrade();
    void update(float deltaTime, const sf::Vector2f& playerPosition);
    void draw(sf::RenderWindow& window);

private:
    int level;
    int maxLevel;
    int numBeams;
    float rotationSpeed;
    sf::Color beamColor;
    std::vector<sf::RectangleShape> beams;

    void updateSkillProperties();
};

#endif

// Implementation

#include "Wiper.h"

Wiper::Wiper() : level(1), maxLevel(5), numBeams(1), rotationSpeed(90.0f), beamColor(sf::Color::Cyan) {
    sf::RectangleShape beam(sf::Vector2f(100.0f, 5.0f)); // Base length and width of each beam
    beam.setFillColor(beamColor);
    beams.push_back(beam);

    updateSkillProperties();
}

void Wiper::upgrade() {
    if (level < maxLevel) {
        level++;
        updateSkillProperties();
    }
}

void Wiper::update(float deltaTime, const sf::Vector2f& playerPosition) {
    float angleIncrement = 360.0f / numBeams;
    float currentAngle = 0.0f;

    for (auto& beam : beams) {
        currentAngle += angleIncrement;
        float angleInRadians = currentAngle * 3.14159f / 180.0f;
        beam.setPosition(playerPosition.x + std::cos(angleInRadians) * 100, playerPosition.y + std::sin(angleInRadians) * 100); // Distance from player
        beam.setRotation(currentAngle + rotationSpeed * deltaTime);
    }
}

void Wiper::draw(sf::RenderWindow& window) {
    for (auto& beam : beams) {
        window.draw(beam);
    }
}

void Wiper::updateSkillProperties() {
    beams.clear();
    numBeams = level; // Number of beams matches level
    beamColor = (level == maxLevel) ? sf::Color(128, 0, 128) : sf::Color::Cyan; // Purple at max level
    rotationSpeed = 90.0f + level * 15.0f; // Increment rotation speed with each level

    for (int i = 0; i < numBeams; i++) {
        sf::RectangleShape beam((level == maxLevel) ? sf::Vector2f(125.0f, 6.25f) : sf::Vector2f(100.0f, 5.0f)); // 1.25x size at max level
        beam.setFillColor(beamColor);
        beams.push_back(beam);
    }
}
/*Level Scaling:
Beams: Adds one beam per level, capped at 5 beams.
Rotation Speed: rotationSpeed increases with each level for faster rotation.
Max Level Enhancements:
beamColor changes to purple.
Beam hitbox size is increased by 1.25x (125 length, 6.25 width).*/