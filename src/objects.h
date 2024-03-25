#pragma once

/* TO-DO avoid duplications in classes */

// Includes
#include <SFML/Graphics.hpp>

// Classes
class Ball
{
private:
    float speedDef   = 1.0f;
    float defPosX    = 0.0f;
    float defPosY    = 0.0f;
public:
    float speedToAdd = 0.1f;
    float speed = speedDef;
    float posX  = defPosX;
    float posY  = defPosY;

    sf::CircleShape shape;

    Ball(float radius, sf::Color fillColor);
    void reset();
};

class Paddle
{
private:
    float   speedDef = 0.0f;
    float   defPosX  = 0.0f;
    float   defPosY  = 0.0f;
public:
    float speed = speedDef;
    float posX = defPosX;
    float posY = defPosY;
    
    sf::RectangleShape shape;
    
    Paddle(float posX, float posY, float speed, sf::Vector2f size, sf::Color fillColor);
    void reset();
};

class Textobj
{
public:
    sf::Text    shape;

    Textobj(std::string string, sf::Font& font, unsigned short fontSize, float posX, float posY, sf::Color fillColor = sf::Color::White);
    Textobj(std::string string, sf::Font& font, unsigned short fontSize, sf::Color fillColor = sf::Color::White);
};