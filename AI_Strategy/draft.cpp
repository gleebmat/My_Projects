#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <conio.h>
#include <ctime>
#include <algorithm>
#include <windows.h>
#include <limits> 
#include <fstream>
#include <cstdlib> 
//STOPPED ON GET VALID INTEGER INTO UTILS.CPP
using namespace std;

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 30;

// Global Map Dimensions
void ConfigureConsole() {
    // Get the handle to the current console window
    HWND hwnd = GetConsoleWindow();
    
    // Force the window to open maximized
    ShowWindow(hwnd, SW_MAXIMIZE);
}
enum class UnitType { SOLDIER, GRENADIER, SNIPER, TANK, HELICOPTER };//enumeration as a strict type for unit types, improving code readability and safety

// --- Helper Input Protection Function ---
// Replaces direct 'cin >> int' to prevent crashes when letters are entered
int GetValidInteger() {
    int value;
    while (true) {
        if (cin >> value) {//returns true if an integer was successfully read or false if the input was invalid (e.g., a letter)
            return value;
        }
        // If input failed (e.g., user typed a letter)
        cout << "Invalid input! Please enter a valid number: ";
        cin.clear(); // Reset the error flag on the stream of the cin object
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
    int minAttack;  
    int maxAttack;   
    int attackRange;
    bool alive{ true };

public:
    Unit(UnitType type, int x, int y) : positionX(x), positionY(y) {//constructor initializes unit attributes based on the provided UnitType and starting coordinates
        switch (type) {
            case UnitType::SOLDIER:
                typeName = "Combatant";   symbol = 'C'; maxHealth = 100; maxMovement = 8;  minAttack = 8;  maxAttack = 12; attackRange = 4; break;
            case UnitType::GRENADIER:
                typeName = "Grenadier"; symbol = 'G'; maxHealth = 110; maxMovement = 6;  minAttack = 12; maxAttack = 18; attackRange = 4; break;
            case UnitType::SNIPER:
                typeName = "Sniper";    symbol = 'S'; maxHealth = 80;  maxMovement = 5;  minAttack = 15; maxAttack = 25; attackRange = 8; break;
            case UnitType::TANK:
                typeName = "Tank";      symbol = 'T'; maxHealth = 200; maxMovement = 6;  minAttack = 30; maxAttack = 40; attackRange = 5; break;
            case UnitType::HELICOPTER:
                typeName = "Warplane";      symbol = 'W'; maxHealth = 130; maxMovement = 15; minAttack = 22; maxAttack = 34; attackRange = 7; break;
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
    int getMinAttack() const { return minAttack; } 
    int getMaxAttack() const { return maxAttack; } 
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
        // Now we use Chebyshev Distance exactly like the attack range calculations. max(abs(dx), abs(dy)) <= maxMovement 
        if (max(abs(dx), abs(dy)) <= maxMovement) {
            positionX += dx;
            positionY += dy;
            
            // BOUNDARY CHECK
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
            // Calculate random damage between minAttack and maxAttack (inclusive)
            int actualDamage = minAttack + (rand() % (maxAttack - minAttack + 1));
            
            cout << typeName << " attacks enemy " << opponent.getTypeName() << "!" << endl;
            opponent.TakeDamage(actualDamage);
            cout << "Dealt " << actualDamage << " damage. (Potential: " << minAttack << "-" << maxAttack << ")" << endl;
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

    void AddUnit(UnitType type, int x, int y) {//Adds a new unit of the specified type and starting coordinates to the player's squad
        squad.push_back(Unit(type, x, y));//creates a new Unit object using the provided type and coordinates, and appends it to the squad vector
    }

    string getName() const { return name; }
    char getId() const { return teamIdentifier; }
    const vector<Unit>& getSquad() const { return squad; }//Returns a constant reference to the player's squad

    vector<Unit>& getSquad() { return squad; }//Overloaded version to allow modification of the squad when needed (e.g., for attacks)

    bool hasLivingUnits() {
        for (const auto& unit : squad) {
            if (unit.isAlive()) return true;
        }
        return false;
    }
    int getLivingUnitCount() const {//we will use the function to chechk how many units left (if the player allowed to act with the same unit twice in a turn or not)
        int count = 0;
        for (const auto& unit : squad) {
            if (unit.isAlive()) count++;
        }
        return count;
    }
    void DisplaySquadStatus() {
        cout << "\n========================================= " << name << "'s Squad Status =========================================" << endl;
        for (size_t i = 0; i < squad.size(); ++i) {
            if (squad[i].isAlive()) {
                printf("%d. %-10s | HP: %3d/%3d | Pos: [%2d,%2d] | Max Move: %2d | Atk: %2d-%-2d | Range: %2d\n",
                    //%d - prints the unit index (starting from 1 for user friendliness)
                    //%-10s - prints the unit type left-aligned in a 10-character wide field
                    //HP: %3d/%3d - prints current HP and max HP in a format like " 80/100"
                    //Pos: [%2d,%2d] - prints the unit's X and Y coordinates in a format like "[ 5, 10]"
                    //Max Move: %2d - prints the unit's maximum movement range
                    //Atk: %2d-%-2d - prints the unit's minimum and maximum
                    //attack damage in a format like " 8-12" 
                       (int)(i + 1),// Unit index for display (1-based)
                       squad[i].getTypeName().c_str(),//c_str() converts the C++ string to a C-style string for printf
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
};

vector<int> GetAttackableEnemyIndices(Unit& attacker, Player& enemyPlayer) {//Returns a vector of indices corresponding to enemy units that are within the attack range

    vector<int> attackableTargets;//This vector will hold the indices of enemy units that are valid targets for the attacker's current position and attack range
    for (size_t i = 0; i < enemyPlayer.getSquad().size(); i++) {
        Unit& enemy = enemyPlayer.getSquad()[i];
        if (!enemy.isAlive()) {
            continue;
        }
        int distance = max(
            abs(attacker.getX() - enemy.getX()),
            abs(attacker.getY() - enemy.getY())
        );
        if (distance <= attacker.getAttackRange()) {
            attackableTargets.push_back((int)i + 1);
        }
    }
    return attackableTargets;

}//this function for the second check later to show the attackable targets in the UI with their indices starting from 1 for user-friendliness 

vector<int> GetUnitsInAttackRange(Unit& attacker, Player& enemyPlayer) {//For the first check later, without the +1 to indices
    vector<int> validTargets;
    for (size_t i = 0; i < enemyPlayer.getSquad().size(); i++) {
        Unit& enemy = enemyPlayer.getSquad()[i];
        if (!enemy.isAlive()) {
            continue;
        }
        int distance = max(
            abs(attacker.getX() - enemy.getX()),
            abs(attacker.getY() - enemy.getY())
        );
        if (distance <= attacker.getAttackRange()) {
            validTargets.push_back((int)i);
        }
    }
    return validTargets;
}

void DrawMap(Player& p1, Player& p2) {
    cout << "\n    ==== BATTLE FIELD ====" << endl;
    cout << "  Y ^ " << endl;

    for (int y = MAP_HEIGHT - 1; y >= 0; y--) {
        printf("%2d |", y);

        for (int x = 0; x < MAP_WIDTH; x++) {
            char cellChar = ' ';

            for (const auto& u : p1.getSquad()) {
                if (u.isAlive() && u.getX() == x && u.getY() == y) {
                    cellChar = u.getSymbol(); 
                    break;
                }
            }

            if (cellChar == ' ') {
                for (const auto& u : p2.getSquad()) {
                    if (u.isAlive() && u.getX() == x && u.getY() == y) {
                        cellChar = tolower(u.getSymbol()); 
                        break;
                    }
                }
            }

            if (cellChar != ' ') {
                cout << cellChar << "|";
            } else {
                cout << " |";
            }
        }
        cout << endl;
    }

    cout << "    ";
    for (int i = 0; i < MAP_WIDTH; i++) {
        cout << "--";
    }
    cout << "---> X" << endl;
    cout << "\n    (UPPERCASE: " << p1.getName() << " | lowercase: " << p2.getName() << ")" << endl;
}

void ClearScreen() {
    cout << "\033[2J\033[H";//This ANSI escape code sequence clears the console screen and moves the cursor to the top-left corner. 

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
    
    int action = GetValidInteger(); 

    if (action == 1) {
        cout << "Enter relative X displacement (dx): ";  int dx = GetValidInteger();
        cout << "Enter relative Y displacement (dy): ";  int dy = GetValidInteger();
        
        int targetX = unit.getX() + dx;
        int targetY = unit.getY() + dy;

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
        vector<int> validTargets = GetUnitsInAttackRange(unit, enemyPlayer);

        if (validTargets.empty()) {
            cout << "No enemies are within attack range!" << endl;
            return;
        }

        cout << "\n=== ENEMIES IN RANGE ===\n";
        for (int idx : validTargets) {
            Unit& enemy = enemyPlayer.getSquad()[idx];
            int distance = max(abs(unit.getX() - enemy.getX()), abs(unit.getY() - enemy.getY()));
            cout << idx + 1 << ". " << enemy.getTypeName() << " | HP: " << enemy.getHealth() << " | Pos: [" << enemy.getX() << ", " << enemy.getY() << "] | Distance: " << distance << endl;
        }

        cout << "\nSelect enemy unit index to target: ";
        int targetIdx = GetValidInteger();
        targetIdx--;

        bool validChoice = false;
        for (int idx : validTargets) {
            if (idx == targetIdx) {
                validChoice = true;
                break;
            }
        }

        if (validChoice) {
            unit.Attack(enemyPlayer.getSquad()[targetIdx]);
        } else {
            cout << "Target is not within attack range!" << endl;
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
    
    // Get the number of living units at the start of the turn
    int livingCount = activePlayer.getLivingUnitCount(); 

    while (actionsPerformed < 2) {
        activePlayer.DisplaySquadStatus();
        cout << "Select unit [" << actionsPerformed + 1 << "/2] to command: ";
        
        int choice = GetValidInteger(); 
        choice--; 

        if (choice >= 0 && choice < (int)activePlayer.getSquad().size()) {
            Unit& chosenUnit = activePlayer.getSquad()[choice];
            
            if (!chosenUnit.isAlive()) {
                cout << "That unit is destroyed! Choose another." << endl;
                continue;
            }
            
            // Bypass the restriction if the player only has 1 living unit left
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
        activePlayer.DisplaySquadStatus();
    }
}
void CallOpenAIEngine(Player& firstPlayer, Player& secondPlayer, int actionNum, int actionChosenIdx0) {//actionChosenIdx0 is the index of the first chosen unit in the turn, if the player has only 1 living unit left, it will be -1 and the AI can choose the same unit for both actions
    ofstream stateFile("game_state.json");//Opens or creates a file named "game_state.json" for writing. 

    
    stateFile << "{\n";
    stateFile << "  \"map_width\": " << MAP_WIDTH << ",\n";
    stateFile << "  \"map_height\": " << MAP_HEIGHT << ",\n";
    stateFile << "  \"action_number\": " << actionNum << ",\n";
    // In order to write it into the database we need to know the name of the AI-Player
    stateFile << "  \"acting_team\": \"" << firstPlayer.getName() << "\",\n"; 
    
    stateFile << "  \"ai_units\": [\n";
    for (size_t i = 0; i < firstPlayer.getSquad().size(); ++i) {
        Unit& u = firstPlayer.getSquad()[i];
        bool canAct = u.isAlive() && ((int)i != actionChosenIdx0);//check whether this unit acted already in the turn (if the player has more than 1 living unit left) 
        vector<int> attackableTargets = GetAttackableEnemyIndices(u, secondPlayer);

        stateFile << "    {\n";
        stateFile << "      \"index\": " << i + 1 << ",\n";
        stateFile << "      \"type\": \"" << u.getTypeName() << "\",\n";
        stateFile << "      \"x\": " << u.getX() << ",\n";
        stateFile << "      \"y\": " << u.getY() << ",\n";
        stateFile << "      \"hp\": " << u.getHealth() << ",\n";
        stateFile << "      \"max_move\": " << u.getMaxMovement() << ",\n";
        stateFile << "      \"range\": " << u.getAttackRange() << ",\n";
        stateFile << "      \"can_act\": " << (canAct ? "true" : "false") << ",\n";
        
        stateFile << "      \"attackable_targets\": [";
        for (size_t j = 0; j < attackableTargets.size(); j++) {
            stateFile << attackableTargets[j];
            if (j < attackableTargets.size() - 1) stateFile << ", ";
        }
        stateFile << "]\n";
        stateFile << "    }";
        if (i < firstPlayer.getSquad().size() - 1) stateFile << ",\n";
    } 
    stateFile << "\n  ],\n";

    stateFile << "  \"human_units\": [\n";
    for (size_t i = 0; i < secondPlayer.getSquad().size(); ++i) {
        Unit& u = secondPlayer.getSquad()[i];
        vector<int> attackableTargets = GetAttackableEnemyIndices(u, firstPlayer);

        stateFile << "    {\n";
        stateFile << "      \"index\": " << i + 1 << ",\n";
        stateFile << "      \"type\": \"" << u.getTypeName() << "\",\n";
        stateFile << "      \"x\": " << u.getX() << ",\n";
        stateFile << "      \"y\": " << u.getY() << ",\n";
        stateFile << "      \"hp\": " << u.getHealth() << ",\n";
        stateFile << "      \"alive\": " << (u.isAlive() ? "true" : "false") << ",\n";
        
        stateFile << "      \"attackable_targets\": [";
        for (size_t j = 0; j < attackableTargets.size(); j++) {
            stateFile << attackableTargets[j];
            if (j < attackableTargets.size() - 1) stateFile << ", ";
        }
        stateFile << "]\n";
        stateFile << "    }";
        if (i < secondPlayer.getSquad().size() - 1) stateFile << ",\n";
    }
    stateFile << "\n  ]\n";
    stateFile << "}";
    stateFile.close();

    system(".venv\\Scripts\\python.exe openai_parsing.py");
}
void PlayOpenAITurn(Player& aiPlayer, Player& enemyPlayer, int turnNum) {
    if (!aiPlayer.hasLivingUnits()) return;

    cout << "\n>>>>>> OpenAI AGENT TURN: " << aiPlayer.getName() << " <<<<<<" << endl;

    CallOpenAIEngine(aiPlayer, enemyPlayer, turnNum, -1);

    ifstream actionFile("ai_action.json");
    if (!actionFile.is_open()) {
        cout << "AI Action file missing!" << endl;
        return;
    }

    string jsonContent((istreambuf_iterator<char>(actionFile)), istreambuf_iterator<char>());//This line reads the entire contents of the "ai_action.json" file into a single string variable named jsonContent.
    actionFile.close();

    vector<int> unitIndices;
    vector<string> actionTypes;
    vector<int> dxs;
    vector<int> dys;
    vector<int> targetIndices;

    size_t pos = 0;

    while ((pos = jsonContent.find("\"unit_index\"", pos)) != string::npos) {// a loop that searches through the jsonContent string for occurrences of the substring "\"unit_index\"". Each time it finds this substring, it extracts the relevant action information 
        int unitIdx = -1;
        int dx = 0;
        int dy = 0;
        int targetIdx = -1;
        string actionType = "";

        size_t colonPos = jsonContent.find(":", pos);//This line searches for the first occurrence of the colon character ":" starting from the position pos in the jsonContent string. The colon is expected to be after the "unit_index" key, separating it from its value.
        if (colonPos != string::npos) {//checks if the colon was found successfully. If it was found, it proceeds to extract the unit index value.
            unitIdx = stoi(jsonContent.substr(colonPos + 1));//This line extracts the substring starting from one character after the colon position to the end of the string (or until the next comma or closing brace, depending
        }

        size_t actionPos = jsonContent.find("\"action_type\"", pos);
        if (actionPos != string::npos) {
            size_t firstQuote = jsonContent.find("\"", actionPos + 15);//This line searches for the first occurrence of the double quote character "\"" starting from the position actionPos + 15 in the jsonContent string. The number 15 is used to skip past the length of the key "\"action_type\"" and any following characters (like ": ").
            size_t secondQuote = jsonContent.find("\"", firstQuote + 1);//This line searches for the next occurrence of the double quote character "\"" starting from one character after the position of the first quote found in the previous line. This is intended to find the closing quote of the action type value.
            actionType = jsonContent.substr(firstQuote + 1, secondQuote - firstQuote - 1);// This effectively captures the string value of the action type without the surrounding quotes
        }

        size_t dxPos = jsonContent.find("\"dx\"", pos);//pretty much the same logic as the unit index extraction, but for the "dx" value
        if (dxPos != string::npos) {
            size_t dxColon = jsonContent.find(":", dxPos);
            dx = stoi(jsonContent.substr(dxColon + 1));
        }

        size_t dyPos = jsonContent.find("\"dy\"", pos);
        if (dyPos != string::npos) {
            size_t dyColon = jsonContent.find(":", dyPos);
            dy = stoi(jsonContent.substr(dyColon + 1));
        }

        size_t targetPos = jsonContent.find("\"target_index\"", pos);
        if (targetPos != string::npos) {
            size_t targetColon = jsonContent.find(":", targetPos);
            targetIdx = stoi(jsonContent.substr(targetColon + 1));
        }

        unitIndices.push_back(unitIdx - 1);//We store unitIdx - 1 because the AI sends indices starting from 1 for user-friendliness
        actionTypes.push_back(actionType);//We store the action type as a string ("move" or "attack") for later processing
        dxs.push_back(dx);
        dys.push_back(dy);
        targetIndices.push_back(targetIdx - 1);//We store targetIdx - 1 for the same reason as unitIdx - 1, to convert from 1-based to 0-based indexing

        pos += 20;//Move the search position forward to look for the next action in the JSON content. The number 20 is arbitrary but should be large enough to move past the current action's data and find the next "unit_index" key for the following action.
    }

    for (size_t i = 0; i < unitIndices.size(); i++) {
        int unitIdx = unitIndices[i];
        if (unitIdx < 0 || unitIdx >= (int)aiPlayer.getSquad().size()) {
            cout << "Invalid AI unit index." << endl;
            continue;
        }

        Unit& chosenUnit = aiPlayer.getSquad()[unitIdx];
        if (!chosenUnit.isAlive()) {
            cout << "AI selected dead unit." << endl;
            continue;
        }

        string actionType = actionTypes[i];

        if (actionType == "move") {
            int dx = dxs[i];
            int dy = dys[i];

            if (max(abs(dx), abs(dy)) > chosenUnit.getMaxMovement()) {
                cout << "Illegal AI movement distance." << endl;
                continue;
            }

            int targetX = chosenUnit.getX() + dx;
            int targetY = chosenUnit.getY() + dy;

            if (targetX < 0) targetX = 0;
            if (targetX >= MAP_WIDTH) targetX = MAP_WIDTH - 1;
            if (targetY < 0) targetY = 0;
            if (targetY >= MAP_HEIGHT) targetY = MAP_HEIGHT - 1;

            if (IsTileOccupied(targetX, targetY, aiPlayer, enemyPlayer)) {
                cout << "AI attempted occupied tile move." << endl;
                continue;
            }

            chosenUnit.Move(dx, dy);
        }
        else if (actionType == "attack") {
            int targetIdx = targetIndices[i];
            if (targetIdx >= 0 && targetIdx < (int)enemyPlayer.getSquad().size() && enemyPlayer.getSquad()[targetIdx].isAlive()) {
                chosenUnit.Attack(enemyPlayer.getSquad()[targetIdx]);
            } else {
                cout << "AI selected invalid target." << endl;
            }
        }
        DrawMap(aiPlayer, enemyPlayer);
        cout << "\nPress any key for next AI action...";
        _getch();
        ClearScreen();
    }
    aiPlayer.DisplaySquadStatus();
    enemyPlayer.DisplaySquadStatus();
}
void InitializeOpenAIEngine() {
    ofstream configFile("game_config.json");
    if (!configFile.is_open()) {
        cout << "Error creating game configuration file!" << endl;
        return;
    }

    configFile << "{\n";
    configFile << "  \"map_width\": " << MAP_WIDTH << ",\n";
    configFile << "  \"map_height\": " << MAP_HEIGHT << ",\n";
    configFile << "  \"unit_characteristics\": {\n";

    UnitType allTypes[] = {UnitType::SOLDIER, UnitType::GRENADIER, UnitType::SNIPER, UnitType::TANK, UnitType::HELICOPTER};
    int numTypes = sizeof(allTypes) / sizeof(allTypes[0]);

    for (int i = 0; i < numTypes; i++) {
        Unit dummy(allTypes[i], 0, 0);//We create a dummy unit of each type just to access its characteristics for writing into the config file. The actual position doesn't matter here since we're only interested in the stats.
        
        configFile << "    \"" << dummy.getTypeName() << "\": {\n";
        configFile << "      \"max_hp\": " << dummy.getMaxHealth() << ",\n";
        configFile << "      \"max_move\": " << dummy.getMaxMovement() << ",\n";
        configFile << "      \"min_attack\": " << dummy.getMinAttack() << ",\n"; 
        configFile << "      \"max_attack\": " << dummy.getMaxAttack() << ",\n"; 
        configFile << "      \"range\": " << dummy.getAttackRange() << "\n";
        configFile << "      }";

        if (i < numTypes - 1) {//Add a comma after each unit type except the last one

            configFile << ",\n";
        } else {//For the last unit type, we just add a newline without a comma to maintain valid JSON formatting
            configFile << "\n";
        }
    }

    configFile << "  },\n"; 
    configFile << "  \"rules\": [\n";
    configFile << "    \"Coordinate system: X is 0 to " << (MAP_WIDTH - 1) << " from left to right, Y is 0 to " << (MAP_HEIGHT - 1) << " from bottom to top.\",\n";
    configFile << "    \"You must issue exactly 2 actions per turn. They must be for different units UNLESS you only have 1 living unit left, in which case both actions go to that single unit.\",\n";
     configFile << "    \"Movement limits use Chebyshev distance: max(abs(dx), abs(dy)) <= max_move.\",\n";
    configFile << "    \"Do not issue move commands onto tiles currently occupied by any other unit.\"\n";
    configFile << "  ]\n";
    
    configFile << "}";
    configFile.close();
}

int main() {
    system(
    "start \"\" /D \"D:\\Python Projects\\python-for-ai\\Python_for_AI\\My_Projects\\AI_Strategy\" "
    "uv run uvicorn main:app --reload"
);//automatically start the FastAPI server in the background using the uvicorn command.
Sleep(3500);//gives the FastAPI server some time to start up before we attempt to open the Swagger documentation
    

    // Open Swagger docs automatically
    system("start http://127.0.0.1:8000/docs/");
    ConfigureConsole();//fully maximize the console window
    srand(time(0));//seed the random number generator with the current time
    cout<<"==========================================="<<endl;
    cout<<"      WELCOME TO THE STRATEGIC BATTLE      "<<endl;
    cout<<"            AI STRATEGY SHOWDOW            "<<endl;
    cout<<"==========================================="<<endl;
    cout << "===========================================" << endl;
    cout << "       SELECT GAME PLAYBACK MODE        " << endl;
    cout << "===========================================" << endl;
    cout << "1. Human vs AI" << endl;
    cout << "2. AI vs AI (Spectator Mode)" << endl;
    cout << "Choice: ";
    int gameMode = GetValidInteger();

    string name1, name2;
    if (gameMode == 1) {
        cout << "Enter Player 1 (Human) Name: "; cin >> name1;
        cout << "Enter Player 2 (OpenAI AI) Name: "; cin >> name2;
    } else {
        cout << "Enter AI Player 1 Name: "; cin >> name1;
        cout << "Enter AI Player 2 Name: "; cin >> name2;
    }

    Player pA(name1, 'A');//identifier 'A' for player 1, will be used to determine uppercase symbols on the map
    Player pB(name2, 'B');//identifier 'B' for player 2, will be used to determine lowercase symbols on the map

    UnitType types[] = {UnitType::SOLDIER, UnitType::GRENADIER, UnitType::SNIPER, UnitType::TANK, UnitType::HELICOPTER};//array of unit 
    InitializeOpenAIEngine();//for writing game_config.json
    int spawnWidthZone = MAP_WIDTH / 5;
    if (spawnWidthZone < 1) spawnWidthZone = 1;

    for (int i = 0; i < 5; i++) {
        pA.AddUnit(types[i], rand() % spawnWidthZone, rand() % MAP_HEIGHT);       
        pB.AddUnit(types[i], (MAP_WIDTH - spawnWidthZone) + (rand() % spawnWidthZone), rand() % MAP_HEIGHT); 
    }

    ClearScreen();
    int globalTurnCounter = 1;
    while (pA.hasLivingUnits() && pB.hasLivingUnits()) {
        // --- PLAYER 1 TURN ---
        DrawMap(pA, pB);
        if (gameMode == 1) {
            PlayTurn(pA, pB); // Turn of the human player
        } else {
            PlayOpenAITurn(pA, pB, globalTurnCounter); // AI 1 Interacts
        }
        
        cout << "\nPress any key to pass turn...";
        _getch();
        ClearScreen();

        if (!pB.hasLivingUnits()) break;

        // --- PLAYER 2 TURN ---
        DrawMap(pA, pB);
        PlayOpenAITurn(pB, pA, globalTurnCounter); // AI 2 Interacts
        
        cout << "\nPress any key to pass turn...";
        _getch();
        ClearScreen();
        globalTurnCounter++;
    }

    cout << "\nGAME OVER!" << endl;
    if (pA.hasLivingUnits()) cout << "The winner is: " << pA.getName() << "!" << endl;
    else cout << "The winner is: " << pB.getName() << "!" << endl;

    return 0;
}