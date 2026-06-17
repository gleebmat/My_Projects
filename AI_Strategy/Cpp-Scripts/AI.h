#pragma once
#include "Player.h"

class AI {
public:
void InitializeOpenAIEngine();
void CallOpenAIEngine(Player& aiPlayer, Player& enemyPlayer, int turnNum, int lastActingUnitIdx);
void PlayOpenAITurn(Player& aiPlayer, Player& enemyPlayer, int turnNum);
};

