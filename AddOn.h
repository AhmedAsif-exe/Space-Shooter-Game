#pragma once
#include <iostream>
#include "Coordinates.h"
#include "Vector.h"
#include <SFML/Graphics.hpp>
class Spaceship;
class CollisionBox;
class AddOn
{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	Coordinates position, tl, br;
	CollisionBox* LimitBind;
	Spaceship* player;
	float speed;
	void AddPoints();
public:
	
	AddOn(Coordinates tl, Coordinates br, Spaceship* player);
	virtual bool HandleCollect(CollisionBox* other) = 0;
	void HandleMovement(float delta_T);
	void Render(sf::RenderWindow* window);
	~AddOn();
};

class Lives : public AddOn
{
	bool HandleCollect(CollisionBox* other);

public:
	Lives(Spaceship *player);

};

class Fire : public AddOn
{
	bool HandleCollect(CollisionBox* other);	 
public:
	Fire(Spaceship *player);

};

class Danger : public AddOn
{
	bool rewardGranted = false;
	bool HandleCollect(CollisionBox* other); 
public:
	Danger(Spaceship *player);

};

class Powerup :public AddOn
{
public:
	bool HandleCollect(CollisionBox* other);	 
	Powerup(Spaceship *player);

};