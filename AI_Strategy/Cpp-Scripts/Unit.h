#pragma once
#include <string>

enum class UnitType { SOLDIER, GRENADIER, SNIPER, TANK, HELICOPTER };//defines the different types of units as constants

class Unit {
private:
    std::string typeName;
    char symbol;
    int health, maxHealth;
    int positionX, positionY;
    int maxMovement;
    int minAttack;
    int maxAttack;
    int attackRange;
    bool alive;

public:
    Unit(UnitType type, int x, int y);

    int getX() const;
    int getY() const;
    char getSymbol() const;
    std::string getTypeName() const;
    int getHealth() const;
    bool isAlive() const;

    int getMaxHealth() const;
    int getMaxMovement() const;
    int getMinAttack() const;
    int getMaxAttack() const;
    int getAttackRange() const;

    void Move(int dx, int dy);
    void Attack(Unit& opponent);
    void TakeDamage(int damage);
};

