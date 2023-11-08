
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Vector.h"
#include "Coordinates.h"
class CollisionBox;
class Spaceship;
class Game;
class Bomb;
class Enemy
{
protected:
	float originalspawn = -600;
	Coordinates position, tl, br;
	int lives;
	CollisionBox* LimitBind;
	sf::Sprite sprite, lifestatus;
	sf::Texture texture, healthbar;
	float cooldown;
	Game* game;

	Vector<Bomb*> bombs;
	const int totallives;
	virtual void createBombs(float delta_t) {}
	void deleteBombs();
	virtual void HandleMovement(float delta_T) {}
	void shotdown();
public:
	bool HandleCollision(CollisionBox* other);
	Enemy(Game* game, Coordinates positions, float cooldown, Coordinates tl, Coordinates br, int lives);
	int getLives();
	virtual void Update(float delta_T) = 0;
	virtual void Render(sf::RenderWindow* window);
	const Coordinates& getPosition() const;
	CollisionBox* getLimitBind() const;
	virtual ~Enemy();
	virtual void AddScore() {};
	virtual bool readytodie();
	 
};

class Invader : public Enemy
{

public:
	Invader(Game* game, Coordinates positions, float cooldown, Coordinates tl, Coordinates br); 
};

class InvaderAlpha : public Invader
{
public:
	InvaderAlpha(Game* game, Coordinates positions);
	virtual void createBombs();
	virtual void Update(float delta_T);
	virtual void AddScore() override;

};

class InvaderBeta : public Invader
{
public:
	virtual void createBombs();
	virtual void Update(float delta_T);
	InvaderBeta(Game* game, Coordinates positions);
	virtual void AddScore() override;
};

class InvaderGamma : public Invader
{
public:
	virtual void createBombs();
	virtual void Update(float delta_T);
	InvaderGamma(Game* game, Coordinates positions);
	virtual void AddScore() override;
};
class Monster : public Enemy
{
	float treading = 0.3;
	Coordinates tl = { 122, 104 }, br = { 210, 280 };
	int playerlife = 0;
	float shootingTimer;
	void blast();
	void Cooldown();
	void ManageBombs(float delta_t);
	void HandleMovement(float delta_T);
public:
	Monster(Game* game);
	void Update(float delta_T);
	void Render(sf::RenderWindow* window);

};
class Dragon : public Enemy
{
	int playerlife = 0;

	float shootingTimer;
	void blast();
	void Cooldown();
	void ManageBombs(float delta_t);
public: 
	Dragon(Game* game);
	void Update(float delta_T);
	void Render(sf::RenderWindow* window);
	 

	~Dragon();
};
