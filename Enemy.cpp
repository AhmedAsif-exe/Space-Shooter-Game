#include "Enemy.h"
#include "Game.h"
#include "Bomb.h"
#include "CollisionBox.h"
#include "Spaceship.h"
#include "ScoreManager.h"
Enemy::Enemy(Game* game, Coordinates positions, float cooldown, Coordinates tl, Coordinates br, int lives) : game(game), position(positions), cooldown(cooldown), tl(tl), br(br), lives(lives), LimitBind(new CollisionBox), totallives(lives)
{
    healthbar.loadFromFile("img/PNG/Lasers/healthbar.png");
    lifestatus.setTexture(healthbar);
    lifestatus.setPosition(position.x, position.y);

    
    LimitBind->setSize(tl + position, br + position);
}
void Enemy::shotdown()
{
    for (int i = 0; i < bombs.getSize(); i++)
    {
        int templife = game->getPlayer()->getLives();
        game->getPlayer()->HandleCollision(bombs[i]->getLimitBind());
        if (templife < game->getPlayer()->getLives())
        {
            delete bombs[i];
            bombs[i] = nullptr;
            bombs.redact(i);
        }
        if (templife - game->getPlayer()->getLives() == 1)
            break;

        if (bombs[i]->HandleCollision(game->getPlayer()->getLimitBind()))
            game->getPlayer()->setDanger();
            
        
    }
}
void Enemy::deleteBombs()
{
    if (!bombs.isNUll())
    {
        for (int i = 0; i < bombs.getSize(); i++)
        {
            if (bombs[i]->getPosition().y > 780)
            {
                delete bombs[i];
                bombs[i] = nullptr;
                bombs.redact(i);
            }
        }
    }
}
bool Enemy::HandleCollision(CollisionBox* other)
{ 
    if (LimitBind->checkForCollision(*other) && readytodie())
    {
        lives--;
        return true;
    }
    return false;
}
CollisionBox* Enemy::getLimitBind() const
{
    return LimitBind;
}
int Enemy::getLives()
{
    return lives;
}
void Enemy::Render(sf::RenderWindow* window)
{

    for (int i = 0; i < bombs.getSize(); i++)
        bombs[i]->Render(window);
    window->draw(sprite);

}
const Coordinates& Enemy::getPosition() const
{
    return position;
}

bool Enemy::readytodie(){
    return (position.y <= originalspawn);
}
Enemy::~Enemy() {
    delete LimitBind;
    LimitBind = nullptr;
    for (int i = 0; i < bombs.getSize(); i++)
    {
        delete bombs[i];
        bombs[i] = nullptr;
        bombs.redact(i);
    }
}
 

Invader::Invader(Game* game, Coordinates positions, float cooldown, Coordinates tl, Coordinates br) : Enemy(game, positions, cooldown, tl, br, 1){}


InvaderAlpha::InvaderAlpha(Game* game, Coordinates positions) : Invader(game, positions, 5000, {18, 21}, {51, 51})
{
    texture.loadFromFile("img/enemy_3.png");
    sprite.setTexture(texture);
    sprite.setScale(0.404624277, 0.53030303);
    sprite.setPosition(positions.x, originalspawn);
}
void InvaderAlpha::Update(float delta_T)
{
    if (originalspawn >= position.y)
    {
        if (cooldown > 0)
            cooldown -= delta_T;

        if (cooldown <= 0)
        {
            createBombs();
        }

        deleteBombs();
        shotdown();

        for (int i = 0; i < bombs.getSize(); i++)
            bombs[i]->HandleMovement(delta_T);
    }
    else
    {
        originalspawn += (0.5 * delta_T);

        sprite.setPosition(position.x, originalspawn);
    }

}
void InvaderAlpha::createBombs()
{
    cooldown = 5 * 1000;

    bombs.push_back(new InvaderBlast{ game, this });
}
void InvaderAlpha::AddScore()
{
    ScoreManager::GetInstance()->AddToScore(10 * game->getlevel());
}

InvaderBeta::InvaderBeta(Game* game, Coordinates positions) : Invader(game, positions, 3000, {11, 6}, {57, 62})
{
    texture.loadFromFile("img/enemy_1.png");
    sprite.setTexture(texture);
    sprite.setScale(0.564516129, 0.660377358);
    sprite.setPosition(positions.x, positions.y);
}
void InvaderBeta::Update(float delta_T)
{
    if (originalspawn >= position.y)
    {
        if (cooldown > 0)
            cooldown -= delta_T;

        if (cooldown <= 0)
            createBombs();

        deleteBombs();
        shotdown();
        for (int i = 0; i < bombs.getSize(); i++)
            bombs[i]->HandleMovement(delta_T);

        }
    else
    {
        originalspawn += (0.5 * delta_T);
        sprite.setPosition(position.x, originalspawn);
    }
}
void InvaderBeta::createBombs()
{
    cooldown = 3 * 1000;
    bombs.push_back(new InvaderBlast{ game, this });
}
void InvaderBeta::AddScore()
{
    ScoreManager::GetInstance()->AddToScore(20 * game->getlevel());
}

