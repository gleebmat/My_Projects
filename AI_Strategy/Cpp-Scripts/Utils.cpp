#include <iostream>
#include <string>
#include "Unit.h"
#include "Player.h"
#include "Utils.h"
#include "Config.h"
#include <windows.h>
#include <limits>      // for numeric_limits
#include <algorithm>   // for std::clamp
#include <ranges>      // ranges/views
#include <optional>    //  std::optional

using namespace std;

int Utils::GetValidInteger() {
    int value;
    while (true) {
        if (cin >> value) {
            return value;
        }
        cout << "Invalid input! Please enter a valid number: ";
        cin.clear();
        //use numeric_limits instead of magic number
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//this will purge the invalid letters out of the buffer
    }
}

void Utils::ClearScreen() {
    cout << "\33[2J\033[H";//This ANSI escape code sequence clears the console screen and moves the cursor to the top-left corner
}

void Utils::ConfigureConsole() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
}

bool Utils::IsTileOccupied(int x, int y, Player& p1, Player& p2) {
    //ranges + lambdas to check occupancy
    auto occupied_at = [x, y](const auto& squad) {
        return std::ranges::any_of(
            squad,
            [x, y](const Unit& u) {
                return u.isAlive() && u.getX() == x && u.getY() == y;
            }
        );
    };

    return occupied_at(p1.getSquad()) || occupied_at(p2.getSquad());
}

void Utils::DrawMap(Player& p1, Player& p2) {
    cout << "\n    ==== BATTLE FIELD ====" << endl;
    cout << "  Y ^ " << endl;

    //ranges::views::iota + reverse for Y loop
    for (int y : std::views::iota(0, Config::MAP_HEIGHT) | std::views::reverse) {//ioto generates a sequence of integers from 0 to MAP_HEIGHT
        printf("%2d |", y);

        for (int x = 0; x < Config::MAP_WIDTH; x++) {
            //std::optional<char> to represent “no unit”
            std::optional<char> cellChar;//neede for units which can appear on the map

            //small lambda to search a squad
            auto find_unit_symbol = [x, y](const auto& squad, bool lower) -> std::optional<char> {
                for (const auto& u : squad) {
                    if (u.isAlive() && u.getX() == x && u.getY() == y) {
                        char c = u.getSymbol();
                        return lower ? static_cast<char>(std::tolower(c)) : c;
                    }
                }
                return std::nullopt;
            };

            if (auto s = find_unit_symbol(p1.getSquad(), false)) {
                cellChar = *s;
            } else if (auto s = find_unit_symbol(p2.getSquad(), true)) {
                cellChar = *s;
            }

            if (cellChar.has_value()) {
                cout << *cellChar << "|";
            } else {
                cout << " |";
            }
        }
        cout << endl;
    }

    cout << "    ";
    for (int i = 0; i < Config::MAP_WIDTH; i++) {
        cout << "--";
    }
    cout << "---> X" << endl;
    cout << "\n    (UPPERCASE: " << p1.getName() << " | lowercase: " << p2.getName() << ")" << endl;
}

