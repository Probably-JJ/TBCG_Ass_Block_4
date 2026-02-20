#pragma once
#include <vector>
#include "Gamewell_api.h"

class Enemy;
class Player;
class Game
{
	enum GAMESTATE
	{
		INIT,
		MENU,
		INTER_ROUND,
		RUNNING_TURNS,
		KILLING
	};

	enum TURNSTATE
	{
		PLAYER_CHOOSE,
		PLAYER_ACTIONS,
		ENEMY_ACTIONS
	};



public:
	Game(GameScreen screen);

	void Initialise();

	void Run();

	bool IsRunning();

	//used within the RoundCycle Function
	void RunTurnCycle();

	GameScreen GetScreen();

	Player* GetPlayer();

	void KillProgram();

private:
	int mouseX, mouseY;


	std::vector<Enemy*> enemies;
	GameScreen m_screen;
	Player* player;
	Object* mouse;
	Input* userInput;

	GAMESTATE g_state;
	TURNSTATE t_state;
};

