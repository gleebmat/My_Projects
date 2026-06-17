#include <iostream>
#include "Cpp-Scripts/AI.h"
#include "Cpp-Scripts/Utils.h"
#include "Cpp-Scripts/Player.h"
#include "Cpp-Scripts/Unit.h"
#include "Cpp-Scripts/Config.h"
#include <fstream>
#include <conio.h>
#include <synchapi.h>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    system(
        "start \"FastAPI Backend\" /D \"D:\\Python Projects\\python-for-ai\\Python_for_AI\\My_Projects\\AI_Strategy\" "
        "uv run uvicorn main:app --reload"
    );

    std::this_thread::sleep_for(std::chrono::milliseconds(3500));

    system(
        "start \"Reflex Frontend\" /D \"D:\\Python Projects\\python-for-ai\\Python_for_AI\\My_Projects\\AI_Strategy\\game_dashboard\" "
        "uv run reflex run"
    );

    std::this_thread::sleep_for(std::chrono::milliseconds(12000));

    system("start http://localhost:3000");

    Utils::ConfigureConsole();
    srand(time(0));
    cout<<"==========================================="<<endl;
    cout<<"      WELCOME TO THE STRATEGIC BATTLE      "<<endl;
    cout<<"            AI STRATEGY SHOWDOW            "<<endl;
    cout<<"==========================================="<<endl;
    cout << "===========================================" << endl;
    cout << "       SELECT GAME PLAYBACK MODE        " << endl;
    cout << "===========================================" << endl;
    cout << "1. Human vs AI" << endl;
    cout << "2. AI vs AI (Spectator Mode)" << endl;
    cout<<"3. Human vs Human"<<endl;
    cout << "Choice: ";
    int gameMode = Utils::GetValidInteger();

    string name1, name2;
    if (gameMode == 1) {
        cout << "Enter Player 1 (Human) Name: "; cin >> name1;
        cout << "Enter Player 2 (OpenAI AI) Name: "; cin >> name2;
    } else if(gameMode == 2) {
        cout << "Enter AI Player 1 Name: "; cin >> name1;
        cout << "Enter AI Player 2 Name: "; cin >> name2;
    } else if(gameMode == 3) {
        cout << "Enter Player 1 (Human) Name: "; cin >> name1;
        cout << "Enter Player 2 (Human) Name: "; cin >> name2;
    }

    Player pA(name1, 'A');
    Player pB(name2, 'B');
    AI ai;
    ai.InitializeOpenAIEngine();

    UnitType types[] = {UnitType::SOLDIER, UnitType::GRENADIER, UnitType::SNIPER, UnitType::TANK, UnitType::HELICOPTER};

    int spawnWidthZone = Config::MAP_WIDTH / 5;
    if (spawnWidthZone < 1) spawnWidthZone = 1;

    for (int i = 0; i < 5; i++) {
        pA.AddUnit(types[i], rand() % spawnWidthZone, rand() % Config::MAP_HEIGHT);
        pB.AddUnit(types[i], (Config::MAP_WIDTH - spawnWidthZone) + (rand() % spawnWidthZone), rand() % Config::MAP_HEIGHT);
    }

    Utils::ClearScreen();
    int globalTurnCounter = 1;
    while (pA.hasLivingUnits() && pB.hasLivingUnits()) {
        if (gameMode == 1) {
            Utils::PlayTurn(pA, pB);
        } else if (gameMode == 2) {
            ai.PlayOpenAITurn(pA, pB, globalTurnCounter);
        }
        else if (gameMode == 3) {
            Utils::PlayTurn(pA, pB);
        }

        cout << "\nPress any key to pass turn...";
        _getch();
        Utils::ClearScreen();

        if (!pB.hasLivingUnits()) break;

        if(gameMode == 1)
        {
            ai.PlayOpenAITurn(pB, pA, globalTurnCounter);
        }
        else if(gameMode == 2)
        {
            ai.PlayOpenAITurn(pB, pA, globalTurnCounter);
        }
        else if(gameMode == 3)
        {
             Utils::PlayTurn(pB, pA);
        }

        cout << "\nPress any key to pass turn...";
        _getch();
        Utils::ClearScreen();
        globalTurnCounter++;
    }

    cout << "\nGAME OVER!" << endl;
    if (pA.hasLivingUnits()) cout << "The winner is: " << pA.getName() << "!" << endl;
    else cout << "The winner is: " << pB.getName() << "!" << endl;
    _getch();

    return 0;
}