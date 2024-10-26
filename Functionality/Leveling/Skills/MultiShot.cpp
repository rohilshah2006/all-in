//cone like, multishot initially, 
// Can be upgraded  5 times, meaning, first pick, blue overlay over player and base 3 shot
//second time picked 5 shots
// fifth time, multishots shoots all angles, final design still but cooler...

/*Skill Scaling:

Level 1: Base 3 shots in a cone.
Level 2: 5 shots in a wider cone.
Level 5: Shoots in all directions with a special overlay design.
Overlay Texture Change:

At level 5, the cone overlay texture switches to finalOverlay, and the color changes to a darker blue for a distinct look.
Shot Firing Pattern:

fireShots draws each shot at a calculated angle. At level 5, shots are distributed evenly in a circle.*/

#ifndef MULTISHOT_H
#define MULTISHOT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Multishot {
public:
    Multishot();
    void upgrade();
    void fireShots(sf::RenderWindow& window, const sf::Vector2f& playerPosition);
    void drawOverlay(sf::RenderWindow& window, const sf::Vector2f& playerPosition);
    std::string getDescription() const;

private:
    int level;
    int maxLevel;
    int numShots;
    sf::Texture regularOverlay;
    sf::Texture finalOverlay;
    sf::ConvexShape coneOverlay;
    std::string description;

    void updateSkillProperties();
    void updateOverlay();
};

#endif

#include "Multishot.h"
#include <cmath>

Multishot::Multishot()
    : level(1), maxLevel(5), numShots(3) {
    // Load textures for overlay
    regularOverlay.loadFromFile("multishot_regular.png");
    finalOverlay.loadFromFile("multishot_final.png");

    // Initialize overlay properties for levels 1-4
    coneOverlay.setPointCount(3);
    coneOverlay.setPoint(0, sf::Vector2f(0, -50));
    coneOverlay.setPoint(1, sf::Vector2f(-30, 50));
    coneOverlay.setPoint(2, sf::Vector2f(30, 50));
    coneOverlay.setTexture(&regularOverlay);
    coneOverlay.setFillColor(sf::Color(0, 191, 255, 100)); // Light blue with transparency

    updateSkillProperties(); // Set initial description
}

void Multishot::upgrade() {
    if (level < maxLevel) {
        level++;
        updateSkillProperties();
    }
}

void Multishot::fireShots(sf::RenderWindow& window, const sf::Vector2f& playerPosition) {
    float angleIncrement = (level == maxLevel) ? 360.0f / numShots : 15.0f;
    float startAngle = (level == maxLevel) ? 0 : -15.0f * ((numShots - 1) / 2);

    for (int i = 0; i < numShots; i++) {
        sf::RectangleShape shot(sf::Vector2f(20, 5)); // Each shot is a small rectangle
        float angle = startAngle + i * angleIncrement;
        shot.setRotation(angle);
        shot.setPosition(playerPosition);
        shot.setFillColor(sf::Color::Blue);
        window.draw(shot);
    }
}

void Multishot::drawOverlay(sf::RenderWindow& window, const sf::Vector2f& playerPosition) {
    coneOverlay.setPosition(playerPosition);
    window.draw(coneOverlay);
}

std::string Multishot::getDescription() const {
    return description;
}

void Multishot::updateSkillProperties() {
    switch (level) {
        case 1:
            numShots = 3;
            description = "Multishot Level 1: Fires 3 shots in a cone.";
            break;
        case 2:
            numShots = 5;
            description = "Multishot Level 2: Fires 5 shots in a wider cone.";
            break;
        case 3:
            numShots = 7;
            description = "Multishot Level 3: Fires 7 shots with increased spread.";
            break;
        case 4:
            numShots = 9;
            description = "Multishot Level 4: Fires 9 shots in a wide arc.";
            break;
        case 5:
            numShots = 12;
            description = "Multishot Level 5: Fires in all directions with enhanced design.";
            updateOverlay(); // Change texture at level 5
            break;
    }
}

void Multishot::updateOverlay() {
    coneOverlay.setTexture(&finalOverlay); // Use final overlay texture at level 5
    coneOverlay.setFillColor(sf::Color(0, 0, 255, 120)); // Darker blue for the final design
}
