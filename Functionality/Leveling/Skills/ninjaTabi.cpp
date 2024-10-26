//lvl 1, dodges 1 attack from any enemy, invulnerable from that single attack, recharges every 10 seconds
//lvl5, 10/10 dodge charges, recharges every 8 seconds
#ifndef NINJATABI_H
#define NINJATABI_H

#include <SFML/Graphics.hpp>
#include <string>

class NinjaTabi {
public:
    NinjaTabi();
    void upgrade();
    bool dodgeAttack();
    void recharge(float deltaTime);
    std::string getDescription() const;

private:
    int level;
    int maxLevel;
    int maxDodges;
    int currentDodges;
    float rechargeTime;
    float rechargeCooldown;
    std::string description;

    void updateSkillProperties();
};

#endif

#include "NinjaTabi.h"
#include <iostream>

NinjaTabi::NinjaTabi()
    : level(1), maxLevel(5), maxDodges(1), currentDodges(1), rechargeTime(10.0f), rechargeCooldown(0.0f) {
    updateSkillProperties(); // Set initial description
}

void NinjaTabi::upgrade() {
    if (level < maxLevel) {
        level++;
        updateSkillProperties();
    }
}

bool NinjaTabi::dodgeAttack() {
    if (currentDodges > 0) {
        currentDodges--;
        rechargeCooldown = rechargeTime; // Start recharge
        return true;
    }
    return false;
}

void NinjaTabi::recharge(float deltaTime) {
    if (currentDodges < maxDodges) {
        rechargeCooldown -= deltaTime;
        if (rechargeCooldown <= 0.0f) {
            currentDodges++;
            rechargeCooldown = rechargeTime; // Reset cooldown for the next dodge
        }
    }
}

std::string NinjaTabi::getDescription() const {
    return description;
}

void NinjaTabi::updateSkillProperties() {
    switch (level) {
        case 1:
            maxDodges = 1;
            rechargeTime = 10.0f;
            description = "NinjaTabi Level 1: 1 dodge charge, recharges every 10 seconds.";
            break;
        case 2:
            maxDodges = 2;
            rechargeTime = 10.0f;
            description = "NinjaTabi Level 2: 2 dodge charges, recharges every 10 seconds.";
            break;
        case 3:
            maxDodges = 4;
            rechargeTime = 9.0f;
            description = "NinjaTabi Level 3: 4 dodge charges, recharges every 9 seconds.";
            break;
        case 4:
            maxDodges = 6;
            rechargeTime = 8.5f;
            description = "NinjaTabi Level 4: 6 dodge charges, recharges every 8.5 seconds.";
            break;
        case 5:
            maxDodges = 10;
            rechargeTime = 8.0f;
            description = "NinjaTabi Level 5: 10 dodge charges, recharges every 8 seconds.";
            break;
    }
    currentDodges = maxDodges; // Reset to max dodges after upgrading
}

/*Explanation
Skill Levels:

Level 1: 1 dodge, recharges every 10 seconds.
Level 2: 2 dodges, same recharge time.
Level 3: 4 dodges, recharges every 9 seconds.
Level 4: 6 dodges, recharges every 8.5 seconds.
Level 5: 10 dodges, recharges every 8 seconds.
Dodge and Recharge:

dodgeAttack() uses a dodge charge if available, starting the cooldown.
recharge() refills dodge charges over time, based on rechargeTime.
Descriptions:

getDescription() provides the current skill level description, updating after each upgrade.*/