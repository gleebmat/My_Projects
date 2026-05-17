#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <conio.h>
#include <ctime>
#include <algorithm>
#include <windows.h>
#include <limits> // Required for clearing input streams safely

using namespace std;

// Global Map Dimensions
const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 30;

enum class UnitType { SOLDIER, GRENADIER, SNIPER, TANK, HELICOPTER };

// --- Helper Input Protection Function ---
// Replaces direct 'cin >> int' to prevent crashes when letters are entered
int GetValidInteger() {
    int value;
    while (true) {
        if (cin >> value) {
            return value;
        }
        // If input failed (e.g., user typed a letter)
        cout << "Invalid input! Please enter a valid number: ";
        cin.clear(); // Reset the error flag on the stream
        cin.ignore(10000, '\n'); // Purge the invalid letters out of the buffer
    }
}

class Unit {
private:
    string typeName;
    char symbol;
    int health;
    int maxHealth;
    int positionX, positionY;
    int maxMovement;
    int attackPower;
    int attackRange;
    bool alive{ true };

public:
    Unit(UnitType type, int x, int y) : positionX(x), positionY(y) {
        switch (type) {
            case UnitType::SOLDIER:
                typeName = "Soldier";   symbol = 'S'; maxHealth = 100; maxMovement = 8;  attackPower = 10; attackRange = 2; break;
            case UnitType::GRENADIER:
                typeName = "Grenadier"; symbol = 'G'; maxHealth = 110; maxMovement = 6;  attackPower = 15; attackRange = 4; break;
            case UnitType::SNIPER:
                typeName = "Sniper";    symbol = 'N'; maxHealth = 80;  maxMovement = 5;  attackPower = 19; attackRange = 8; break;
            case UnitType::TANK:
                typeName = "Tank";      symbol = 'T'; maxHealth = 200; maxMovement = 6;  attackPower = 35; attackRange = 5; break;
            case UnitType::HELICOPTER:
                typeName = "Heli";      symbol = 'H'; maxHealth = 130; maxMovement = 15; attackPower = 28; attackRange = 7; break;
        }
        health = maxHealth;
    }

    int getX() const { return positionX; }
    int getY() const { return positionY; }
    char getSymbol() const { return symbol; }
    string getTypeName() const { return typeName; }
    int getHealth() const { return health; }
    bool isAlive() const { return alive; }
    int getMaxHealth() const { return maxHealth; }
    int getMaxMovement() const { return maxMovement; }
    int getAttackPower() const { return attackPower; }
    int getAttackRange() const { return attackRange; }

    void TakeDamage(int damage) {
        if (!alive) return;
        health -= damage;
        if (health <= 0) {
            health = 0;
            alive = false;
            cout << typeName << " has been destroyed!" << endl;
        }
    }

    void Move(int dx, int dy) {
        if (abs(dx) + abs(dy) <= maxMovement) {
            positionX += dx;
            positionY += dy;
            
            // BOUNDARY CHECK: Dynamically bounded to constants
            if (positionX < 0) positionX = 0;   
            if (positionX > MAP_WIDTH - 1) positionX = MAP_WIDTH - 1;
            if (positionY < 0) positionY = 0;   
            if (positionY > MAP_HEIGHT - 1) positionY = MAP_HEIGHT - 1;
            
            cout << typeName << " moved to [" << positionX << ", " << positionY << "]" << endl;
        } else {
            cout << "Target out of movement range! Limit is " << maxMovement << endl;
        }
    }

    void Attack(Unit& opponent) {
        int distance = max(abs(positionX - opponent.getX()), abs(positionY - opponent.getY()));
        if (distance <= attackRange) {
            cout << typeName << " attacks enemy " << opponent.getTypeName() << "!" << endl;
            opponent.TakeDamage(attackPower);
            cout << "Dealt " << attackPower << " damage." << endl;
        } else {
            cout << "Enemy out of range! " << typeName << "'s range is " << attackRange << " (Distance: " << distance << ")" << endl;
        }
    }
};

class Player {
private:
    string name;
    vector<Unit> squad;
    char teamIdentifier; 

public:
    Player(string n, char id) : name(n), teamIdentifier(id) {}

    void AddUnit(UnitType type, int x, int y) {
        squad.push_back(Unit(type, x, y));
    }

    string getName() const { return name; }
    char getId() const { return teamIdentifier; }
    vector<Unit>& getSquad() { return squad; }

