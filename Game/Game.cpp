#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "CardInfo.h"
#include "ICard.h"

#define OUT std::cout << 

Game::Game(GameScreen screen) : m_screen(screen)
{
	Initialise();
}

Game::~Game()
{
	if (AtkE1 != nullptr)
	{
		delete AtkE1;
	}
	if (AtkE2 != nullptr)
	{
		delete AtkE2;
	}
	if (mouse != nullptr)
	{
		delete mouse;
	}
	if (player != nullptr)
	{
		delete player;
	}
	if (DUMMYTARGET != nullptr)
	{
		delete DUMMYTARGET;
	}
	if (userInput != nullptr)
	{
		delete userInput;
	}
}

void Game::Initialise()
{
	//locks game out of other logic until needed
	g_state = INIT;
	t_state.push(INITIALISING);
	roundsRemaining = 1;

	m_screen.SetBackgroundRGB(25, 25, 25);

	if (AtkE1 != nullptr)
	{
		delete AtkE1;
	}
	if (AtkE2 != nullptr)
	{
		delete AtkE2;
	}
	if (mouse != nullptr)
	{
		delete mouse;
	}
	if (player != nullptr)
	{
		delete player;
	}
	if (DUMMYTARGET != nullptr)
	{
		delete DUMMYTARGET;
	}
	//screen is 1280 x 720

	mouse = new Object("assets/Images/Cursor.bmp", 0, 0, 32, 32, true);
	mouse->SetShouldCollide(true);

	p_targetIndicator = new Object("assets/Images/Target.bmp", 0, 0, 32, 32, false);


	player = new Player(70, 232, *mouse, 100, 15, "assets/Images/Wren_Bird.bmp", 256);



	//should later be moved to a round-round init
	DUMMYTARGET = new Enemy(0, 0, *mouse, 9999, 0, "assets/Images/Wren_Evil.bmp", 1, Enemy::OTHER);
	DUMMYTARGET->Hide();


	AtkE1 = new Enemy(954, 432, *mouse, 30, 5, "assets/Images/Wren_Evil.bmp", 256, Enemy::ATTACKER);
	enemyCount++;
	AtkE2 = new Enemy(954, 32, *mouse, 30, 5, "assets/Images/Wren_Evil.bmp", 256, Enemy::ATTACKER);
	enemyCount++;

	enemies.push_back(AtkE1);
	enemies.push_back(AtkE2);

	for (Enemy* e : enemies)
	{
		e->SetTarget(GetPlayer());
	}

	//test
	player->SetTarget(DUMMYTARGET);
	AtkE1->SetTarget(GetPlayer());
	AtkE2->SetTarget(GetPlayer());

	//card test
	CardInfo* C_Damage = new CardInfo(*mouse, "assets/Images/Attack.bmp", 32);
	C_Damage->Build("TestCard1 DamageCard 20 10")->Apply(player->GetTarget()); //build returns and ICard;




	//enter menu after finishing Initialisation
	g_state = MENU;
}

