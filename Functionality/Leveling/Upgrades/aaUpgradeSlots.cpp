//4 upgrade slots
#ifndef UPGRADESLOTS_H
#define UPGRADESLOTS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>
#include <iostream>

class UpgradeSlots {
public:
    UpgradeSlots();
    void addUpgrade(const std::string& upgrade);
    void showUpgradeSelection(sf::RenderWindow& window);
    bool isFull() const;
    int getUpgradeCount() const;

private:
    int maxUpgradeSlots;
    std::vector<std::string> upgrades;
    sf::Texture upgradeTextures[3];
    sf::Sprite upgradeIcons[3];

    std::vector<std::string> generateUpgradeOptions();
    void displaySelectionScreen(sf::RenderWindow& window, const std::vector<std::string>& options);
    void loadUpgradeTextures();
};

#endif

// Implementation

UpgradeSlots::UpgradeSlots() : maxUpgradeSlots(4) {
    loadUpgradeTextures();
}

void UpgradeSlots::loadUpgradeTextures() {
    upgradeTextures[0].loadFromFile("damage_icon.png");     // Replace with actual path
    upgradeTextures[1].loadFromFile("cooldown_icon.png");   // Replace with actual path
    upgradeTextures[2].loadFromFile("radius_icon.png");     // Replace with actual path

    for (int i = 0; i < 3; i++) {
        upgradeIcons[i].setTexture(upgradeTextures[i]);
        upgradeIcons[i].setScale(0.5f, 0.5f); // Scale down if needed
    }
}

void UpgradeSlots::addUpgrade(const std::string& upgrade) {
    if (!isFull()) {
        upgrades.push_back(upgrade);
    } else {
        std::cout << "Upgrade slots are full.\n";
    }
}

bool UpgradeSlots::isFull() const {
    return upgrades.size() >= maxUpgradeSlots;
}

int UpgradeSlots::getUpgradeCount() const {
    return upgrades.size();
}

std::vector<std::string> UpgradeSlots::generateUpgradeOptions() {
    std::vector<std::string> possibleUpgrades = {
        "Increased Damage", "Faster Cooldown", "Larger Radius", "Bonus Health",
        "Speed Boost", "Enhanced Armor", "Regeneration", "Critical Hit Chance"
    };
    
    // Randomly select 3 options from possible upgrades
    std::vector<std::string> options;
    std::sample(possibleUpgrades.begin(), possibleUpgrades.end(), std::back_inserter(options), 3, std::mt19937{std::random_device{}()});
    return options;
}

void UpgradeSlots::showUpgradeSelection(sf::RenderWindow& window) {
    if (isFull()) {
        std::cout << "No available upgrade slots.\n";
        return;
    }

    std::vector<std::string> options = generateUpgradeOptions();
    displaySelectionScreen(window, options);
}

void UpgradeSlots::displaySelectionScreen(sf::RenderWindow& window, const std::vector<std::string>& options) {
    bool selectionMade = false;

    while (window.isOpen() && !selectionMade) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1 && !options.empty()) {
                    addUpgrade(options[0]);
                    selectionMade = true;
                } else if (event.key.code == sf::Keyboard::Num2 && options.size() > 1) {
                    addUpgrade(options[1]);
                    selectionMade = true;
                } else if (event.key.code == sf::Keyboard::Num3 && options.size() > 2) {
                    addUpgrade(options[2]);
                    selectionMade = true;
                }
            }
        }

        window.clear();
        
        // Display each upgrade option with icon and description
        for (size_t i = 0; i < options.size(); i++) {
            upgradeIcons[i].setPosition(100, 100 + i * 120); // Position icons vertically
            window.draw(upgradeIcons[i]);

            sf::Text optionText;
            optionText.setString(std::to_string(i + 1) + ": " + options[i]);
            optionText.setPosition(100, 150 + i * 120); // Position text below icon
            window.draw(optionText);
        }
        
        window.display();
    }
}

/*Upgrade Textures and Icons:

upgradeTextures loads three PNG icons (e.g., "damage_icon.png", "cooldown_icon.png", "radius_icon.png").
upgradeIcons are set to use these textures and are displayed above each description.
Selection Display with Icons:

displaySelectionScreen() draws each icon with its corresponding upgrade description, updating the layout to position the icons above each option.
Gameplay Pause During Selection:

While the selection screen is displayed, gameplay is paused, and the player can pick an option using Num1, Num2, or Num3.*/