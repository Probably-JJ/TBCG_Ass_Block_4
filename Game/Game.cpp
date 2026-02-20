#include "Game.h"
#include "Player.h"
#include "Enemy.h"

Game::Game(GameScreen screen) : m_screen(screen)
{
	Initialise();
}

void Game::Initialise()
{
	//screen is 1280 x 720

	mouse = new Object("assets/Images/Wren_Bird.bmp", 0, 0, 32, 32, true); //create a child class of Entity, override the mouseover function
	mouse->SetShouldCollide(true);

	player = new Player(70, 232, *mouse, 100, 10, "assets/Images/Wren_Bird.bmp", 256);



	//should later be moved to a round-round init
	Enemy* AttackerEnemy = new Enemy(954, 332, *mouse, 100, 10, "assets/Images/Wren_Evil.bmp", 256, Enemy::ATTACKER);
	enemies.push_back(AttackerEnemy);


	for (Enemy* e : enemies)
	{
		e->SetTarget(GetPlayer());
	}



	//test
	player->SetTarget(AttackerEnemy);
}

void Game::Run()
{
	userInput->GetMousePos(mouseX, mouseY);
	mouse->SetPosition(mouseX, mouseY);

	mouse->Update();

	player->Update();
	for (Enemy* e : enemies)
	{
		e->Update();
		std::cout << 'e' << std::endl;
	}




	if (userInput->GetKeyDown('t'))
	{
		enemies[1]->TurnAction(enemies[1]->GetTarget());
		enemies[1]->SetPos(enemies[1]->GetPosX() + 10, enemies[1]->GetPosY() + 10);
	}




	if (userInput->GetKeyDown('#'))
	{
		KillProgram();
	}




	m_screen.Update();
}

bool Game::IsRunning()
{
	return m_screen.IsRunning();
}

GameScreen Game::GetScreen()
{
	return m_screen;
}

Player* Game::GetPlayer()
{
	return player;
}

void Game::KillProgram()
{
	m_screen.CloseScreen();
	delete mouse;
	delete player;

	//delete enemies from end of vector and reverse iterate through;
	// i = enemies.end();
}
