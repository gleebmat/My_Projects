#include "Player.h"
#include "Unit.h"
#include <iostream>
#include <algorithm>

#include <ranges>  // ranges::any_of, ranges::count_if

using namespace std;

Player::Player(string n, char id) : name(std::move(n)), teamIdentifier(id) {}//name is a temporary object, which is moved into the Player object

void Player::AddUnit(UnitType type, int x, int y) {
    squad.push_back(Unit(type, x, y));
}

std::string Player::getName() const { return name; }
char Player::getId() const { return teamIdentifier; }
const std::vector<Unit>& Player::getSquad() const { return squad; }
std::vector<Unit>& Player::getSquad() { return squad; }

bool Player::hasLivingUnits() {
    
    return std::ranges::any_of(
        squad,
        [](const Unit& u) { return u.isAlive(); }
    );
}

int Player::getLivingUnitCount() const {
   
    return static_cast<int>(std::ranges::count_if(
        squad,
        [](const Unit& u) { return u.isAlive(); }
    ));
}

void Player::DisplaySquadStatus() {
    cout << "\n========================================= " << name << "'s Squad Status =========================================" << endl;
    for (size_t i = 0; i < squad.size(); ++i) {
        if (squad[i].isAlive()) {
            printf("%d. %-10s | HP: %3d/%3d | Pos: [%2d,%2d] | Max Move: %2d | Atk: %2d-%-2d | Range: %2d\n",
                   (int)(i + 1),
                   squad[i].getTypeName().c_str(),
                   squad[i].getHealth(),
                   squad[i].getMaxHealth(),
                   squad[i].getX(),
                   squad[i].getY(),
                   squad[i].getMaxMovement(),
                   squad[i].getMinAttack(),
                   squad[i].getMaxAttack(),
                   squad[i].getAttackRange());
        } else {
            printf("%d. %-10s | [DEAD]\n", (int)(i + 1), squad[i].getTypeName().c_str());
        }
    }
    cout << "=================================================================================================================" << endl;
}
