//allows user pick an upgrade/skills and pick from a new hand of upgrades/skills, resets the upgrade lvl,
//e.g. rerolling lvl 5 bomb will give you a hand of lvl 1 skills/upgrades
//starts appearing once player has 6 skills in slot, or max upgrade slots (4)
#ifndef REROLLITEM_H
#define REROLLITEM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

class RerollItem {
public:
    RerollItem();
    bool canActivate(int skillSlotsFilled, int maxSkillSlots, int upgradeSlotsFilled, int maxUpgradeSlots) const;
    void activateReroll(std::vector<class Skill*>& skills, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, const sf::Vector2f& position);
    std::string getDescription() const;

private:
    sf::Texture itemTexture;
    sf::Sprite itemSprite;
    std::string description;

    void resetSkillLevel(Skill* skill);
    std::vector<Skill*> generateNewHand(const std::vector<Skill*>& allSkills);
    void displaySelectionScreen(sf::RenderWindow& window, const std::vector<Skill*>& newHand);
};

#endif

// Implementation

#include "RerollItem.h"
#include "Skill.h" // Assuming Skill class exists
#include <iostream>

RerollItem::RerollItem() {
    itemTexture.loadFromFile("reroll_item.png"); // Replace with actual item texture path
    itemSprite.setTexture(itemTexture);
    itemSprite.setOrigin(itemTexture.getSize().x / 2, itemTexture.getSize().y / 2);
    description = "Resets selected skill to level 1 and provides a new hand of options.";
}

bool RerollItem::canActivate(int skillSlotsFilled, int maxSkillSlots, int upgradeSlotsFilled, int maxUpgradeSlots) const {
    return (skillSlotsFilled >= maxSkillSlots || upgradeSlotsFilled >= maxUpgradeSlots);
}

void RerollItem::activateReroll(std::vector<Skill*>& skills, sf::RenderWindow& window) {
    // Select a random skill to reroll
    int skillIndex = rand() % skills.size();
    resetSkillLevel(skills[skillIndex]);

    // Generate a new hand of level 1 skill options
    std::vector<Skill*> newHand = generateNewHand(skills);
    displaySelectionScreen(window, newHand); // Pauses gameplay to display selection screen
}

void RerollItem::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    itemSprite.setPosition(position);
    window.draw(itemSprite);
}

std::string RerollItem::getDescription() const {
    return description;
}

void RerollItem::resetSkillLevel(Skill* skill) {
    skill->setLevel(1); // Reset skill to level 1
}

std::vector<Skill*> RerollItem::generateNewHand(const std::vector<Skill*>& allSkills) {
    std::vector<Skill*> newHand;
    std::sample(allSkills.begin(), allSkills.end(), std::back_inserter(newHand), 3, std::mt19937{std::random_device{}()});
    
    // Ensure the selected skills are level 1
    for (auto& skill : newHand) {
        skill->setLevel(1);
    }
    return newHand;
}

void RerollItem::displaySelectionScreen(sf::RenderWindow& window, const std::vector<Skill*>& newHand) {
    bool selectionMade = false;

    while (window.isOpen() && !selectionMade) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Detect keypresses for skill selection or skip
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1 && !newHand.empty()) {
                    // Select first skill in new hand
                    *newHand[0] = *newHand[0]; // Replace with actual skill application logic
                    selectionMade = true;
                } else if (event.key.code == sf::Keyboard::Num2 && newHand.size() > 1) {
                    *newHand[1] = *newHand[1]; // Replace with actual skill application logic
                    selectionMade = true;
                } else if (event.key.code == sf::Keyboard::Num3 && newHand.size() > 2) {
                    *newHand[2] = *newHand[2]; // Replace with actual skill application logic
                    selectionMade = true;
                } else if (event.key.code == sf::Keyboard::S) {
                    // Skip option
                    selectionMade = true;
                }
            }
        }

        // Clear and display selection UI
        window.clear();
        for (size_t i = 0; i < newHand.size(); i++) {
            newHand[i]->drawAsOption(window, i); // Displays each skill option in the selection UI
        }
        window.display();
    }
}
/*Activation Conditions:

canActivate() checks if the player has reached either max skill or upgrade slots, allowing the item to be used.
Rerolling a Skill:

activateReroll() selects a random skill from the player’s active skills, resets it to level 1, and generates a new hand of level 1 skills.
New Skill Hand:

generateNewHand() creates a new set of level 1 skills, allowing the player to select from fresh options.
Skill Selection Screen:

displaySelectionScreen() pauses gameplay, displays new skill options, and allows the player to pick a skill or skip with a key press (e.g., Num1, Num2, Num3, or S to skip).*/