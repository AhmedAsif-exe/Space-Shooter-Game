#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class TextBox;
class ScoreManager;
class Game;
class Menu
{
protected:
	float cooldown = 0.15 * 1000, transition = 0.15 * 1000;
	sf::Sprite sprite, icon;
	sf::Texture texture, logo;
	sf::Text* text;
	Game* game;
	const int size;
	sf::Font font;
	int cursor = 1;

	void display(int i);

	void select();
	virtual void viewchange(){}

public:
	Menu();
	Menu(Game* game, int size);
	virtual void Update(float delta_T) = 0;
	virtual void Display() = 0;
	virtual void Render(sf::RenderWindow* window);
	
};

class StartScreen : public Menu
{

	void viewchange() override;
public:
	StartScreen(Game* game);
	virtual void Display();
	virtual void Update(float delta_T) override;
};
class Instructions : public Menu
{
	void viewchange() override;
public:
	Instructions(Game* game);
	virtual void Display() override;
	virtual void Update(float delta_T) override;
};
class Pause : public Menu
{
	void viewchange() override;
public:
	Pause(Game* game);
	virtual void Display() override;
	virtual void Update(float delta_T) override;
};
class GameOver : public Menu
{
	void viewchange() override;
	void selecthorizontal();
	bool read = false;
public:
	GameOver(Game* game);
	virtual void Display() override;
	virtual void Update(float delta_T) override;
};
class EnterName : public Menu
{	
	TextBox* input;

	void viewchange() override;


public:
	EnterName(Game* game );
	virtual void Display() override {}
	virtual void Render(sf::RenderWindow* window) override;
	virtual void Update(float delta_T) override;
	void ProcessInput(unsigned int character);
};


class ScoreBoard : public Menu
{
	sf::Texture standingtextures[3];
	sf::Sprite standings[3];
	void viewchange() override;

public:
	ScoreBoard(Game* game); 
	virtual void Update(float delta_T);
	virtual void Display() {};
	virtual void Render(sf::RenderWindow* window);
};