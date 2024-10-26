//drops a "bomb"/
//after few seconds, will do damage to enemies within and outside of bomb area
//keep in mind, every upgrade is initially weak, just becomes more powerful as the game goes on
//upgrade1 , drops 1 bomb
//final upgrade, drops 5 bombs around player, blows up 100% quicker , designs change as upgraded
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class BombSkill {
public:
    BombSkill()
        : level(1), maxLevel(5), numBombs(1), explosionDelay(3.0f) {
        loadTextures();
        updateSkillDescription();
    }

    // Upgrade the bomb skill, changing attributes based on level
    void upgrade() {
        if (level < maxLevel) {
            level++;
            numBombs = (level == 5) ? 5 : level;
            explosionDelay = (level == 5) ? explosionDelay / 2 : explosionDelay;
            updateSkillDescription();
        } else {
            std::cout << "Bomb skill is already at max level!\n";
        }
    }

    // Show skill details in the console for now
    void displaySkillInfo() const {
        std::cout << "Bomb Skill - Level " << level << ": " << description << "\n";
    }

    // Draw bombs on screen based on level and location
    void dropBombs(sf::RenderWindow& window, const sf::Vector2f& position) {
        for (int i = 0; i < numBombs; i++) {
            sf::Sprite bombSprite = bombSprites[level - 1];
            bombSprite.setPosition(position.x + (i - numBombs / 2) * 40, position.y);
            window.draw(bombSprite);
        }
    }

private:
    int level;
    int maxLevel;
    int numBombs;
    float explosionDelay;
    std::string description;
    std::vector<sf::Texture> bombTextures;
    std::vector<sf::Sprite> bombSprites;

    // Load different textures for each level of the skill
    void loadTextures() {
        for (int i = 1; i <= maxLevel; i++) {
            sf::Texture texture;
            if (texture.loadFromFile("bomb_level" + std::to_string(i) + ".png")) {
                bombTextures.push_back(texture);
                sf::Sprite sprite(texture);
                bombSprites.push_back(sprite);
            } else {
                std::cerr << "Failed to load bomb_level" << i << ".png\n";
            }
        }
    }

    // Update skill description for the current level
    void updateSkillDescription() {
        description = "Drops " + std::to_string(numBombs) + " bomb(s)";
        if (level == maxLevel) {
            description += ", with 100% faster explosion";
        }
    }
};
