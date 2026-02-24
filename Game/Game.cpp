#include "Game.h"
#include "Player.h"
#include "Enemy.h"

#define OUTSTATE std::cout << g_state << std::endl

Game::Game(GameScreen screen) : m_screen(screen)
{
	Initialise();
}

void Game::Initialise()
{
	//locks game out of other logic until needed
	g_state = INIT;
	t_state.push(INITIALISING);

	//screen is 1280 x 720

	mouse = new Object("assets/Images/Wren_Bird.bmp", 0, 0, 32, 32, true);
	mouse->SetShouldCollide(true);

	p_targetIndicator = new Object("assets/Images/Wren_Bird.bmp", 0, 0, 32, 32, true);


	player = new Player(70, 232, *mouse, 100, 10, "assets/Images/Wren_Bird.bmp", 256);



	//should later be moved to a round-round init
	AtkE1 = new Enemy(954, 432, *mouse, 100, 10, "assets/Images/Wren_Evil.bmp", 256, Enemy::ATTACKER);
	enemyCount++;
	AtkE2 = new Enemy(954, 32, *mouse, 100, 10, "assets/Images/Wren_Evil.bmp", 256, Enemy::ATTACKER);
	enemyCount++;

	//enemies.push_back(AtkE1);
	//enemies.push_back(AtkE2);

	//for (Enemy* e : enemies)
	//{
	//	e->SetTarget(GetPlayer());
	//}

	//test
	player->SetTarget(AtkE1);
	AtkE1->SetTarget(GetPlayer());
	AtkE2->SetTarget(GetPlayer());

	//enter menu after finishing Initialisation
	g_state = MENU;
}

void Game::Run()
{
	//mouse pos always needs to be updated
	userInput->GetMousePos(mouseX, mouseY);
	mouse->SetPosition(mouseX, mouseY);
	mouse->Update();

	if (g_state == MENU)
	{
		//main menu


		//DEGUG
		g_state = INTER_ROUND;
	}

	else if (g_state == INTER_ROUND)
	{
		//choose cards
		//init round
		//then change state
		g_state = RUNNING_TURNS;
	}

	else if (g_state == RUNNING_TURNS)
	{
		//player and enemies only need updating if the core loop is active
		player->Update();
		AtkE1->Update();
		AtkE2->Update();

		//the vector currently breaks the health readout.
		//for (Enemy* e : enemies)
		//{
		//	e->Update();
		//}


		RunTurnCycle();
	}

	else if (g_state == GAMEOVER)
	{
		//if win
		//if loss
		//run appropirate logic
	}


	//closes the game
	if (userInput->GetKeyDown('#'))
	{
		g_state = KILLING;
		KillProgram();
	}
	m_screen.Update();
}

bool Game::IsRunning()
{
	return m_screen.IsRunning();
}


Player* Game::GetPlayer()
{
	return player;
}

GameScreen Game::GetScreen()
{
	return m_screen;
}

void Game::RunTurnCycle()
{
	//break out of this loop

	if (t_state.top() == INITIALISING)
	{
		GetPlayer()->ResetActionMade();

		//statestack
		t_state.push(CHECK_WIN_LOSS);
		t_state.push(ENEMY_ACTIONS);
		t_state.push(PLAYER_ACTIONS);
		t_state.push(PLAYER_CHOOSE);
	}

	else if (t_state.top() == PLAYER_CHOOSE)
	{
		if (!GetPlayer()->GetActionMade())
		{
			GetPlayer()->SelectAction();
		}
		else
		{
			t_state.pop();
		}
	}

	else if (t_state.top() == PLAYER_ACTIONS)
	{
		GetPlayer()->TurnAction(GetPlayer()->GetTarget());
		//separate state due to potential for multiple actions
		t_state.pop();
	}

	else if (t_state.top() == ENEMY_ACTIONS)
	{
		//replace with iteration through vec
		AtkE1->TurnAction(AtkE1->GetTarget());
		AtkE2->TurnAction(AtkE2->GetTarget());

		t_state.pop();
	}

	else if (t_state.top() == CHECK_WIN_LOSS)
	{
		if (enemyCount == 0)
		{
			playerWin = true;
			//next round
			//g_state = Initialising round
		}
		else if (GetPlayer()->QueryDead())
		{
			playerLoss = true;
			//g_state gameover
		}
		t_state.pop();
	}
}

void Game::KillProgram()
{
	m_screen.CloseScreen();
	delete mouse;
	delete player;

	//delete enemies from end of vector and reverse iterate through;
	// i = enemies.end();?
}

void Game::SetPlayerTarget()
{
	for (Enemy* e : enemies)
	{
		//check if enemy has been clicked
		if (e->GetDrawn()->IsOverlapping(*mouse) && e->OnMouseClick(e->GetDrawn()))
		{
			GetPlayer()->SetTarget(e);
			p_targetIndicator->SetPosition(e->GetPosX(), e->GetPosY());
		}
	}
}