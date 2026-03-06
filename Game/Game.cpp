#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "CardInfo.h"
#include "ICard.h"
#include "Entity.h"
#include "Button.h"
#include <fstream>
#include <iostream>

#define OUT std::cout << 
#define LOOPHAND for (int i = 0; i < 4; i++)


Game::Game(GameScreen screen) : m_screen(screen), handBuilt(false), textUpdated(false)
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
	if (displayAlert != nullptr)
	{
		delete displayAlert;
	}
	if (p_targetIndicator != nullptr)
	{
		delete p_targetIndicator;
	}
	if (closeInfo != nullptr)
	{
		delete closeInfo;
	}
	if (m_playButton != nullptr)
	{
		delete m_playButton;
	}
	if (m_replayButton != nullptr)
	{
		delete m_replayButton;
	}
	if (soundPlayer != nullptr)
	{
		delete soundPlayer;
	}
}

void Game::Initialise()
{
	//locks game out of other logic until needed
	g_state = INIT;
	t_state.push(INITIALISING);
	roundsRemaining = 3;

	playerLoss = false;
	playerWin = true;

	m_screen.SetBackgroundRGB(25, 25, 25);

	if (AtkE1 != nullptr)
	{
		delete AtkE1;
		AtkE1 = nullptr;
	}
	if (AtkE2 != nullptr)
	{
		delete AtkE2;
		AtkE2 = nullptr;
	}
	if (mouse != nullptr)
	{
		delete mouse;
		mouse = nullptr;
	}
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	if (DUMMYTARGET != nullptr)
	{
		delete DUMMYTARGET;
		DUMMYTARGET = nullptr;
	}

	if (displayAlert != nullptr)
	{
		delete displayAlert;
		displayAlert = nullptr;
	}

	if (p_targetIndicator != nullptr)
	{
		delete p_targetIndicator;
		p_targetIndicator = nullptr;
	}

	if (closeInfo != nullptr)
	{
		delete closeInfo;
		closeInfo = nullptr;
	}

	if (m_replayButton != nullptr)
	{
		delete m_replayButton;
		m_replayButton = nullptr;
	}

	if (m_playButton != nullptr)
	{
		delete m_playButton;
		m_playButton = nullptr;
	}


	//screen is 1280 x 720
	mouse = new Object("assets/Images/Cursor.bmp", 0, 0, 16, 16, true);
	mouse->SetShouldCollide(true);

	p_targetIndicator = new Object("assets/Images/Target.bmp", 0, 0, 32, 32, false);


	player = new Player(70, 232, *mouse, 100, 10, "assets/Images/Wren_Bird.bmp", 256);

	Colour green;
	green.r = 128;
	green.g = 255;
	green.b = 128;

	//reusable textDisplay
	m_textData =  "The TBCG";
	displayAlert = new TextObject(m_textData.c_str(), "assets/default.ttf", 50, 500, 300, green, true);



	DUMMYTARGET = new Enemy(0, 0, *mouse, 99999, 0, "assets/Images/Wren_Evil.bmp", 1, Enemy::OTHER);
	DUMMYTARGET->Hide();

	AtkE1 = new Enemy(954, 432, *mouse, 70, 8, "assets/Images/Wren_Evil.bmp", 256, Enemy::ATTACKER);
	AtkE2 = new Enemy(954, 32, *mouse, 50, 15, "assets/Images/Super_Wren_Evil.bmp", 256, Enemy::ATTACKER);

	//enemies.push_back(AtkE1);
	//enemies.push_back(AtkE2);

	//for (Enemy* e : enemies)
	//{
	//	e->SetTarget(GetPlayer());
	//}

	player->SetTarget(DUMMYTARGET);
	AtkE1->SetTarget(GetPlayer());
	AtkE2->SetTarget(GetPlayer());


	//only allowed to run once as cards are never deleted in this version of the game, merely taken out of play
	if (!handBuilt)
	{

		//build cards
		std::ifstream file;
		file.open("assets/config.txt");
		std::string line, cardName, type;
		int value, weight, i;


		i = 0;
		while (std::getline(file, line))
		{
			//this would be structured to use the DeckManager if it were to be completed
			m_hand[i] = new CardInfo(*mouse);
			m_hand[i]->Build(line);
			i++;
		}
		handBuilt = true;
	}

	//Additional UI
	m_textData = "Press # to close game";
	closeInfo = new TextObject(m_textData.c_str(), "assets/default.ttf", 20, 10, 700, green, true);

	m_playButton = new Button(600, 350, *mouse, "assets/Images/Start_Button.bmp", 64);
	m_replayButton = new Button(600, 350, *mouse, "assets/Images/Restart_Button.bmp", 64);
	m_replayButton->GetDrawn()->SetShouldDraw(false);
	m_replayButton->GetDrawn()->SetShouldCollide(false);

	clickSFX = soundPlayer->LoadSFX("assets/click.mp3");

	//enter menu after finishing Initialisation
	g_state = MENU;
}

