#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Game.h"
#include "Spaceship.h"
#include "TextBox.h"
#include "ScoreManager.h"
Menu::Menu() : size(0) {}
Menu::Menu(Game* game, int size) : game(game), size(size)
{
    if (size < 0)
        throw std::out_of_range("Index out of range in insert()");
    else
        text = new sf::Text[size];
    logo.loadFromFile("img/icon.png");
    icon.setTexture(logo);
    icon.setScale(0.6, 0.6);
    font.loadFromFile("Fonts/batmfa__.ttf");
    select();
}
void Menu::display(int i)
{
    icon.setPosition(70, 190 + 100 * i);
}
void Menu::select()
{
    cooldown = 150;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        cursor--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        cursor++;

    if (cursor >= size)
        cursor = size - 1;
    else if (cursor < 1)
        cursor = 1;

    display(cursor);
}
void Menu::Render(sf::RenderWindow* window)
{
    window->draw(sprite);
    for (int i = 0; i < size; i++)
        window->draw(text[i]);
    window->draw(icon);
}

StartScreen::StartScreen(Game* game) : Menu(game, 4)
{
    int y = 290;
    icon.setColor(sf::Color(240, 240, 240));
    texture.loadFromFile("img/StartScreen.jpg");
    sprite.setTexture(texture);
    sprite.setScale(1.5234375, 1.5234375);
    for (int i = 0; i < size; i++)
    {
        text[i].setFont(font);
        text[i].setFillColor(sf::Color(240, 240, 240));
        if (i == 0)
        {
            text[i].setPosition(73, 40);
            text[i].setCharacterSize(60);
            text[i].setStyle(sf::Text::Bold);
        }
        else
        {
            text[i].setPosition(140, y);
            text[i].setCharacterSize(40);
            y += 100;
        }
    }
}
void StartScreen::Update(float delta_T)
{
    Display();
    if (cooldown > 0)
        cooldown -= delta_T;

    if (transition > 0)
        transition -= delta_T;


    if (cooldown <= 0)
        select();
    
    if (transition <= 0)
        viewchange();
}
void StartScreen::Display()
{
    text[0].setString("Space-Shooter");
    text[1].setString("New Game");
    text[2].setString("Instructions");
    text[3].setString("Quit");
}
void StartScreen::viewchange()
{
    transition = 0.15 * 1000;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        switch (cursor)
        {
        case 1:
            game->changescreen(MenuId::NameDisplay);
            break;
        case 2:
            game->changescreen(MenuId::InstructionsMenu);
            break;
        case 3:
            game->setEndGame();
            break;
        }
    }
}

Instructions::Instructions(Game* game) : Menu(game, 7)
{
    int y = 290;
    icon.setColor(sf::Color(240, 240, 240));
    texture.loadFromFile("img/InstructionBackground.jpg");
    sprite.setTexture(texture);
    sprite.setScale(0.5078125, 0.5078125);
    for (int i = 0; i < size; i++)
    {
        text[i].setFont(font);
        text[i].setFillColor(sf::Color(240, 240, 240));
        if (i == 0)
        {
            text[i].setPosition(112, 40);
            text[i].setCharacterSize(60);
            text[i].setStyle(sf::Text::Bold);
        }
        else if (i == 6)
        {
            text[i].setPosition(20, 700);
            text[i].setCharacterSize(45);
            icon.setPosition(160, 700);
        }
        else
        {
            text[i].setPosition(40, y);
            text[i].setCharacterSize(15);
            y += 50;
        }
    }
}
void Instructions::viewchange()
{
    transition = 0.15 * 1000;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        game->changescreen(MenuId::StartScreenMenu);
    
}
void Instructions::Display()
{
    text[0].setString("Instructions");
    text[1].setString(" 1) Move your spacecraft with the arrow keys or other\n   controls to avoid enemy attacks and collect power-ups.");
    text[2].setString("2) Shoot down enemy spacecraft with your primary weapon or\n   special abilities, such as missiles or lasers.");
    text[3].setString("3) Collect power-ups to enhance your spacecraft's abilities, such\n   as increasing your firepower or improving your shield strength.");
    text[4].setString("4) Avoid colliding with enemy spacecraft or their projectiles, as\n   this will cause damage to your spacecraft");
    text[5].setString("5) Survive as long as possible against increasingly difficult waves\n   of enemies, and try to achieve a high score by shooting down\n   as many enemy spacecraft as possible.");
    text[6].setString("Back");
}
void Instructions::Update(float delta_T)
{
    Display();
    if (transition > 0)
        transition -= delta_T;

    if (transition <= 0)
        viewchange();
    
}

