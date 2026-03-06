#pragma once
#include <vector>
#include <stack>
#include "Gamewell_api.h"

class Enemy;
class Player;
class CardInfo;
class Entity;
class Button;
class Game
{
	//when restructuring this part of my code in future, each state would be divided into classes
	//this change in structure would not only be better as all logic would be hidden from each other
	//but it would also be much cleaner and easier to read through
	//this current structure is extremely unreadable and messy.
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
	~Game();

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

	//allows e to be clicked then sets the target to them
	void CheckPlayerTarget(Enemy* e);

private:
	int mouseX, mouseY, enemyCount, roundsRemaining;
	bool playerWin;
	bool playerLoss;

	std::string m_textData;

	TextObject* displayAlert;

	std::vector<Enemy*> enemies;
	GameScreen m_screen;
	Player* player;
	Object* mouse;
	Input* userInput;
	Object* p_targetIndicator;

	Enemy* DUMMYTARGET;

	Enemy* AtkE1;
	Enemy* AtkE2;

	GAMESTATE g_state;
	std::stack<TURNSTATE> t_state;

	bool textUpdated;
	TextObject* closeInfo;
	Button* m_playButton;
	Button* m_replayButton;
	Sound* soundPlayer;
	SFXID clickSFX;

	//replacing the deck as that system wasnt finished
	CardInfo* m_hand[4];
	bool handBuilt;

};

