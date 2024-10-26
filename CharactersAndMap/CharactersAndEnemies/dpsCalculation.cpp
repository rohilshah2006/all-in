// basic dps calculation, in corner of screen
/*Damage Tracking:

addDamage(): Adds damage from each hit to the totalDamage within each second.
update(): Every second, it updates currentDPS based on totalDamage, resets the total, and refreshes the display text.
Display and Formatting:

updateDPSText(): Updates the text with the latest DPS value.
draw(): Renders the DPS counter at the top-right corner of the screen.
Usage:

Call addDamage() each time a skill or base attack deals damage.
Call update() in your main loop with the delta time, then draw() to render.*/

#ifndef DPSDISPLAY_H
#define DPSDISPLAY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

class DPSDisplay {
public:
    DPSDisplay();
    void addDamage(float damage);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    float currentDPS;
    float totalDamage;
    float dpsUpdateTime;
    sf::Font font;
    sf::Text dpsText;

    void updateDPSText();
};

#endif

// Implementation

#include "DPSDisplay.h"

DPSDisplay::DPSDisplay() : currentDPS(0), totalDamage(0), dpsUpdateTime(1.0f) {
    font.loadFromFile("arial.ttf"); // Replace with the appropriate font path
    dpsText.setFont(font);
    dpsText.setCharacterSize(18);
    dpsText.setFillColor(sf::Color::White);
    dpsText.setPosition(900, 10); // Adjust as needed for the top-right corner

    updateDPSText();
}

void DPSDisplay::addDamage(float damage) {
    totalDamage += damage; // Track damage dealt in the current second
}

void DPSDisplay::update(float deltaTime) {
    dpsUpdateTime -= deltaTime;

    if (dpsUpdateTime <= 0) {
        currentDPS = totalDamage; // Set DPS based on total damage dealt in the last second
        totalDamage = 0;          // Reset for the next second
        dpsUpdateTime = 1.0f;     // Reset update timer

        updateDPSText();
    }
}

void DPSDisplay::draw(sf::RenderWindow& window) {
    window.draw(dpsText);
}

void DPSDisplay::updateDPSText() {
    std::ostringstream dpsStream;
    dpsStream << "DPS: " << currentDPS;
    dpsText.setString(dpsStream.str());
}
