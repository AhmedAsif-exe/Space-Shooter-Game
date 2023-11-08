#pragma once
#include <iostream>
#include "Coordinates.h"
#include "Vector.h"
class Spaceship;
class Game;
class Enemy;
class Bullet;
class Bomb;
class CollisionBox
{
	 Coordinates topLeft, bottomRight;
public:
	CollisionBox() :topLeft(), bottomRight() {}
	CollisionBox( Coordinates& tLeft,  Coordinates& bRight) : topLeft(tLeft), bottomRight(bRight) {}
	bool checkForCollision(const CollisionBox& obj);
	void setSize(const Coordinates tLeft, const Coordinates bRight);

};

