#include <SFML/Graphics.hpp>
#include <iostream>
#include "Spaceship.h"
#include "Game.h"
#include "Enemy.h"
#include "Menu.h"
#include "ScoreManager.h"
Game::Game() : window(new sf::RenderWindow(sf::VideoMode(780, 780), "SpaceShooter Game")), player(new Spaceship(this)), endGame(false), currentScreen(MenuId::StartScreenMenu)
{
	bg_texture.loadFromFile("img/Mainbackground.jpg");
	font.loadFromFile("Fonts/batmfa__.ttf");
	healthbar.loadFromFile("img/PNG/Lasers/healthbar.png");
	lifestatus.setTexture(healthbar);
	lifestatus.setPosition(600, 10);
	lifestatus.setScale(1, 0.25);

	ScoreManager::GetInstance()->ReadFromFile("ScoreBoard.dat");
	scoredisplay.setFont(font);
	scoredisplay.setCharacterSize(20);
	scoredisplay.setPosition(10, 10);
	Background.setTexture(bg_texture);
	Background.setScale(1.059782608695652, 0.5963302752293578);
	
	menu[MenuId::StartScreenMenu] = new StartScreen(this);
	menu[MenuId::InstructionsMenu] = new Instructions(this);
	menu[MenuId::PauseScreen] = new Pause(this);
	menu[MenuId::EndScreen] = new GameOver(this);
	menu[MenuId::NameDisplay] = new EnterName(this);
	menu[MenuId::HighScore] = new ScoreBoard(this);

}
 void Game::setEndGame()
{
	endGame = true;
}
int Game::getWaves() const
{
	return waves;
}
void Game::setWaves(int x)
{
	waves = x;
}
int Game::getlevel() const
{
	return level;
}
void Game::setlevel()
{
	if (waves < 4 && waves > 0)
		level = 1;
	else if (waves >= 4 && waves < 8)
		level = 2;
	else if (waves >= 8)
		level = 3;
}
void Game::changescreen(MenuId i)
{
	if (i == -1 || (i >= 0 && i <= 5))
	currentScreen = i;
}
void Game::Run()
{
	sf::Clock clock;
	while (true)
	{
		sf::Event e;
		while (window->pollEvent(e))
		{
			if (e.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || endGame == true)
			{
				window->close();
				return;
			}

			if (e.type == sf::Event::TextEntered)
			{
				if (currentScreen == MenuId::NameDisplay)
				{
					dynamic_cast<EnterName*>(menu[currentScreen])->ProcessInput(e.text.unicode);
				}
			}
		}
		Update(clock.restart().asMicroseconds()/1000.f);
		Render();
	}
}
void Game::Render()
{
	window->clear(sf::Color::Black);
	if (currentScreen == MenuId::MainGame)
	{
		window->draw(Background);
		player->Render(window);
		for (int i = 0; i < enemies.getSize(); i++)
			enemies[i]->Render(window);

		scoredisplay.setString(std::to_string(ScoreManager::GetInstance()->GetCurrentScore()->score));
		window->draw(scoredisplay);
		window->draw(lifestatus);
	}
	else 
	 	menu[currentScreen]->Render(window);

	

	window->display();	
}
template <typename E>
void Game::spawnEnemy(Coordinates pos)
{
	enemies.push_back(new E{ this, pos });
}
void Game::chooseEnemy(Coordinates spawnPos)
{
	switch (int(rand()) % 3)
	{
	case 0:
		spawnEnemy<InvaderAlpha>(spawnPos);
		break;
	case 1:
		spawnEnemy<InvaderBeta>(spawnPos);

		break;
	case 2:
		spawnEnemy<InvaderGamma>(spawnPos);
		break;
	}
}
void Game::Update(float deltaT)
{
	if (currentScreen == MenuId::MainGame)
	{
		setlevel();
		int templife = player->getLives();
		for (int i = 0; i < enemies.getSize(); i++)
		{
			if (player->getLives() <= 0)
				break;
			player->HandleCollision(enemies[i]->getLimitBind());
		}
		if (templife == player->getLives())
			player->Update(deltaT);
	
		lifestatus.setScale(player->getLives() * 0.33, 0.25);
	
		if (enemies.getSize() == 0)
			wavemaker();

		else
			for (int i = 0; i < enemies.getSize(); i++)
				enemies[i]->Update(deltaT);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			currentScreen = MenuId::PauseScreen;
		
		if (player->getLives() <= 0)
			currentScreen = MenuId::EndScreen;
		
	}
	else
		menu[currentScreen]->Update(deltaT);
	
}