    bool hasLivingUnits() {
        for (const auto& unit : squad) {
            if (unit.isAlive()) return true;
        }
        return false;
    }

    void DisplaySquadStatus() {
        cout << "\n========================================= " << name << "'s Squad Status =========================================" << endl;
        for (size_t i = 0; i < squad.size(); ++i) {
            if (squad[i].isAlive()) {
                // Formatting width blocks ensures the pipes '|' stay perfectly parallel vertically
                printf("%d. %-10s | HP: %3d/%3d | Pos: [%2d,%2d] | Max Move: %2d | Atk Power: %2d | Range: %2d\n",
                       (int)(i + 1),
                       squad[i].getTypeName().c_str(),
                       squad[i].getHealth(),
                       squad[i].getMaxHealth(),
                       squad[i].getX(),
                       squad[i].getY(),
                       squad[i].getMaxMovement(),
                       squad[i].getAttackPower(),
                       squad[i].getAttackRange());
            } else {
                printf("%d. %-10s | [DEAD]\n", (int)(i + 1), squad[i].getTypeName().c_str());
            }
        }
        cout << "=================================================================================================================" << endl;
    }
};

void DrawMap(Player& p1, Player& p2) {
    // 1. Render Top Border
    cout << "\n   ┌";
    for (int x = 0; x < MAP_WIDTH; x++) cout << "───";
    cout << "┐\n";
    
    // 2. Render Grid Rows
    for (int y = MAP_HEIGHT - 1; y >= 0; y--) {
        printf("%2d │", y); // Y-axis row indicator

        for (int x = 0; x < MAP_WIDTH; x++) {
            char cellChar = ' '; // Default empty space inside the cell slot

            // Search Player 1
            for (auto& u : p1.getSquad()) {
                if (u.isAlive() && u.getX() == x && u.getY() == y) {
                    cellChar = u.getSymbol(); 
                    break;
                }
            }
            // Search Player 2 if slot is still empty
            if (cellChar == ' ') {
                for (auto& u : p2.getSquad()) {
                    if (u.isAlive() && u.getX() == x && u.getY() == y) {
                        cellChar = tolower(u.getSymbol()); 
                        break;
                    }
                }
            }

            // This outputs the clean individual cellular slot: | | or |S|
            cout << " " << cellChar << "│";
        }
        cout << "\n";
    }

    // 3. Render Bottom Border
    cout << "   └";
    for (int x = 0; x < MAP_WIDTH; x++) cout << "───";
    cout << "┘\n";

    // 4. Render X-Axis Directional Pointer (---------->x)
    cout << "    ";
    for (int x = 0; x < MAP_WIDTH - 1; x++) cout << "───";
    cout << "──────► X\n";

    // 5. Render X-Axis Number Ticks
    cout << "     ";
    for (int x = 0; x < MAP_WIDTH; x++) {
        if (x % 5 == 0) printf("%-3d", x);
        else cout << "   ";
    }
    cout << "\n";
}


void ConfigureConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, 0);

    // Provide buffer headroom proportional to your dimensions
    COORD bufferSize = { (short)(MAP_WIDTH + 20), (short)(MAP_HEIGHT + 30) };
    SetConsoleScreenBufferSize(hConsole, bufferSize);
}

void ClearScreen() {
    cout << "\033[2J\033[H";
}

bool IsTileOccupied(int x, int y, Player& p1, Player& p2) {
    for (const auto& u : p1.getSquad()) {
        if (u.isAlive() && u.getX() == x && u.getY() == y) return true;
    }
    for (const auto& u : p2.getSquad()) {
        if (u.isAlive() && u.getX() == x && u.getY() == y) return true;
    }
    return false;
}

