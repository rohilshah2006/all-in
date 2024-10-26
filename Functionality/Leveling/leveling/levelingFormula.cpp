//amoung for leveling exp req, e.g. lvl1 to lvl2 will be 500 exp req
//lvl 2 to 3 could be like 800
//i'm thinking, +300 exp req for each lvl 1-10
//+500 for 10-20 maybe
//1.05x the original amount each upgrade after lvl 20

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Constants for EXP drop types
enum class ExpType { COMMON = 5, UNCOMMON = 10, RARE = 20 };

// Utility function for generating random numbers
int getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Namespace for all game entities
namespace GameEntities {

    // Player class with leveling system
    class Player {
    private:
        sf::Sprite sprite;
        int level;
        int exp;
        int expToNextLevel;

    public:
        Player(const sf::Texture& texture)
            : level(1), exp(0), expToNextLevel(500) { // Start with 500 EXP required for level 2
            sprite.setTexture(texture);
            sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        }

        void addExp(int amount) {
            exp += amount;
            std::cout << "Gained " << amount << " EXP! Total EXP: " << exp << std::endl;
            if (exp >= expToNextLevel) {
                levelUp();
            }
        }

        void levelUp() {
            level++;
            exp -= expToNextLevel;
            expToNextLevel = calculateExpToNextLevel();

            std::cout << "Level Up! New Level: " << level << " | EXP for Next Level: " << expToNextLevel << std::endl;
        }

        int calculateExpToNextLevel() const {
            if (level < 10) {
                return expToNextLevel + 300;
            } else if (level < 20) {
                return expToNextLevel + 500;
            } else {
                return static_cast<int>(expToNextLevel * 1.05); // 5% increase for each level after 20
            }
        }

        void setPosition(const sf::Vector2f& position) {
            sprite.setPosition(position);
        }

        sf::Sprite& getSprite() { return sprite; }
    };

    // ExpDrop class representing an EXP drop on the ground
    class ExpDrop {
    public:
        sf::Sprite sprite;
        ExpType type;
        int amount;

        ExpDrop(const sf::Texture& texture, ExpType type, sf::Vector2f position)
            : type(type), amount(static_cast<int>(type)) {
            sprite.setTexture(texture);
            sprite.setPosition(position);
            sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        }

        int getAmount() const { return amount; }
    };

    // Enemy class with customized EXP drop rates
    class Enemy {
    private:
        sf::Sprite sprite;

    public:
        Enemy(const sf::Texture& texture) {
            sprite.setTexture(texture);
            sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        }

        bool isDead() const {
            return true; // Placeholder for actual health logic
        }
        
        sf::Sprite& getSprite() { return sprite; }

        // Generate EXP drops based on enemy difficulty
        std::vector<ExpDrop> dropExp(const sf::Texture& expTexture, const sf::Vector2f& position) {
            std::vector<ExpDrop> drops;
            int dropChance = getRandom(1, 100);

            if (dropChance <= 70) {
                drops.emplace_back(expTexture, ExpType::COMMON, position); // 70% chance for 5 EXP
            }
            if (dropChance > 70 && dropChance <= 90) {
                drops.emplace_back(expTexture, ExpType::UNCOMMON, position); // 20% chance for 10 EXP
            }
            if (dropChance > 90) {
                drops.emplace_back(expTexture, ExpType::RARE, position); // 10% chance for 20 EXP
            }
            return drops;
        }

        void setPosition(const sf::Vector2f& position) {
            sprite.setPosition(position);
        }
    };
}