Spaceship*& Game::getPlayer()  
{
	return player;
}
Vector<Enemy*>& Game::getEnemies() 
{
	return enemies;
}
void Game::Pattern1()
{

	for (int i = 0; i < 10; ++i)
	{
		Coordinates spawnPos = { i * 70 + 40, 40 };
		chooseEnemy(spawnPos);

		spawnPos.setCo(40 + i * 70, 40 + 4 * 70);
		chooseEnemy(spawnPos);
	}

	for (int i = 0; i < 4; ++i)
	{
		Coordinates spawnPos = { 40, 40 + i * 70 };
		chooseEnemy(spawnPos);

		spawnPos.setCo(9 * 70 + 40, 40 + i * 70);
		chooseEnemy(spawnPos);
	}
}
void Game::Pattern2()
{
	int height = 0;
	for (int i = 5; i >= 1; i--)
	{
		int width = 0;
		for (int k = 5; k > i; k--)
			width += 70;

		for (int j = 0; j < 2 * i - 1; j++)
		{
			Coordinates spawnPos;
			if (i == 5 || j == 0 || j == 2 * i - 2)
				chooseEnemy(spawnPos.setCo(width + j * 70 + 75, 75 + height));
		}
		height += 70;
	}
}
void Game::Pattern3()
{
	int height = 0;
	for (int i = 0; i < 5; i++)
	{
		Coordinates spawnPos;
		if (i == 2)
			for (int j = 0; j < 9; j++)
				chooseEnemy(spawnPos.setCo(75 + 70 * j, 75 + height));
		else
			chooseEnemy(spawnPos.setCo(75 + 70 * 4, 75 + height));

		height += 70;
	}
}
void Game::Pattern4()
{
	int sprite_width = 70, x_offset = 20, y_offset = 40, diamond_distance = 40;
	chooseEnemy({ sprite_width * 2 + x_offset, y_offset });
	chooseEnemy({ sprite_width * 7 + x_offset + diamond_distance, y_offset });
	chooseEnemy({ sprite_width + x_offset, y_offset + sprite_width });
	chooseEnemy({ 3 * sprite_width + x_offset, y_offset + sprite_width });
	chooseEnemy({ 6 * sprite_width + x_offset + diamond_distance, y_offset + sprite_width });
	chooseEnemy({ 8 * sprite_width + x_offset + diamond_distance, y_offset + sprite_width });
	chooseEnemy({ x_offset, y_offset + sprite_width * 2 });
	chooseEnemy({ x_offset + 4 * sprite_width, y_offset + sprite_width * 2 });
	chooseEnemy({ x_offset + 5 * sprite_width + diamond_distance, y_offset + sprite_width * 2 });
	chooseEnemy({ x_offset + 9 * sprite_width + diamond_distance, y_offset + sprite_width * 2 });
	chooseEnemy({ sprite_width + x_offset, y_offset + sprite_width * 3 });
	chooseEnemy({ 3 * sprite_width + x_offset, y_offset + sprite_width * 3 });
	chooseEnemy({ 6 * sprite_width + x_offset + diamond_distance, y_offset + sprite_width * 3 });
	chooseEnemy({ 8 * sprite_width + x_offset + diamond_distance, y_offset + sprite_width * 3 });
	chooseEnemy({ sprite_width * 2 + x_offset, y_offset + sprite_width * 4 });
	chooseEnemy({ sprite_width * 7 + x_offset + diamond_distance, y_offset + sprite_width * 4 });
}
void Game::Pattern5()
{
	//int sprite_width = 70, x_offset = 180, y_offset = 40
	chooseEnemy({ 320, 40 });
	chooseEnemy({ 390, 40 });
	chooseEnemy({ 250, 110 });
	chooseEnemy({ 460, 110 });
	chooseEnemy({ 530, 180 });
	chooseEnemy({ 180, 180 });
	chooseEnemy({ 530, 250 });
	chooseEnemy({ 180, 250 });
	chooseEnemy({ 250, 320 });
	chooseEnemy({ 460, 320 });
	chooseEnemy({ 320, 390 });
	chooseEnemy({ 390, 390 });
}
void Game::Pattern6()
{
	chooseEnemy({75 + 140,0 + 20});
	chooseEnemy({ 75 + 420, 0 + 20 });
	chooseEnemy({ 75 + 70, 70 + 20 });
	chooseEnemy({ 75 + 210, 70 + 20 });
	chooseEnemy({ 75 + 350, 70 + 20 });
	chooseEnemy({ 75 + 490, 70 + 20 });
	chooseEnemy({75 + 0, 20 + 140});
	chooseEnemy({ 75 + 280, 20 + 140 });
	chooseEnemy({ 75 + 560, 20 + 140 });
	chooseEnemy({ 75 + 0, 20 + 210 });
	chooseEnemy({ 75 + 560, 20 + 210 });
	chooseEnemy({ 75 + 70, 20 + 280 }); 
	chooseEnemy({75 + 490, 20 + 280});
	chooseEnemy({ 75 + 140, 20 + 350 });
	chooseEnemy({ 75 + 420, 20 + 350 });
	chooseEnemy({ 75 + 210, 20 + 420 });
	chooseEnemy({ 75 + 350, 20 + 420 });
	chooseEnemy({ 75 + 280, 20 + 490 });

}
void Game::Pattern7()
{
	Pattern1();
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 8; j++)	
			chooseEnemy({ 110 + j * 70, 110 + i * 70 });	
}
void Game::Pattern8()
{
	Pattern2();
	int x_offset = 75 + 70 * 2, y_offset = 75 + 70;
	int temp = 5;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < temp; j++)
			chooseEnemy({ x_offset + j * 70, y_offset + i * 70 });
		
		temp -= 2;
		x_offset += 70;

	}
}
void Game::Pattern9()
{
	Pattern4();
	int height = 0;
	for (int i = 0; i < 3; i++)
	{
		Coordinates spawnPos;
		if (i == 1)
			for (int j = 0; j < 3; j++)
				chooseEnemy(spawnPos.setCo(90 + 70 * j, 110 + height));
		else
			chooseEnemy(spawnPos.setCo( 160, 110 + height));

		height += 70;
	}
	height = 0;
	for (int i = 0; i < 3; i++)
	{
		Coordinates spawnPos;
		if (i == 1)
			for (int j = 0; j < 3; j++)
				chooseEnemy(spawnPos.setCo(480 + 70 * j, 110 + height));
		else
			chooseEnemy(spawnPos.setCo(550, 110 + height));

		height += 70;
	}
	
}
void Game::Pattern10()
{

	Pattern5();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (!(i == 0 && j == 3 || i == 3 && j == 0 || i == 0 && j == 0 || i == 3 && j == 3))
				chooseEnemy({ 250 + i * 70, 110 + j * 70 });
}
void Game::Pattern11()
{
	Pattern6();
	chooseEnemy({ 75 + 2 * 70, 20 + 70 });
	chooseEnemy({ 75 + 6 * 70, 20 + 70 });
	chooseEnemy({ 75 + 1 * 70, 20 + 2 * 70 });
	chooseEnemy({ 75 + 2 * 70, 20 + 2 * 70 });
	chooseEnemy({ 75 + 3 * 70, 20 + 2 * 70 });
	chooseEnemy({ 75 + 5 * 70, 20 + 2 * 70 });
	chooseEnemy({ 75 + 6 * 70, 20 + 2 * 70 });
	chooseEnemy({ 75 + 7 * 70, 20 + 2 * 70 });
	int x_offset = 75 + 70 , y_offset = 20 + 70 * 3;
	int temp = 7;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < temp; j++)
			chooseEnemy({ x_offset + j * 70, y_offset + i * 70 });

		temp -= 2;
		x_offset += 70;

	}

}
void Game::wavemaker()
{
		switch (waves)
		{
		case 0:
			Pattern1();
			break;
		case 1:
			Pattern2();
			break;
		case 2:
			Pattern3();
			break;
		case 3:
			enemies.push_back(new Monster(this));
			break;
		case 4:
			Pattern4();
			break;
		case 5:
			Pattern5();
			break;
		case 6:
			Pattern6();
			break;
		case 7:
			enemies.push_back(new Dragon(this));
			break;
		case 8:
			Pattern7();
		
			break;
		case 9:
			Pattern8();
			
			break;
		case 10:
			Pattern9();
			break;
		case 11:
			Pattern11();
			Pattern10();
			break;
		case 12:
			break;
		}
		waves++;
		if (waves > 12)
		{
			waves = waves % 5 + 7;
		}
}

Game::~Game()
{
	delete menu[MenuId::StartScreenMenu];
	delete menu[MenuId::InstructionsMenu];
	delete menu[MenuId::PauseScreen];
	delete menu[MenuId::EndScreen];
	delete menu[MenuId::NameDisplay];
	delete menu[MenuId::HighScore];
	
	menu[MenuId::StartScreenMenu] = nullptr;
	menu[MenuId::InstructionsMenu] = nullptr;
	menu[MenuId::PauseScreen] = nullptr;
	menu[MenuId::EndScreen] = nullptr;
	menu[MenuId::NameDisplay] = nullptr;
	menu[MenuId::HighScore] = nullptr;

	delete window; 
	window = nullptr;
	
	delete player;
	player = nullptr;

	for (int i = 0; i < enemies.getSize(); i++)
	{
		delete enemies[i];
		enemies[i] = nullptr;
		enemies.redact(i);
	}
	enemies.clear();
}