Pause::Pause(Game* game) : Menu(game, 5)
{
    int y = 290;
    select();
    icon.setColor(sf::Color(240, 240, 240));
    texture.loadFromFile("img/PauseScreen.jpg");
    sprite.setTexture(texture);

    for (int i = 0; i < size; i++)
    {
        text[i].setFont(font);
        text[i].setFillColor(sf::Color(240, 240, 240));
        text[i].setFillColor(sf::Color(240, 240, 240));
        if (i == 0)
        {
            text[i].setPosition(142, 40);
            text[i].setCharacterSize(60);
            text[i].setStyle(sf::Text::Bold);
        }
        else
        {
            text[i].setPosition(140, y);
            text[i].setCharacterSize(40);
            y += 100;
        }

    }

}
void Pause::viewchange()
{
    transition = 0.15 * 1000;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        switch (cursor)
        {
        case 1:
            game->changescreen(MenuId::MainGame);
            break;
        case 2:
            delete game->getPlayer();
            game->getPlayer() = new Spaceship(game);
            for (int i = 0; i < game->getEnemies().getSize(); i++)
            {
                delete game->getEnemies()[i];
                game->getEnemies()[i] = nullptr;
                game->getEnemies().redact(i);
            }
            game->getEnemies().clear();
            game->changescreen(MenuId::NameDisplay);
            game->setWaves(0);
            *ScoreManager::GetInstance()->GetCurrentScore() = Score();
            break;
        case 3:
            game->changescreen(MenuId::HighScore);
            break;
        case 4:
            game->setEndGame();
            break;
        }
    }
}
void Pause::Display()
{
    text[0].setString("Pause Menu");
    text[1].setString("Resume");
    text[2].setString("NewGame");
    text[3].setString("ScoreBoard");
    text[4].setString("Quit");
}
void Pause::Update(float delta_T)
{
    Display();
    if (cooldown > 0)
        cooldown -= delta_T;
    if (transition > 0)
        transition -= delta_T;

    if (cooldown <= 0)
        select();
    if (transition <= 0)
        viewchange();
}

GameOver::GameOver(Game* game) : Menu(game, 4)
{
    int y = 20;
    select();
    icon.setPosition(210, 735);
    icon.setColor(sf::Color(240, 240, 240));
    texture.loadFromFile("img/EndScreen.jpg");
    sprite.setTexture(texture);
    icon.setScale(0.3, 0.3);
    text[0].setString("Game Over");
    text[2].setString("NewGame");
    text[3].setString("Quit");
    for (int i = 0; i < size; i++)
    {
        text[i].setFont(font);
        text[i].setFillColor(sf::Color(240, 240, 240));
        
        if (i == 1)
            continue;
        if (i == 0)
        {
            text[i].setPosition(95, 40);
            text[i].setCharacterSize(80);
            text[i].setStyle(sf::Text::Bold);
            text[i].setFillColor(sf::Color::Red);
        }
        else
        {
            text[i].setPosition(y, 730);
            text[i].setCharacterSize(30);
            y += 620;
        }

    }
}
void GameOver::viewchange()
{
    transition = 0.15 * 1000;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        read = false;
        switch (cursor)
        {
        case 1:
            delete game->getPlayer();
            game->getPlayer() = new Spaceship(game);
            for (int i = 0; i < game->getEnemies().getSize(); i++)
            {
                delete game->getEnemies()[i];
                game->getEnemies()[i] = nullptr;
                game->getEnemies().redact(i);
            }
            game->getEnemies().clear();
            game->changescreen(MenuId::NameDisplay);
            game->setWaves(0);

            break;
        case 2:
            game->setEndGame();
        }
    }

}
void GameOver::Display()
{
    text[1].setString(std::to_string(ScoreManager::GetInstance()->GetCurrentScore()->score));
   
    text[1].setCharacterSize(100);
    
    text[1].setPosition(390 - text[1].getGlobalBounds().width /2, 390 - text[1].getGlobalBounds().height / 2);

  
}
void GameOver::Update(float delta_T)
{
    Display();
    if (read == false)
    {
        ScoreManager::GetInstance()->entry();
        read == true;
    }
    if (cooldown > 0)
        cooldown -= delta_T;
    if (transition > 0)
        transition -= delta_T;

    if (cooldown <= 0)
        selecthorizontal();
    if (transition <= 0)
        viewchange();
    
}
void GameOver::selecthorizontal()
{
    cooldown = 150;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        cursor = 1;
        icon.setPosition(210, 735);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        cursor = 2;
        icon.setPosition(730, 735);
    }
}