void Game::Run()
{
	//mouse pos always needs to be updated
	userInput->GetMousePos(mouseX, mouseY);
	mouse->SetPosition(mouseX, mouseY);
	mouse->Update();


	switch (g_state)
	{
		case MENU:
		{
			//main menu


			//DEGUG
			g_state = INTER_ROUND;
			break;
		}

		case INTER_ROUND:
		{
			//choose cards
			//init round
			AtkE1->ResetEnemy();
			AtkE2->ResetEnemy();

			roundsRemaining--;
			//then change state
			g_state = RUNNING_TURNS;
			break;
		}

		case RUNNING_TURNS:
		{
			//player and enemies only need updating if the core loop is active
			player->Update();
			p_targetIndicator->Update();
			AtkE1->Update();
			AtkE2->Update();
			DUMMYTARGET->Update();

			//the vector currently breaks the health readout.
			//for (Enemy* e : enemies)
			//{
			//	e->Update();
			//}


			RunTurnCycle();
			break;
		}

		case GAMEOVER:
		{
			//if win
			if (playerWin)
			{
				m_screen.SetBackgroundRGB(0, 255, 0);
			}
			if (playerLoss)
			{
				m_screen.SetBackgroundRGB(255, 0, 0);
			}
			//run appropirate logic
			break;
		}
	}

	//closes the game
	if (userInput->GetKeyDown('#'))
	{
		g_state = KILLING;
		KillProgram();
	}
	else m_screen.Update();
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
		GetPlayer()->SetTarget(DUMMYTARGET);
		p_targetIndicator->SetShouldDraw(false);


		//statestack
		t_state.push(CHECK_WIN_LOSS);
		t_state.push(ENEMY_ACTIONS);
		t_state.push(PLAYER_ACTIONS);
		t_state.push(PLAYER_CHOOSE);
	}

	else if (t_state.top() == PLAYER_CHOOSE)
	{
		//where the player selects their target
		CheckPlayerTarget(AtkE1);
		CheckPlayerTarget(AtkE2);

		//if player hasn't selected an action & Target = DUMMY
		//Select Action
		if (!GetPlayer()->GetActionMade() && (GetPlayer()->GetTarget() == DUMMYTARGET))
		{
			GetPlayer()->SelectAction();
		}
		else if (GetPlayer()->GetTarget() == DUMMYTARGET)
		{
			GetPlayer()->ResetActionMade();
			//idicate to select target
		}
		else if (!GetPlayer()->GetActionMade())
		{
			GetPlayer()->SelectAction();
		}
		else
		{
			t_state.pop();
		}
	}

	//separate state due to potential for multiple actions
	else if (t_state.top() == PLAYER_ACTIONS)
	{
		GetPlayer()->TurnAction(GetPlayer()->GetTarget());
		t_state.pop();
	}

	else if (t_state.top() == ENEMY_ACTIONS)
	{
		//replace with iteration through vec
		 
		 
		//check enemy health, if they are dead, remove their attacks
		if (!AtkE1->QueryDead() && !AtkE1->GetIgnore())
		{
			AtkE1->TurnAction(AtkE1->GetTarget());
		}
		else if(!AtkE1->GetIgnore())
		{
			//stops the enemy from being able to be seen and selected as a target
			enemyCount--;
			AtkE1->Hide();
		}


		if (!AtkE2->QueryDead() && !AtkE2->GetIgnore())
		{
			AtkE2->TurnAction(AtkE2->GetTarget());
		}
		else if(!AtkE2->GetIgnore())
		{
			//stops the enemy from being able to be seen and selected as a target
			enemyCount--;
			AtkE2->Hide();
		}


		t_state.pop();
	}

	else if (t_state.top() == CHECK_WIN_LOSS)
	{
		if (enemyCount == 0)
		{
			//next round
			//g_state = Initialising round

			//if rounds remaining = 0
			playerWin = true;
			g_state = GAMEOVER;
		}
		else if (GetPlayer()->QueryDead())
		{
			playerLoss = true;
			g_state = GAMEOVER;
		}

		t_state.pop();
	}
}

void Game::KillProgram()
{
	m_screen.CloseScreen();

	//delete enemies from end of vector and reverse iterate through;
	// i = enemies.end();?
}

void Game::CheckPlayerTarget(Enemy* e)
{
	//for (Enemy* e : enemies)
	//{
	//	//check if enemy has been clicked
	//	if (e->GetDrawn()->IsOverlapping(*mouse) && e->OnMouseClick(e->GetDrawn()))
	//	{
	//		GetPlayer()->SetTarget(e);
	//		p_targetIndicator->SetPosition(e->GetPosX(), e->GetPosY());
	//	}
	//}


	//check if enemy has been clicked
	if (e->GetDrawn()->IsOverlapping(*mouse) && e->OnMouseClick(e->GetDrawn()))
	{
		GetPlayer()->SetTarget(e);
		p_targetIndicator->SetPosition(e->GetPosX(), e->GetPosY());
		p_targetIndicator->SetShouldDraw(true);
	}
}