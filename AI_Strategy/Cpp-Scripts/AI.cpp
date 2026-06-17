#include "AI.h"
#include "Config.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include "Utils.h"
#include "Unit.h"
#include <conio.h>

// NEW FEATURES:
#include <filesystem>  // std::filesystem
#include <optional>    // std::optional
#include <ranges>
#include <algorithm>      // ranges for loops
using namespace std;
namespace fs = std::filesystem;// filesystem alias

void AI::InitializeOpenAIEngine() {
    ofstream configFile("game_config.json");
    if (!configFile.is_open()) {
        cout << "Error creating game configuration file!" << endl;
        return;
    }

    configFile << "{\n";
    configFile << "  \"map_width\": " << Config::MAP_WIDTH << ",\n";
    configFile << "  \"map_height\": " << Config::MAP_HEIGHT << ",\n";
    configFile << "  \"unit_characteristics\": {\n";

    UnitType allTypes[] = {
        UnitType::SOLDIER,
        UnitType::GRENADIER,
        UnitType::SNIPER,
        UnitType::TANK,
        UnitType::HELICOPTER
    };
    int numTypes = sizeof(allTypes) / sizeof(allTypes[0]);

    for (int i = 0; i < numTypes; i++) {
        Unit dummy(allTypes[i], 0, 0);//dummy unit for accessing stats

        configFile << "    \"" << dummy.getTypeName() << "\": {\n";
        configFile << "      \"max_hp\": " << dummy.getMaxHealth() << ",\n";
        configFile << "      \"max_move\": " << dummy.getMaxMovement() << ",\n";
        configFile << "      \"min_attack\": " << dummy.getMinAttack() << ",\n";
        configFile << "      \"max_attack\": " << dummy.getMaxAttack() << ",\n";
        configFile << "      \"range\": " << dummy.getAttackRange() << "\n";
        configFile << "      }";

        if (i < numTypes - 1) {
            configFile << ",\n";
        } else {
            configFile << "\n";
        }
    }

    configFile << "  },\n";
    configFile << "  \"rules\": [\n";
    configFile << "    \"Coordinate system: X is 0 to " << (Config::MAP_WIDTH - 1) << " from left to right, Y is 0 to " << (Config::MAP_HEIGHT - 1) << " from bottom to top.\",\n";
    configFile << "    \"You must issue exactly 2 actions per turn. They must be for different units UNLESS you only have 1 living unit left, in which case both actions go to that single unit.\",\n";
    configFile << "    \"Movement limits use Chebyshev distance: max(abs(dx), abs(dy)) <= max_move.\",\n";
    configFile << "    \"Do not issue move commands onto tiles currently occupied by any other unit.\"\n";
    configFile << "  ]\n";
    configFile << "}";
    configFile.close();
}

//struct + optional to represent parsed actions
struct ParsedAction {
    int unitIndex{};
    std::string actionType;
    int dx{};
    int dy{};
    std::optional<int> targetIndex; // may be absent,0-based enemy index
};

// std::string + std::optional
static std::vector<ParsedAction> parse_actions_from_json(const std::string& jsonContent) {
    std::vector<ParsedAction> actions;
    size_t pos = 0;

    while ((pos = jsonContent.find("\"unit_index\"", pos)) != std::string::npos) {
        ParsedAction act{};//declaring a variable of type ParsedAction, with  all its members initialized to their default values
        int unitIdx = -1;
        int dx = 0;
        int dy = 0;
        int targetIdx = -1;
        std::string actionType;

        size_t colonPos = jsonContent.find(":", pos);
        if (colonPos != std::string::npos) {
            unitIdx = std::stoi(jsonContent.substr(colonPos + 1));//stoi converts string to int
        }

        size_t actionPos = jsonContent.find("\"action_type\"", pos);
        if (actionPos != std::string::npos) {
            size_t firstQuote = jsonContent.find("\"", actionPos + 15);
            size_t secondQuote = jsonContent.find("\"", firstQuote + 1);
            actionType = jsonContent.substr(firstQuote + 1, secondQuote - firstQuote - 1);
        }

        size_t dxPos = jsonContent.find("\"dx\"", pos);
        if (dxPos != std::string::npos) {
            size_t dxColon = jsonContent.find(":", dxPos);
            dx = std::stoi(jsonContent.substr(dxColon + 1));
        }

        size_t dyPos = jsonContent.find("\"dy\"", pos);
        if (dyPos != std::string::npos) {
            size_t dyColon = jsonContent.find(":", dyPos);
            dy = std::stoi(jsonContent.substr(dyColon + 1));
        }

        size_t targetPos = jsonContent.find("\"target_index\"", pos);
        if (targetPos != std::string::npos) {
            size_t targetColon = jsonContent.find(":", targetPos);
            targetIdx = std::stoi(jsonContent.substr(targetColon + 1));
            act.targetIndex = targetIdx - 1; // keep original 1-based -> 0-based
        }

        act.unitIndex = unitIdx - 1;
        act.actionType = std::move(actionType);
        act.dx = dx;
        act.dy = dy;

        actions.push_back(std::move(act));
        pos += 20;
    }

    return actions;
}

