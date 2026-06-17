#pragma once
#include "Player.h"
#include "Unit.h"
#include <vector>
#include <iostream>

namespace Utils {
    int GetValidInteger();
    void ClearScreen();
    void ConfigureConsole();
    bool IsTileOccupied(int x, int y, Player& p1, Player& p2);
    void DrawMap(Player& p1,Player& p2);
    void ExecuteUnitAction(Unit& unit, Player& activePlayer, Player& enemyPlayer);
    std::vector<int> GetUnitsInAttackRange(Unit& attacker,Player& enemyPlayer);
    std::vector<int> GetAttackableEnemyIndices(Unit& attacker,Player& enemyPlayer);
    void PlayTurn(Player& activePlayer, Player& enemyPlayer);
};