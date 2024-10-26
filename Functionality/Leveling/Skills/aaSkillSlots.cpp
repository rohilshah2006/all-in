// 6 skill slots
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>

namespace SkillSystem {

    // Struct for storing skill data
    struct Skill {
        std::string name;
        std::string description;
        sf::Texture iconTexture;
    };

    // Class representing the skill selection menu
    class SkillSelectionMenu {
    private:
        std::vector<Skill> availableSkills;
        std::vector<Skill> acquiredSkills;
        sf::Font font;
        sf::RectangleShape slotBackground;
        sf::Text descriptionText;
        sf::RectangleShape iconDisplay;
        
    public:
        SkillSelectionMenu() {
            // Load a font for descriptions (Replace with actual font file)
            font.loadFromFile("arial.ttf");

            // Initialize slot display elements
            slotBackground.setSize(sf::Vector2f(150, 250)); // Rectangular slot for each skill
            slotBackground.setFillColor(sf::Color(50, 50, 50, 200)); // Semi-transparent dark gray

            descriptionText.setFont(font);
            descriptionText.setCharacterSize(16);
            descriptionText.setFillColor(sf::Color::White);
            
            iconDisplay.setSize(sf::Vector2f(64, 64)); // Size for skill icon
            iconDisplay.setOrigin(32, 32); // Center the icon
        }

        void addAvailableSkill(const Skill& skill) {
            availableSkills.push_back(skill);
        }

        void showSkillSelection(sf::RenderWindow& window) {
            // Pause game logic could go here

            // Randomly select 3 skills, favoring already acquired skills
            std::vector<Skill> selection = selectSkillsForUpgrade();

            // Display each selected skill in a vertical layout
            for (int i = 0; i < 3; i++) {
                float xPos = window.getSize().x / 2 - 75;
                float yPos = 100 + i * 270;

                slotBackground.setPosition(xPos, yPos);
                window.draw(slotBackground);

                // Set and display icon
                iconDisplay.setTexture(&selection[i].iconTexture);
                iconDisplay.setPosition(xPos + 75, yPos + 40);
                window.draw(iconDisplay);

                // Set and display description
                descriptionText.setString(selection[i].description);
                descriptionText.setPosition(xPos + 10, yPos + 150);
                window.draw(descriptionText);
            }

            // Display logic here, for demonstration only
            window.display();
        }

        // Skill selection algorithm with increased probability for owned skills
        std::vector<Skill> selectSkillsForUpgrade() {
            std::vector<Skill> selectedSkills;
            std::map<int, Skill> skillPool;
            int maxWeight = 0;

            for (size_t i = 0; i < availableSkills.size(); ++i) {
                int weight = 10; // Base weight

                // Increase probability if the skill is already acquired
                for (const auto& acquired : acquiredSkills) {
                    if (availableSkills[i].name == acquired.name) {
                        weight += 20; // Increase weight for acquired skills
                        break;
                    }
                }

                maxWeight += weight;
                skillPool[maxWeight] = availableSkills[i];
            }

            while (selectedSkills.size() < 3) {
                int randValue = rand() % maxWeight + 1;

                for (const auto& entry : skillPool) {
                    if (randValue <= entry.first) {
                        selectedSkills.push_back(entry.second);
                        break;
                    }
                }
            }
            return selectedSkills;
        }

        void acquireSkill(const Skill& skill) {
            if (acquiredSkills.size() < 6) {
                acquiredSkills.push_back(skill);
            }
        }

        int getSkillCount() const {
            return acquiredSkills.size();
        }
    };
}



/*Explanation of Key Parts
Skill Selection Menu:

SkillSelectionMenu has a showSkillSelection function, displaying three vertical slots with skill icons and descriptions.
The selectSkillsForUpgrade function provides a higher chance of picking previously acquired skills, as defined in the weighted random selection.
6-Max Slot Limit:

acquireSkill checks if the player has fewer than 6 skills before adding a new one to acquiredSkills.
Interface Display:

The showSkillSelection function pauses gameplay to render a selection screen with three options. Each option shows the skill’s icon and description.
Adjustable Descriptions:

The description is easily customizable per skill using descriptionText.setString.
Notes
Textures and Fonts: Replace "skill_icon.png" and "arial.ttf" with paths to actual resources.
Event Handling: This example does not include input handling for selecting a skill. You can add event handling for mouse clicks or keypresses.*/