void Game::Run()
{
	//mouse pos always needs to be updated
	userInput->GetMousePos(mouseX, mouseY);
	mouse->SetPosition(mouseX, mouseY);

	switch (g_state)
	{
		case MENU:
		{
			//main menu
			//show title
			displayAlert->Update();
			//show button
			m_playButton->Update();

			//wait for button press
			if (m_playButton->GetClicked())
			{
				//hide both
				displayAlert->SetShouldDraw(false);
				m_playButton->GetDrawn()->SetShouldDraw(false);
				m_playButton->GetDrawn()->SetShouldCollide(false);

				//enter inter_roud
				g_state = INTER_ROUND;
			}
			break;
		}

		case INTER_ROUND:
		{
			//init round
			AtkE1->ResetEnemy();
			enemyCount++;
			AtkE2->ResetEnemy();
			enemyCount++;

			LOOPHAND
			{
				m_hand[i]->GetCard()->Reset();
				m_hand[i]->GetCard()->GetObject()->SetShouldDraw(true);
				m_hand[i]->GetCard()->GetObject()->SetShouldCollide(true);
				m_hand[i]->GetCard()->GetObject()->SetPosition(440 + (i * 100), 560);
			}

			roundsRemaining--;
			//then change state
			g_state = RUNNING_TURNS;
			break;
		}

		case RUNNING_TURNS:
		{
			player->Update();
			p_targetIndicator->Update();
			AtkE1->Update();
			AtkE2->Update();
			DUMMYTARGET->Update();
			displayAlert->Update();

			//update each card
			LOOPHAND
			{
				m_hand[i]->GetCard()->GetObject()->Update();
			}

			RunTurnCycle();
			break;
		}

		case GAMEOVER:
		{
			//if win
			if (playerWin)
			{
				m_screen.SetBackgroundRGB(0, 128, 0);
				m_replayButton->GetDrawn()->SetShouldCollide(true);
				m_replayButton->GetDrawn()->SetShouldDraw(true);

				m_replayButton->Update();
				if (m_replayButton->GetClicked())
				{
					Initialise();
				}
			}
			if (playerLoss)
			{
				m_screen.SetBackgroundRGB(128, 0, 0);
				m_replayButton->GetDrawn()->SetShouldCollide(true);
				m_replayButton->GetDrawn()->SetShouldDraw(true);

				m_replayButton->Update();
				if (m_replayButton->GetClicked())
				{
					Initialise();
				}
			}
			//run appropirate logic
			break;
		}
	}

	closeInfo->Update();
	mouse->Update();
	if (userInput->GetMouseDown(LEFTMOUSEBUTTON))
	{
		soundPlayer->PlaySFX(clickSFX);
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
	
#pragma region INIT
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
#pragma endregion

#pragma region PLAYER
	else if (t_state.top() == PLAYER_CHOOSE)
	{
		//where the player selects their target
		CheckPlayerTarget(AtkE1);
		CheckPlayerTarget(AtkE2);

		if (!GetPlayer()->GetActionMade() && (GetPlayer()->GetTarget() == DUMMYTARGET))
		{
			//if player hasn't selected an action && Target = DUMMY
			//Select Action
			GetPlayer()->SelectAction();

			LOOPHAND
			{
				GetPlayer()->SelectAction(m_hand[i]->GetCard());
			}
		}
		else if (GetPlayer()->GetTarget() == DUMMYTARGET)
		{
			//if action selected but target == Dummy

			if (!textUpdated)
			{
				m_textData = "Select A Target Before Selecting Your Action";
				displayAlert->SetText(m_textData.c_str());
				displayAlert->SetPosition(10, 10);
				displayAlert->SetUniformScale(30);
				textUpdated = true;
				displayAlert->SetShouldDraw(true);
			}

			GetPlayer()->ResetActionMade();
			//idicate to select target
		}
		else if (!GetPlayer()->GetActionMade())
		{
			GetPlayer()->SelectAction();

			LOOPHAND
			{
				GetPlayer()->SelectAction(m_hand[i]->GetCard());
			}
		}
		else
		{
			displayAlert->SetShouldDraw(false);
			textUpdated = false;
			t_state.pop();
		}
	}

	//separate state due to potential for multiple actions in fully developed game
	else if (t_state.top() == PLAYER_ACTIONS)
	{
		GetPlayer()->TurnAction(GetPlayer()->GetTarget());

		LOOPHAND
		{
			if (m_hand[i]->GetCard()->GetPlayed())
			{
				//take card out of play until next round
				m_hand[i]->GetCard()->GetObject()->SetShouldDraw(false);
				m_hand[i]->GetCard()->GetObject()->SetShouldCollide(false);
				m_hand[i]->GetCard()->GetObject()->SetPosition(1, 1);
			}
		}

		t_state.pop();
	}
#pragma endregion

	else if (t_state.top() == ENEMY_ACTIONS)
	{
		 
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
		if (enemyCount <= 0)
		{
			//next round

			if (roundsRemaining <= 0)
			{
				playerWin = true;
				g_state = GAMEOVER;
			}
			else
			{
				g_state = INTER_ROUND;
			}
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
