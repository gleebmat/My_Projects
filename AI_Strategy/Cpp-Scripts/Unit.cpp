#include "Unit.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Utils.h"
#include "Config.h"
#include <random>   

// NEW FEATURE:
#include <algorithm> // std::clamp

using namespace std;

Unit::Unit(UnitType type, int x, int y) {
    positionX = x;
    positionY = y;

    switch (type) {
        case UnitType::SOLDIER:
            typeName = "Combatant"; symbol = 'C'; maxHealth = 100;
            maxMovement = 8; minAttack = 8; maxAttack = 14; attackRange = 4;
            break;

        case UnitType::GRENADIER:
            typeName = "Grenadier"; symbol = 'G'; maxHealth = 110;
            maxMovement = 6; minAttack = 12; maxAttack = 23; attackRange = 4;
            break;

        case UnitType::SNIPER:
            typeName = "Sniper"; symbol = 'S'; maxHealth = 80;
            maxMovement = 5; minAttack = 15; maxAttack = 25; attackRange = 8;
            break;

        case UnitType::TANK:
            typeName = "Tank"; symbol = 'T'; maxHealth = 200;
            maxMovement = 6; minAttack = 25; maxAttack = 40; attackRange = 5;
            break;

        case UnitType::HELICOPTER:
            typeName = "Warplane"; symbol = 'W'; maxHealth = 130;
            maxMovement = 15; minAttack = 10; maxAttack = 50; attackRange = 7;
            break;
    }

    health = maxHealth;
    alive = true;
}

void Unit::TakeDamage(int damage) {
    if (!alive) return;
    health -= damage;
    if (health <= 0) {
        health = 0;
        alive = false;
        cout << typeName << " has been destroyed!" << endl;
    }
}

void Unit::Move(int dx, int dy) {
    if (max(abs(dx), abs(dy)) <= maxMovement) {
        positionX += dx;
        positionY += dy;

        //clamp is needed for boundary checks, new feature
        positionX = std::clamp(positionX, 0, Config::MAP_WIDTH - 1);
        positionY = std::clamp(positionY, 0, Config::MAP_HEIGHT - 1);

        cout << typeName << " moved to [" << positionX << ", " << positionY << "]" << endl;
    } else {
        cout << "Target out of movement range! Limit is " << maxMovement << endl;
    }
}

void Unit::Attack(Unit& opponent) {
    
    static thread_local std::mt19937 generator(std::random_device{}());//static for thread safety
    std::uniform_int_distribution<int> distribution(minAttack, maxAttack);

    int distance = max(abs(positionX - opponent.getX()), abs(positionY - opponent.getY()));
    if (distance <= attackRange) {
        int actualDamage = distribution(generator);
        cout << typeName << " attacks enemy " << opponent.getTypeName() << "!" << endl;
        opponent.TakeDamage(actualDamage);
        cout << "Dealt " << actualDamage << " damage. (Potential: " << minAttack << "-" << maxAttack << ")" << endl;
    } else {
        cout << "Enemy out of range! " << typeName << "'s range is " << attackRange << " (Distance: " << distance << ")" << endl;
    }
}

int Unit::getX() const { return positionX; }
int Unit::getY() const { return positionY; }
char Unit::getSymbol() const { return symbol; }
std::string Unit::getTypeName() const { return typeName; }
int Unit::getHealth() const { return health; }
bool Unit::isAlive() const { return alive; }
int Unit::getMaxHealth() const { return maxHealth; }
int Unit::getMaxMovement() const { return maxMovement; }
int Unit::getMinAttack() const { return minAttack; }
int Unit::getMaxAttack() const { return maxAttack; }
int Unit::getAttackRange() const { return attackRange; }
