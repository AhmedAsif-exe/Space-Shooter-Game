
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Vector.h"
#include "Coordinates.h"
class Game;
class Enemy;
class CollisionBox;
class Bomb
{
protected:
    Coordinates Positions, tl, br;
    sf::Sprite sprite;
    sf::Texture texture;
    CollisionBox* LimitBind;
    Game* game;
    Enemy* host;
    float speed = 0.2;


public:
    Bomb(Game* game, Enemy* host, Coordinates br);
    virtual bool  HandleCollision(CollisionBox* other) { return false; }
    CollisionBox* getLimitBind() const;
    virtual void HandleMovement(float delta_T) = 0;
    virtual void Render(sf::RenderWindow* window);
    const Coordinates& getPosition() const;
 
    ~Bomb();
};
class InvaderBlast : public Bomb
{
public:
    void HandleMovement(float delta_T);
    InvaderBlast(Game* game, Enemy* host); 
};
class MonsterBlast : public Bomb
{
public:
    void HandleMovement(float delta_T);
    MonsterBlast(Game* game, Enemy* host);
    
};
class DragonBlast : public Bomb
{
 
    int Blastdirection;
    sf::Texture texture45, texture_45;
    Vector<Coordinates> tl90, tl45, tl_45;
    Vector<Coordinates> br90, br45, br_45;
    Vector<CollisionBox*> LimitBind90, LimitBind45, LimitBind_45;
    Coordinates Position45, Position_45;
    void trajectory();
    void Render(sf::RenderWindow* window);
    virtual bool HandleCollision(CollisionBox* other);
public:
 
    void HandleMovement(float delta_T);
    DragonBlast(Game* game, Enemy* host, int Blastdirection);
    ~DragonBlast();
}; 