void Utils::ExecuteUnitAction(Unit& unit, Player& activePlayer, Player& enemyPlayer) {
    cout << "\nActing with: " << unit.getTypeName() << " [" << unit.getX() << ":" << unit.getY() << "]" << endl;
    cout << "1. Move\n2. Attack\nChoice: ";

    int action = GetValidInteger();

    if (action == 1) {
        cout << "Enter relative X displacement (dx): ";  int dx = GetValidInteger();
        cout << "Enter relative Y displacement (dy): ";  int dy = GetValidInteger();

        int targetX = unit.getX() + dx;
        int targetY = unit.getY() + dy;

        //std::clamp for bounds
        targetX = std::clamp(targetX, 0, Config::MAP_WIDTH - 1);
        targetY = std::clamp(targetY, 0, Config::MAP_HEIGHT - 1);

        if (IsTileOccupied(targetX, targetY, activePlayer, enemyPlayer)) {
            cout << "Movement Blocked! The target coordinates [" << targetX << ", " << targetY << "] are already occupied!" << endl;
        } else {
            unit.Move(dx, dy);
        }
    }
    else if (action == 2) {
        vector<int> validTargets = GetUnitsInAttackRange(unit, enemyPlayer);

        if (validTargets.empty()) {
            cout << "No enemies are within attack range!" << endl;
            return;
        }

        cout << "\n=== ENEMIES IN RANGE ===\n";
        for (int idx : validTargets) {
            Unit& enemy = enemyPlayer.getSquad()[idx];
            int distance = max(abs(unit.getX() - enemy.getX()), abs(unit.getY() - enemy.getY()));
            cout << idx + 1 << ". " << enemy.getTypeName()
                 << " | HP: " << enemy.getHealth()
                 << " | Pos: [" << enemy.getX() << ", " << enemy.getY() << "]"
                 << " | Distance: " << distance << endl;
        }

        cout << "\nSelect enemy unit index to target: ";
        int targetIdx = GetValidInteger();
        targetIdx--;

        //ranges::any_of to validate choice
        bool validChoice = std::ranges::any_of(
            validTargets,
            [targetIdx](int idx) { return idx == targetIdx; }
        );

        if (validChoice) {
            unit.Attack(enemyPlayer.getSquad()[targetIdx]);
        } else {
            cout << "Target is not within attack range!" << endl;
        }
    } else {
        cout << "Invalid action. Unit stays idle." << endl;
    }
}

vector<int> Utils::GetAttackableEnemyIndices(Unit& attacker, Player& enemyPlayer) {
    vector<int> attackableTargets;

    //ranges::views::iota to iterate indices
    auto& squad = enemyPlayer.getSquad();
    for (int i : std::views::iota(0, static_cast<int>(squad.size()))) {
        Unit& enemy = squad[static_cast<size_t>(i)];
        if (!enemy.isAlive()) continue;

        int distance = max(
            abs(attacker.getX() - enemy.getX()),
            abs(attacker.getY() - enemy.getY())
        );
        if (distance <= attacker.getAttackRange()) {
            attackableTargets.push_back(i + 1); // keep original +1 behavior
        }
    }
    return attackableTargets;
}

std::vector<int> Utils::GetUnitsInAttackRange(Unit& attacker, Player& enemyPlayer) {
    vector<int> validTargets;

    auto& squad = enemyPlayer.getSquad();
    //same ranges::views::iota pattern
    for (int i : std::views::iota(0, static_cast<int>(squad.size()))) {
        Unit& enemy = squad[static_cast<size_t>(i)];
        if (!enemy.isAlive()) continue;

        int distance = max(
            abs(attacker.getX() - enemy.getX()),
            abs(attacker.getY() - enemy.getY())
        );
        if (distance <= attacker.getAttackRange()) {
            validTargets.push_back(i); // 0-based indices
        }
    }
    return validTargets;
}

void Utils::PlayTurn(Player& activePlayer, Player& enemyPlayer) {
    if (!activePlayer.hasLivingUnits()) return;
    Utils::ClearScreen();
    DrawMap(activePlayer, enemyPlayer);
    cout << "\n>>>>>> TURN: " << activePlayer.getName() << " <<<<<<" << endl;

    int actionsPerformed = 0;
    int chosenIndices[2] = { -1, -1 };

    int livingCount = activePlayer.getLivingUnitCount();

    while (actionsPerformed < 2) {
        activePlayer.DisplaySquadStatus();
        cout << "Select unit [" << actionsPerformed + 1 << "/2] to command: ";

        int choice = GetValidInteger();
        choice--;

        auto& squad = activePlayer.getSquad();
        if (choice >= 0 && choice < (int)squad.size()) {
            Unit& chosenUnit = squad[choice];

            if (!chosenUnit.isAlive()) {
                cout << "That unit is destroyed! Choose another." << endl;
                continue;
            }

            if (choice == chosenIndices[0] && livingCount > 1) {
                cout << "This unit already acted this turn! Choose a different one." << endl;
                continue;
            }

            ExecuteUnitAction(chosenUnit, activePlayer, enemyPlayer);
            chosenIndices[actionsPerformed] = choice;
            actionsPerformed++;
        } else {
            cout << "Invalid unit choice." << endl;
        }
        ClearScreen();
        DrawMap(activePlayer, enemyPlayer);
    }
}
