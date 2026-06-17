#pragma once
#include "Unit.h"
#include <vector>

class Player {
private:
    std::string name;
    std::vector<Unit> squad;
    char teamIdentifier;


public:
    Player(std::string n, char id);
    void AddUnit(UnitType type, int x, int y);
    std::string getName() const;
    char getId() const;
    std::vector<Unit>& getSquad();
    const std::vector<Unit>& getSquad() const;
    bool hasLivingUnits();
    int getLivingUnitCount() const;
    void DisplaySquadStatus();
};