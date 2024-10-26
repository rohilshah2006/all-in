//lightblue transparent overlay, under player
//does slight minimal damage for enemies within the area
//lvl 5 could just be a radius 2x the oriignal size, and does like 1.1x damage, it has a dps
/*Level-Based Scaling:

Each level increases the radius by 20% up to level 5, where the radius doubles.
Damage scales by a factor of 1.1x per level, starting from baseDamage (5.0).
Damage Application:

applyDamage calculates DPS by applying damage every frame based on deltaTime.
The damage applies only to enemies within the radius of the field.
Drawing the Field:

draw sets the field position relative to the player’s position and renders it as a light-blue transparent overlay.
*/

#ifndef ELECTRICFIELD_H
#define ELECTRICFIELD_H

#include <SFML/Graphics.hpp>
#include <vector>

class ElectricField {
public:
    ElectricField();
    void upgrade();
    void applyDamage(std::vector<class Enemy*>& enemies, float deltaTime);
    void draw(sf::RenderWindow& window, const sf::Vector2f& playerPosition);

private:
    int level;
    int maxLevel;
    float radius;
    float baseDamage;
    float damageMultiplier;
    sf::CircleShape fieldShape;

    void updateFieldProperties();
};

#endif