void ExecuteUnitAction(Unit& unit, Player& activePlayer, Player& enemyPlayer) {
    cout << "\nActing with: " << unit.getTypeName() << " [" << unit.getX() << ":" << unit.getY() << "]" << endl;
    cout << "1. Move\n2. Attack\nChoice: ";
    
    int action = GetValidInteger(); // Protected input

    if (action == 1) {
        cout << "Enter relative X displacement (dx): ";  int dx = GetValidInteger();
        cout << "Enter relative Y displacement (dy): ";  int dy = GetValidInteger();
        
        int targetX = unit.getX() + dx;
        int targetY = unit.getY() + dy;

        // BOUNDARY CHECK: Replaced hardcoded '99' with constants
        if (targetX < 0) targetX = 0; 
        if (targetX > MAP_WIDTH - 1) targetX = MAP_WIDTH - 1;
        if (targetY < 0) targetY = 0; 
        if (targetY > MAP_HEIGHT - 1) targetY = MAP_HEIGHT - 1;

        if (IsTileOccupied(targetX, targetY, activePlayer, enemyPlayer)) {
            cout << "Movement Blocked! The target coordinates [" << targetX << ", " << targetY << "] are already occupied!" << endl;
        } else {
            unit.Move(dx, dy);
        }
    } 
    else if (action == 2) {
        enemyPlayer.DisplaySquadStatus();
        cout << "Select enemy unit index to target: ";
        
        int targetIdx = GetValidInteger(); // Protected input
        targetIdx--; 

        if (targetIdx >= 0 && targetIdx < (int)enemyPlayer.getSquad().size() && enemyPlayer.getSquad()[targetIdx].isAlive()) {
            unit.Attack(enemyPlayer.getSquad()[targetIdx]);
        } else {
            cout << "Invalid or dead target! Turn action wasted." << endl;
        }
    } else {
        cout << "Invalid action. Unit stays idle." << endl;
    }
}

void PlayTurn(Player& activePlayer, Player& enemyPlayer) {
    if (!activePlayer.hasLivingUnits()) return;

    cout << "\n>>>>>> TURN: " << activePlayer.getName() << " <<<<<<" << endl;
    
    int actionsPerformed = 0;
    int chosenIndices[2] = {-1, -1};

    while (actionsPerformed < 2) {
        activePlayer.DisplaySquadStatus();
        cout << "Select unit [" << actionsPerformed + 1 << "/2] to command: ";
        
        int choice = GetValidInteger(); // Protected input
        choice--; 

        if (choice >= 0 && choice < (int)activePlayer.getSquad().size()) {
            Unit& chosenUnit = activePlayer.getSquad()[choice];
            
            if (!chosenUnit.isAlive()) {
                cout << "That unit is destroyed! Choose another." << endl;
                continue;
            }
            if (choice == chosenIndices[0]) {
                cout << "This unit already acted this turn! Choose a different one." << endl;
                continue;
            }

            ExecuteUnitAction(chosenUnit, activePlayer, enemyPlayer);
            chosenIndices[actionsPerformed] = choice;
            actionsPerformed++;
        } else {
            cout << "Invalid unit choice." << endl;
        }
    }
}

int main() {
    ConfigureConsole();
    srand(time(0));
    string name1, name2;
    cout << "Enter Player 1 Name: "; cin >> name1;
    cout << "Enter Player 2 Name: "; cin >> name2;

    Player pA(name1, 'A');
    Player pB(name2, 'B');

    UnitType types[] = {UnitType::SOLDIER, UnitType::GRENADIER, UnitType::SNIPER, UnitType::TANK, UnitType::HELICOPTER};
    
    // Calculates horizontal spawn bandwidth proportionally (20% of your current width limit)
    int spawnWidthZone = MAP_WIDTH / 5;
    if (spawnWidthZone < 1) spawnWidthZone = 1;

    for (int i = 0; i < 5; i++) {
        // BOUNDARY CHECK: Replaced old hardcoded 20 and 100 boundaries
        pA.AddUnit(types[i], rand() % spawnWidthZone, rand() % MAP_HEIGHT);       
        pB.AddUnit(types[i], (MAP_WIDTH - spawnWidthZone) + (rand() % spawnWidthZone), rand() % MAP_HEIGHT); 
    }

    ClearScreen();

    while (pA.hasLivingUnits() && pB.hasLivingUnits()) {
        DrawMap(pA, pB);
        PlayTurn(pA, pB);
        cout << "\nPress any key to pass turn to next player...";
        _getch();
        ClearScreen();

        if (!pB.hasLivingUnits()) break;

        DrawMap(pA, pB);
        PlayTurn(pB, pA);
        cout << "\nPress any key to pass turn to next player...";
        _getch();
        ClearScreen();
    }

    cout << "\nGAME OVER!" << endl;
    if (pA.hasLivingUnits()) cout << "The winner is: " << pA.getName() << "!" << endl;
    else cout << "The winner is: " << pB.getName() << "!" << endl;

    return 0;
}