InvaderGamma::InvaderGamma(Game* game, Coordinates positions) : Invader(game, positions, 2000, { 20, 20 }, {50, 44})
{
    texture.loadFromFile("img/enemy_2.png");
    sprite.setTexture(texture);
    sprite.setScale(0.583333333, 0.454545455);
    sprite.setPosition(positions.x, positions.y);
}
void InvaderGamma::Update(float delta_T)
{
    if (originalspawn >= position.y)
    {
        if (cooldown > 0)
            cooldown -= delta_T;

        if (cooldown <= 0)
            createBombs();

        deleteBombs();
        shotdown();
        for (int i = 0; i < bombs.getSize(); i++)
            bombs[i]->HandleMovement(delta_T);

    }
    else
    {
        originalspawn += (0.5 * delta_T);
        sprite.setPosition(position.x, originalspawn);
    }
}
void InvaderGamma::createBombs()
{
    cooldown = 2 * 1000;
    bombs.push_back(new InvaderBlast{ game, this });
}
void InvaderGamma::AddScore()
{
    ScoreManager::GetInstance()->AddToScore(30 * game->getlevel());
}

Monster::Monster(Game* game) : Enemy(game, { 30, 30 }, 2 * 1000, { 122, 104 }, { 210, 280 }, 40), shootingTimer(0)
{
    texture.loadFromFile("img/monster1.png");
    sprite.setTexture(texture);
    sprite.setScale(0.4962406015037594, 0.4962406015037594);
    sprite.setPosition(30, originalspawn);
    lifestatus.setScale(2.2, 0.2);
}
void Monster::Render(sf::RenderWindow* window)
{
    Enemy::Render(window);
    window->draw(lifestatus);

}
void Monster::HandleMovement(float delta_T)
{
    if (originalspawn < position.y)
        originalspawn += (0.5 * delta_T);
    else
    {
        if (position.x > 780 - 360 && treading > 0)
            treading *= -1;
        if (position.x < 30 && treading < 0)
            treading *= -1;

        position.x += (treading * delta_T);
    }
    sprite.setPosition(position.x, originalspawn);
    lifestatus.setPosition(position.x, originalspawn);
    LimitBind->setSize(tl + position, br + position);
}
void Monster::Update(float delta_T)
{
    if (position.y >= 30)
    {
        if (cooldown > 0)
            cooldown -= delta_T;
        else 
          ManageBombs(delta_T);
        shotdown();
      
        if (shootingTimer >= 4 * 1000)
        {

            Cooldown();
            shootingTimer = 0;
            cooldown = 2 * 1000;
        }
        
    }
    lifestatus.setScale(2.2 / totallives * lives, 0.2);

    HandleMovement(delta_T);
    for (int i = 0; i < bombs.getSize(); i++)
        bombs[i]->HandleMovement(delta_T);

}
void Monster::ManageBombs(float delta_t)
{  
    if (bombs.getSize() == 0)
        blast();
    shootingTimer += delta_t;
}
void Monster::blast()
{
    playerlife = game->getPlayer()->getLives();
    bombs.push_back(new MonsterBlast(game, this));
}
void Monster::Cooldown()
{
    if (playerlife - game->getPlayer()->getLives() == 0)
    {
        ScoreManager::GetInstance()->AddToScore(40);
        playerlife = 0;
    }
    for (int i = 0; i < bombs.getSize(); i++)
    {
        delete bombs[i];
        bombs[i] = nullptr;
        bombs.redact(i);
    }
}


Dragon::Dragon(Game* game) : Enemy(game, { 190, 30}, 5 * 1000, { 107, 75 }, { 264, 216 }, 80), shootingTimer(0) {
    texture.loadFromFile("img/dragontexture.png");
    sprite.setTexture(texture);
    sprite.setPosition(190, originalspawn);
    lifestatus.setScale(2.67, 0.2);
}
void Dragon::blast()
{
    int blastDirectionset = int(game->getPlayer()->getposition().x) / 260;
    playerlife = game->getPlayer()->getLives();
    bombs.push_back(new DragonBlast(game, this,  blastDirectionset));
 
}
void Dragon::Cooldown()
{
    if (playerlife - game->getPlayer()->getLives() == 0)
    {
        ScoreManager::GetInstance()->AddToScore(50);
        playerlife = 0;
    }
    for (int i = 0; i < bombs.getSize(); i++)
    {
        delete bombs[i];
        bombs[i] = nullptr;
        bombs.redact(i);
    }
}
void Dragon::ManageBombs(float delta_t)
{
    if (bombs.getSize() == 0)
        blast();

    shootingTimer += delta_t;
}
void Dragon::Update(float delta_T)
{
    if (originalspawn < position.y)
    {
        originalspawn += (0.5 * delta_T);
        sprite.setPosition(position.x, originalspawn);
        LimitBind->setSize(tl + position, br + position);
        lifestatus.setPosition(position.x, originalspawn);
    }
    else
    {
 
        if (cooldown > 0)
            cooldown -= delta_T;
        else
            ManageBombs(delta_T);
        shotdown();
        lifestatus.setScale(2.67 / totallives * lives, 0.2);
        if (shootingTimer >= 7 * 1000)
        {
            Cooldown();
            shootingTimer = 0;
            cooldown = 5 * 1000;
        }
       
    }
    

}
void Dragon::Render(sf::RenderWindow* window)
{
    Enemy::Render(window);
    window->draw(lifestatus);
}
Dragon::~Dragon() { }
 