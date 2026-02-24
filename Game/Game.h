#pragma once
#include <vector>
#include <stack>
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
		KILLING,
		GAMEOVER
	};

	enum TURNSTATE
	{
		INITIALISING,
		PLAYER_CHOOSE,
		PLAYER_ACTIONS,
		ENEMY_ACTIONS,
		CHECK_WIN_LOSS
	};



public:
	Game(GameScreen screen);

	void Initialise();

	void Run();

	bool IsRunning();

	//returns a pointer to the player
	Player* GetPlayer();

	//returns the gamescreen
	GameScreen GetScreen();

	//used within the RoundCycle Function
	void RunTurnCycle();

	void KillProgram();

	void SetPlayerTarget();

private:
	int mouseX, mouseY, enemyCount;
	bool playerWin = false;
	bool playerLoss = false;

	std::vector<Enemy*> enemies;
	GameScreen m_screen;
	Player* player;
	Object* mouse;
	Input* userInput;
	Object* p_targetIndicator;


	Enemy* AtkE1;
	Enemy* AtkE2;

	GAMESTATE g_state;
	std::stack<TURNSTATE> t_state;
};

