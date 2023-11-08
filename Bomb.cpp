
#include "Coordinates.h"
#include "Bomb.h"
#include "Game.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CollisionBox.h"
Bomb::Bomb(Game* game, Enemy* host, Coordinates br) : game(game), host(host), tl(), br(br){
    LimitBind = new CollisionBox();
    LimitBind->setSize(tl + Positions, br + Positions);
}
void Bomb::Render(sf::RenderWindow* window)
{
    window->draw(sprite);
}
CollisionBox* Bomb::getLimitBind() const
{
    return LimitBind;
}
Bomb::~Bomb() {
    delete LimitBind;
    LimitBind = nullptr;
}
 
void InvaderBlast::HandleMovement(float delta_T)
{
    Positions.y += (speed * game->getlevel() * delta_T);

    sprite.setPosition(Positions.x, Positions.y);
    LimitBind->setSize(tl + Positions, br + Positions);
}
const Coordinates& Bomb::getPosition() const
{
    return Positions;
}
InvaderBlast::InvaderBlast(Game* game, Enemy* host) : Bomb(game, host, { 9, 29 })
{
    texture.loadFromFile("img/PNG/Lasers/laserRed03.png");
    sprite.setTexture(texture);
    sprite.setScale(1, 0.77);
    Positions.setCo(host->getPosition().x + 35, host->getPosition().y);

    sprite.setPosition(Positions.x, Positions.y);
}

MonsterBlast::MonsterBlast(Game* game, Enemy* host) : Bomb(game, host, {30, 513})
{
    texture.loadFromFile("img/PNG/Lasers/laserRed14.png");
    sprite.setTexture(texture);
    sprite.setScale(2.290341237709659, 9);
    Positions.x = host->getPosition().x + 150;
    Positions.y = host->getPosition().y + 244;

    LimitBind->setSize(tl + Positions, br + Positions);
    sprite.setPosition(Positions.x, Positions.y);
}
void MonsterBlast::HandleMovement(float delta_T)
{
    Positions.x = host->getPosition().x + 150;
    sprite.setPosition(Positions.x, Positions.y);
    LimitBind->setSize(tl + Positions, br + Positions);
}

DragonBlast::DragonBlast(Game* game, Enemy* host, int Blastdirection) : Bomb(game, host, { 0, 0 }), Position45({ 300, 220 }), Position_45({ 40, 190 }), Blastdirection(Blastdirection)
{

    texture.loadFromFile("img/PNG/Lasers/DragonBeam.png");
    texture45.loadFromFile("img/PNG/Lasers/DragonBeam45.png");
    texture_45.loadFromFile("img/PNG/Lasers/DragonBeam-45.png");
    Positions.setCo(290, 220);
    trajectory();

    tl90.push_back({ 41, 6 });
    br90.push_back({ 83, 384 });
    tl90.push_back({ 22, 398 });
    br90.push_back({ 102, 473 });

    tl45.push_back({ 34, 49 });
    tl45.push_back({ 54, 68 });
    tl45.push_back({ 79, 91 });
    tl45.push_back({ 101, 112 });
    tl45.push_back({ 118, 132 });
    tl45.push_back({ 142, 155 });
    tl45.push_back({ 170, 185 });
    tl45.push_back({ 200, 218 });
    tl45.push_back({ 237, 255 });

    br45.push_back({ 65, 63 });
    br45.push_back({ 87, 85 });
    br45.push_back({ 110, 108 });
    br45.push_back({ 134, 127 });
    br45.push_back({ 156, 152 });
    br45.push_back({ 183, 178 });
    br45.push_back({ 213, 212 });
    br45.push_back({ 252, 248 });
    br45.push_back({ 308, 308 });

    tl_45.push_back({ 278, 49 });
    tl_45.push_back({ 255, 68 });
    tl_45.push_back({ 232, 91 });
    tl_45.push_back({ 208, 112 });
    tl_45.push_back({ 186, 132 });
    tl_45.push_back({ 159, 155 });
    tl_45.push_back({ 129, 185 });
    tl_45.push_back({ 91, 218 });
    tl_45.push_back({ 35, 255 });

    br_45.push_back({ 309, 63 });
    br_45.push_back({ 289, 85 });
    br_45.push_back({ 263, 108 });
    br_45.push_back({ 241, 127 });
    br_45.push_back({ 224, 152 });
    br_45.push_back({ 201, 178 });
    br_45.push_back({ 173, 212 });
    br_45.push_back({ 142, 248 });
    br_45.push_back({ 105, 308 });


    for (int i = 0; i < tl90.getSize(); i++){
        LimitBind90.push_back(new CollisionBox);
        LimitBind90[i]->setSize({ tl90[i] + Positions }, { br90[i] + Positions });
    }
    for (int i = 0; i < tl45.getSize(); i++)
    {
        LimitBind45.push_back(new CollisionBox);
        LimitBind45[i]->setSize({ tl45[i] + Position45 }, { br45[i] + Position45 });
    }
    for (int i = 0; i < tl_45.getSize(); i++)
    {
        LimitBind_45.push_back(new CollisionBox);
        LimitBind_45[i]->setSize({ tl_45[i] + Position_45 }, { br_45[i] + Position_45 });
    }
}
void DragonBlast::trajectory()
{
    switch (Blastdirection % 3)
    {
    case 0:
        sprite.setTexture(texture_45);
        sprite.setPosition(Position_45.x, Position_45.y);
        break;
      
    case 1:
        sprite.setTexture(texture);
        sprite.setPosition(Positions.x, Positions.y);
        break;
    case 2:
        sprite.setTexture(texture45);
        sprite.setPosition(Position45.x, Position45.y);
        break;
    default:
        sprite.setTexture(texture);
        sprite.setPosition(Positions.x, Positions.y);
        break;
    }
   
}
void DragonBlast::HandleMovement(float delta_T) {}
void DragonBlast::Render(sf::RenderWindow* window)
{

    window->draw(sprite);
}
bool DragonBlast::HandleCollision(CollisionBox *other)
{
    switch (Blastdirection)
    {
    case 0:
        for (int i = 0; i < LimitBind_45.getSize(); i++)
            if (other->checkForCollision(*LimitBind_45[i]))
                return true;
        break;
       
    case 1:
        for (int i = 0; i < LimitBind90.getSize(); i++)
            if (other->checkForCollision(*LimitBind90[i]))
                return true;
            
        break;
    case 2:
        for (int i = 0; i < LimitBind45.getSize(); i++)
            if (other->checkForCollision(*LimitBind45[i]))
                return true;
        break;
    default:
        for (int i = 0; i < LimitBind90.getSize(); i++)
        {
            if (other->checkForCollision(*LimitBind90[i]))
                return true;
        }
    }
    return false;
}
 
DragonBlast::~DragonBlast()
{
    for (int i = 0; i < LimitBind90.getSize(); i++)
    {
        delete LimitBind90[i];
        LimitBind90[i] = nullptr;
        LimitBind90.redact(i);
    }
    LimitBind90.clear();
    for (int i = 0; i < LimitBind45.getSize(); i++)
    {
        delete LimitBind45[i];
        LimitBind45[i] = nullptr;
        LimitBind45.redact(i);
    }
    LimitBind45.clear();
    for (int i = 0; i < LimitBind_45.getSize(); i++)
    {
        delete LimitBind_45[i];
        LimitBind_45[i] = nullptr;
        LimitBind_45.redact(i);
    }
    LimitBind_45.clear();
}