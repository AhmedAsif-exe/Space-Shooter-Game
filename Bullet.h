#include <SFML/Graphics.hpp>
#include "Vector.h"
#include <iostream>
#include "Game.h"
#include "Spaceship.h"
struct Coordinates;
class Game;
class Spaceship;
class CollisionBox;
class Bullet
{
    float angle;
    Coordinates Positions, tl, br;
    CollisionBox* LimitBind;
    float speed = 1;
    sf::Sprite sprite;
    sf::Texture b_texture;
    Spaceship* player;
    Game* game;
    

public:
    void chooseSprite(bool firemode);
    Bullet(Game* game, Spaceship* player, float angle);
    Coordinates getPositions();
    CollisionBox* getLimitBind() const;
    void HandleMovement(float delta_T);
    void Render(sf::RenderWindow* window);
    
   
    ~Bullet();
    
};
