#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Coordinates.h"

class Menu;
class Spaceship;
enum MenuId
{
	StartScreenMenu,
	NameDisplay,
	PauseScreen,
	EndScreen,
	InstructionsMenu,
	HighScore,

	Size,

	MainGame = -1
};

class Enemy;
class Game
{
	sf::Sprite lifestatus;
	sf::Texture healthbar;
	sf::Font font;
	sf::Text scoredisplay;
	Menu* menu[MenuId::Size];
	MenuId currentScreen;
	bool endGame;
	sf::Texture bg_texture;
	sf::Sprite Background;
	sf::RenderWindow* window;
	Spaceship* player;
	int waves = 0;
	int level = 1;
	void wavemaker();
	
	Coordinates pattern1Counts = { 10, 5 };
	void Update(float deltaT);

	void Render();

	Vector<Enemy*> enemies;

	template <typename E>
	void spawnEnemy(Coordinates pos);

	void Pattern1();
	void Pattern2();
	void Pattern3();
	void Pattern4();
	void Pattern5();
	void Pattern6();
	void Pattern7();
	void Pattern8();
	void Pattern9();
	void Pattern10();
	void Pattern11();
	void chooseEnemy(Coordinates spawnPos);
	void setlevel();
	 

public:
	int getWaves() const;
	void setWaves(int x);
	int getlevel() const;
	void setEndGame();
	void changescreen(MenuId i);
	Spaceship*& getPlayer() ;
	Vector<Enemy*>& getEnemies();
	Game();
	void Run();
	~Game();

};