EnterName::EnterName(Game* game ) : Menu(game, 1) , input(new TextBox) {
   
    text->setCharacterSize(40);
    text->setFillColor(sf::Color(140, 140, 140));
    text->setString("Enter Your Name: ");
    text->setFont(font);
    text->setPosition((780 - text->getGlobalBounds().width) / 2, 200);

    texture.loadFromFile("img/Mainbackground.jpg");
    sprite.setTexture(texture);
    sprite.setScale(1.06f, 0.60f);
}
void EnterName::Update(float delta_T)
{

    if (transition >= 0)
        transition -= delta_T;

    if (transition < 0)
        viewchange();
}
void EnterName::ProcessInput(unsigned int character)
{
    input->processInputs(character);
}
void EnterName::viewchange()
{
    transition = 0.15 * 1000;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        ScoreManager::GetInstance()->setName(input->getText());
        
        game->changescreen(MenuId::MainGame);
    }
   
}
void EnterName::Render(sf::RenderWindow* window)
{
    window->draw(sprite);
    window->draw(*text);

    input->Render(window);
}

ScoreBoard::ScoreBoard(Game* game) : Menu(game, 12)
{
    int y = 120;
    standingtextures[0].loadFromFile("img/Alpha.png");
    standingtextures[1].loadFromFile("img/Gold.png");
    standingtextures[2].loadFromFile("img/Bronze.png");
    
    texture.loadFromFile("img/ScoreBoardBG.jpg");
    sprite.setTexture(texture);
    icon.setPosition(130, 735);
    icon.setColor(sf::Color::Black);
    icon.setScale(0.3, 0.3);
            
    for (int i = 0; i < 12; i++)
    {
        text[i].setFont(font);
        text[i].setFillColor(sf::Color::Black);
        if (i == 0)
        {
            text[i].setCharacterSize(60);
            text[i].setString("Leader-Board");
            text[i].setPosition((780 - text[0].getGlobalBounds().width) / 2, 40);
        }
        else if (i == 11)
        {
            text[i].setCharacterSize(30);
            text[i].setString("Back");
            text[i].setPosition(20, 730);
        }
        else
        {            
            text[i].setCharacterSize(40);
            text[i].setPosition(60, y);
            y += 60;
        }
    }
        y = 120;
        for (int i = 0; i < 3; i++)
        {
            standings[i].setTexture(standingtextures[i]);
            standings[i].setScale(0.4, 0.4);
            standings[i].setPosition(10, y);
            y += 60;
        }
}
void ScoreBoard::Update(float delta_T)
{
    for (int i = 0; i < 10; i++)
        text[i + 1].setString(std::to_string(i + 1) + std::string(" ") + ScoreManager::GetInstance()->GetScores()[i].playername + std::string("...................") + std::to_string(ScoreManager::GetInstance()->GetScores()[i ].score));
       


    if (transition >= 0)
        transition -= delta_T;

    if (transition < 0)
        viewchange();
}
void ScoreBoard::viewchange()
{
    transition = 0.15 * 1000;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        game->changescreen(MenuId::PauseScreen);
    
}
void ScoreBoard::Render(sf::RenderWindow* window)
{
    Menu::Render(window);
    for (int i = 0; i < 3; i++)
        window->draw(standings[i]);
}