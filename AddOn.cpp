#include "AddOn.h"
#include "Spaceship.h"
#include "CollisionBox.h"
#include "ScoreManager.h"

AddOn::AddOn(Coordinates tl, Coordinates br, Spaceship* player) : tl(tl), br(br), speed(0.3), player(player) 
{
	position.setCo(rand() % 730, -100);
	LimitBind = new CollisionBox;
	LimitBind->setSize(tl + position, br + position);
}
void AddOn::HandleMovement(float delta_T)
{
	position.y += (speed * delta_T);
	sprite.setPosition(position.x, position.y);
	LimitBind->setSize(tl + position, br + position);
}
void AddOn::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
}
AddOn::~AddOn() {
	delete LimitBind;
	LimitBind = nullptr;
}
void AddOn::AddPoints()
{
	ScoreManager::GetInstance()->AddToScore(5);
}



Lives::Lives(Spaceship *player) : AddOn({ 0,0 }, { 50, 50 }, player) {
	texture.loadFromFile("img/PNG/Power-ups/life.png");
	sprite.setTexture(texture);
	sprite.setScale(0.96153846153, 1);
	sprite.setPosition(position.x, position.y);
}
bool Lives::HandleCollect(CollisionBox* other)
{
	if (LimitBind->checkForCollision(*other))
	{
		player->setLifeline();
		 AddPoints();
		return true;
	}
	return false;
}

Fire::Fire(Spaceship *player) : AddOn({ 0,0 }, { 50, 50 }, player) {
	texture.loadFromFile("img/PNG/Power-ups/Fire.png");
	sprite.setTexture(texture);
	sprite.setScale( 1, 0.96153846153);
	sprite.setPosition(position.x, position.y);
}
bool Fire::HandleCollect(CollisionBox* other)
{
	if (LimitBind->checkForCollision(*other))
	{
		player->setFiremode();
		AddPoints();
		return true;	 
	}
	return false;
}

Danger::Danger(Spaceship *player): AddOn({ 0, 0 }, { 50, 50 }, player)
{
	texture.loadFromFile("img/PNG/Power-ups/danger.png");
	sprite.setTexture(texture);
	sprite.setScale(0.96153846153, 1);
	sprite.setPosition(position.x, position.y);
}
bool Danger::HandleCollect(CollisionBox* other)
{
	if (position.y > 780 && rewardGranted == false)
	{
		rewardGranted = true;
		AddPoints();
	}
	if (LimitBind->checkForCollision(*other))
	{
		player->setDanger();
		return true;
	}
	return false;
}

Powerup::Powerup(Spaceship *player) : AddOn({0, 0}, {50, 50}, player)
{
	texture.loadFromFile("img/PNG/Power-ups/powerup.png");
	sprite.setTexture(texture);
	sprite.setScale(0.96153846153, 1);
	sprite.setPosition(position.x, position.y);
}
bool Powerup::HandleCollect(CollisionBox* other)
{
	if (LimitBind->checkForCollision(*other))
	{
		player->setPowerup();
		 AddPoints();
		return true;
	}
	return false;	

}