void AI::PlayOpenAITurn(Player& aiPlayer, Player& enemyPlayer, int turnNum) {
    if (!aiPlayer.hasLivingUnits()) return;
    Utils::ClearScreen();
    cout << "\n>>>>>> OpenAI AGENT TURN: " << aiPlayer.getName() << " <<<<<<" << endl;

    CallOpenAIEngine(aiPlayer, enemyPlayer, turnNum, -1);

    //filesystem check before opening file
    if (!fs::exists("ai_action.json")) {
        cout << "AI Action file missing!" << endl;
        return;
    }

    ifstream actionFile("ai_action.json");
    if (!actionFile.is_open()) {
        cout << "AI Action file missing!" << endl;
        return;
    }

    string jsonContent((istreambuf_iterator<char>(actionFile)), istreambuf_iterator<char>());
    actionFile.close();

    auto actions = parse_actions_from_json(jsonContent); //parsed struct list

    //range-based for over ParsedAction
    for (const auto& act : actions) {
        Utils::DrawMap(aiPlayer, enemyPlayer);

        int unitIdx = act.unitIndex;
        if (unitIdx < 0 || unitIdx >= (int)aiPlayer.getSquad().size()) {
            cout << "Invalid AI unit index." << endl;
            continue;
        }

        Unit& chosenUnit = aiPlayer.getSquad()[unitIdx];
        if (!chosenUnit.isAlive()) {
            cout << "AI selected dead unit." << endl;
            continue;
        }

        if (act.actionType == "move") {
            if (max(abs(act.dx), abs(act.dy)) > chosenUnit.getMaxMovement()) {
                cout << "Illegal AI movement distance." << endl;
                continue;
            }

            int targetX = chosenUnit.getX() + act.dx;
            int targetY = chosenUnit.getY() + act.dy;

            //std::clamp for bounds
            targetX = std::clamp(targetX, 0, Config::MAP_WIDTH - 1);
            targetY = std::clamp(targetY, 0, Config::MAP_HEIGHT - 1);

            if (Utils::IsTileOccupied(targetX, targetY, aiPlayer, enemyPlayer)) {
                cout << "AI attempted occupied tile move." << endl;
                continue;
            }

            chosenUnit.Move(act.dx, act.dy);
        }
        else if (act.actionType == "attack") {
            if (!act.targetIndex.has_value()) {
                cout << "AI did not specify target index." << endl;
            } else {
                int targetIdx = *act.targetIndex;
                if (targetIdx >= 0 &&
                    targetIdx < (int)enemyPlayer.getSquad().size() &&
                    enemyPlayer.getSquad()[targetIdx].isAlive()) {
                    chosenUnit.Attack(enemyPlayer.getSquad()[targetIdx]);
                } else {
                    cout << "AI selected invalid target." << endl;
                }
            }
        }

        cout << "\nPress any key for next AI action...";
        _getch();
        Utils::ClearScreen();
    }

    Utils::DrawMap(aiPlayer, enemyPlayer);
    aiPlayer.DisplaySquadStatus();
    enemyPlayer.DisplaySquadStatus();
}

void AI::CallOpenAIEngine(Player& firstPlayer, Player& secondPlayer, int actionNum, int actionChosenIdx0) {
    ofstream stateFile("game_state.json");

    stateFile << "{\n";
    stateFile << "  \"map_width\": " << Config::MAP_WIDTH << ",\n";
    stateFile << "  \"map_height\": " << Config::MAP_HEIGHT << ",\n";
    stateFile << "  \"action_number\": " << actionNum << ",\n";
    stateFile << "  \"acting_team\": \"" << firstPlayer.getName() << "\",\n";

    stateFile << "  \"ai_units\": [\n";
    for (size_t i = 0; i < firstPlayer.getSquad().size(); ++i) {
        Unit& u = firstPlayer.getSquad()[i];
        bool canAct = u.isAlive() && ((int)i != actionChosenIdx0);
        vector<int> attackableTargets = Utils::GetAttackableEnemyIndices(u, secondPlayer);

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
        vector<int> attackableTargets = Utils::GetAttackableEnemyIndices(u, firstPlayer);

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
