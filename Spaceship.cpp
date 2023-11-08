#include "Bullet.h"
#include "Spaceship.h"
#include "CollisionBox.h"
#include "Enemy.h"
#include "AddOn.h"
#include <iostream>
#include <math.h>
Coordinates Spaceship::getposition()
{
	return position;
}
CollisionBox* Spaceship::getLimitBind()
{
	return LimitBind;
}
bool Spaceship::getFiremode() const
{
	return firemode;
}
bool Spaceship::getPowerup() const
{
	return powerup;
}
Spaceship::Spaceship(Game* game) : game(game), tl({ 9, 10 }), br({ 67, 68 }), LimitBind(new CollisionBox), firemode(false), powerup(false)
{
	position.setCo(340, 700);
	texture.loadFromFile("img/player_ship.png");
	sprite.setTexture(texture);
	sprite.setPosition(position.x, position.y);
	LimitBind->setSize(tl + position, br + position);
	sprite.setScale(0.75, 0.75);
}

void Spaceship::setLifeline()
{
	if (lives < 3)
		lives++;
}
void Spaceship::setFiremode()
{
	if (firemode == false)
		firemode = true;
	else
		firecooldown = 5 * 1000;
}
void Spaceship::setDanger()
{
	if (lives > 0 && powerup == false)
	{
		lives--;
		position.setCo(340, 700);
		sprite.setPosition(position.x, position.y);
		LimitBind->setSize(tl + position, br + position);
	}
	
}
void Spaceship::setPowerup()
{
	if (powerup == false)
	{
		powerup = true;
		texture.loadFromFile("img/berserk.png");
		sprite.setTexture(texture);
	}
	else
		powerUpAddon = 5 * 1000;
}

void Spaceship::HandleMovement(float delta_T)
{
	float ogx = position.x, ogy = position.y;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		position.x -= (speed * delta_T );
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		position.x += (speed * delta_T);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		position.y -= (speed * delta_T);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		position.y += (speed * delta_T);

	if (ogx > position.x && ogy > position.y)
	{
		if (powerup == false)
			texture.loadFromFile("img/player_ship45.png");
		else
			texture.loadFromFile("img/berserk45.png");
	}

	else if (ogx < position.x && ogy > position.y)
	{
		if (powerup == false)
			texture.loadFromFile("img/player_ship-45.png");
		else
			texture.loadFromFile("img/berserk-45.png");
	}
	else
	{
		if (powerup == false)
			texture.loadFromFile("img/player_ship.png");
		else
			texture.loadFromFile("img/berserk.png");
	}

	sprite.setTexture(texture);
	sprite.setScale(0.75, 0.75);

	if (position.x < -75)
		position.x = 855;
	else if (position.x > 855)
		position.x = -75;

	if (position.y < -75)
		position.y = 855;
	else if (position.y > 855)
		position.y = -75;

	sprite.setPosition(position.x, position.y); 
	LimitBind->setSize(tl + position, br + position);
}
void Spaceship::createBullets()
{
	cooldown = 0.5 * 1000; 
	bullets.push_back(new Bullet{ game, this, 90 });

	if (powerup == true)
		for (int angle = 45; angle <= 135; angle += 15)
			bullets.push_back(new Bullet{ game, this, float(angle) });
		
	
}

void Spaceship::deleteBullets()
{
	if (!bullets.isNUll())
		for (int i = 0; i < bullets.getSize(); i ++)
		{
			if (bullets[i]->getPositions().y < 0)
			{
				delete bullets[i];
				bullets[i] = nullptr;
				bullets.redact(i);
			}
		}
}
void Spaceship::Update(float deltaT)
{
	if (cooldown > 0)
		cooldown -= deltaT;
	
	if (addoncooldown > 0)
		addoncooldown -= deltaT;

	if (addoncooldown <= 0)
		createAddon();
	


	if (cooldown <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		createBullets();
	
	deleteBullets();
	HandleMovement(deltaT);


	for (int i = 0; i < addon.getSize(); i++)
	{
		addon[i]->HandleMovement(deltaT);
		if (addon[i]->HandleCollect(LimitBind))
		{
			position.setCo(340, 700);
			LimitBind->setSize(tl + position, br + position);
			delete addon[i];
			addon[i] = nullptr;
			addon.redact(i);
		}
	}
	
	if (firemode == true)
		fireaddon -= deltaT;
	
	if (powerup == true)
		powerUpAddon -= deltaT;

	if (powerUpAddon <= 0)
	{
		powerup = false;
		powerUpAddon = 5 * 1000; 
		texture.loadFromFile("img/player_ship.png");
		sprite.setTexture(texture);
	}
	if (fireaddon <= 0)
	{
		firemode = false;
		fireaddon = 5 * 1000;
	}

	for (int i = 0; i < game->getEnemies().getSize(); i++)
	{
		for (int j = 0; j < bullets.getSize(); j++)
		{
	
			if (game->getEnemies()[i]->HandleCollision(bullets[j]->getLimitBind()) && firemode == false)
			{
				delete bullets[j];
				bullets[j] = nullptr;
				bullets.redact(j);
				
			}

			if (game->getEnemies()[i]->getLives() <= 0)
			{
				game->getEnemies()[i]->AddScore();
				delete game->getEnemies()[i];
				game->getEnemies()[i] = nullptr;
				game->getEnemies().redact(i);		
				break;
			}
		}

	}

	for (int i = 0; i < bullets.getSize(); i++)
		bullets[i]->HandleMovement(deltaT);
}

void Spaceship::createAddon()
{
	addoncooldown = rand() % (15 * 1000);
	switch (int(rand() % 4))
	{
	case 0:
		addon.push_back(new Powerup{ this });
		break;
	case 1:
		addon.push_back(new Fire{ this });
		break;
	case 2:
		addon.push_back(new Lives{ this });
		break;
	case 3:
		addon.push_back(new Danger{ this });
		break;
	}
}
void Spaceship::Render(sf::RenderWindow* window)
{
	for (int i = 0; i < bullets.getSize(); i++)
		bullets[i]->Render(window);
	for (int i = 0; i < addon.getSize(); i++)
		addon[i]->Render(window);
	window->draw(sprite);
}
int Spaceship::getLives()
{
	return lives;
}
bool Spaceship::HandleCollision(CollisionBox* other)
{

	if (LimitBind->checkForCollision(*other) && powerup == false)
	{
		lives--;	
	
		if (lives > 0) {
			position.setCo(340, 700);
			LimitBind->setSize(tl + position, br + position);
		
			sprite.setPosition(340, 700);
		}
			//enter sound effects later
		return true;
	}
	
	return false;
}

Spaceship::~Spaceship()
{
	delete LimitBind;
	LimitBind = nullptr;
	for (int i = 0; i < bullets.getSize(); i++)
	{
		delete bullets[i];
		bullets[i] = nullptr;
		bullets.redact(i);
	}
	bullets.clear();
	for (int i = 0; i < addon.getSize(); i++)
	{
		delete addon[i];
		addon[i] = nullptr;
		addon.redact(i);
	} 
	addon.clear();
}
 