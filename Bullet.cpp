#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"
#include "Vector.h"
#include "CollisionBox.h"
#include "Game.h"
#include "Spaceship.h"
#include <math.h>
#include <fstream>

Bullet::Bullet(Game* game, Spaceship* player, float angle = 90) : game(game), player(player), tl(),br({9, 29}) , angle(angle )
{
    chooseSprite(player->getFiremode());
    sprite.setTexture(b_texture);
    Positions.y = player->getposition().y - 2;
   
    

    LimitBind = new CollisionBox();
    LimitBind->setSize(tl + Positions, br + Positions);
    sprite.setPosition(Positions.x, Positions.y);
}
void Bullet::chooseSprite(bool firemode)
{
    switch (int(angle))
    {
    case 45:
        b_texture.loadFromFile("img/PNG/Lasers/lazerbullet135.png");
        Positions.x = player->getposition().x + 36.5 + 36;
        break;
    case 60:
        b_texture.loadFromFile("img/PNG/Lasers/lazerbullet120.png");
        Positions.x = player->getposition().x + 36.5 + 20;
        break;
    case 75:
        b_texture.loadFromFile("img/PNG/Lasers/lazerbullet105.png");
        Positions.x = player->getposition().x + 36.5 + 9;
        break;
    case 105:
        b_texture.loadFromFile("img/PNG/Lasers/lazerbullet75.png");
        Positions.x = player->getposition().x + 36.5 - 9;
        break;
    case 120:
        b_texture.loadFromFile("img/PNG/Lasers/lazerbullet60.png");
        Positions.x = player->getposition().x + 36.5 - 20;
        break; 
    case 135:
        b_texture.loadFromFile("img/PNG/Lasers/lazerbullet45.png");
        Positions.x = player->getposition().x + 36.5 - 36;
        break;
    case 90:
        if (firemode == false)
            b_texture.loadFromFile("img/PNG/Lasers/laserBlue15.png");
        else
            b_texture.loadFromFile("img/PNG/Lasers/laserRed15.png");

        Positions.x = player->getposition().x + 36.5;
        sprite.setScale(1, 0.5);
        break;
    }
}

void Bullet::HandleMovement(float delta_T)
{
    Positions.y -= (speed * delta_T * sin(angle * 3.14159 / 180));
    Positions.x -= (speed * delta_T * cos(angle * 3.14159 / 180));

    sprite.setPosition(Positions.x, Positions.y);
    LimitBind->setSize(tl + Positions, br + Positions);
}
void Bullet::Render(sf::RenderWindow* window)
{
    window->draw(sprite);
}
Coordinates Bullet::getPositions()
{
    return Positions;
}

CollisionBox* Bullet::getLimitBind() const
{
    return LimitBind;
}
Bullet::~Bullet() 
{
    delete LimitBind;
    LimitBind = nullptr;    
}
 