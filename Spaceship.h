#pragma once
#include <SFML/Graphics.hpp>
#include "Coordinates.h"
#include "Vector.h"
class CollisionBox; 
class Bullet;
class Game;
class Enemy;
class AddOn;
class Spaceship
{
	Coordinates position, tl, br;
	CollisionBox* LimitBind;
	float speed = 0.75;
	float cooldown = -1;
	float addoncooldown = 20 * 1000;
	float firecooldown = 5 * 1000;

	sf::Sprite sprite;
	sf::Texture texture;
	int lives = 3;
	Game* game;
	Vector<Bullet*> bullets;
	Vector<AddOn*> addon;
	float fireaddon = 5 * 1000;
	float powerUpAddon = 5 * 1000; 
	void HandleMovement(float delta_T);
	bool firemode;
	bool powerup;
	void createBullets();
	void deleteBullets();
	void createAddon();
public: 
	Spaceship(Game* game);
	bool HandleCollision(CollisionBox* other);
	int getLives(); 
	void setLifeline();
	void setFiremode();
	void setDanger();
	void setPowerup();
	bool getPowerup() const;
	bool getFiremode() const;
	Coordinates getposition();
	CollisionBox* getLimitBind();
	void Update(float deltaT);
	void Render(sf::RenderWindow* window);
	~Spaceship();
};
