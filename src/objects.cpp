#include "objects.h"

// ==============
// Classes methods

// Ball
Ball::Ball(float radius, float speedToAdd, sf::Color fillColor)
{
    Ball::speedToAdd = speedToAdd;
    shape.setRadius(radius);
    shape.setFillColor(fillColor);
}

void Ball::reset()
{
    posX = defPosX;
    posY = defPosY;
    speed = speedDef;
}

void Ball::increaseSpeed()
{
    (speed.first < 0) ? speed.first  -= speedToAdd : speed.first += speedToAdd;
    (speed.second < 0) ? speed.second -= speedToAdd : speed.second += speedToAdd;
}

// Paddle
Paddle::Paddle(float posX, float posY, float speed, sf::Vector2f size, sf::Color fillColor)
{
    
    defPosX  = posX;
    defPosY  = posY;
    speedDef = speed;
    Paddle::posX    = defPosX;
    Paddle::posY    = defPosY;
    Paddle::speed   = speedDef;
    shape.setSize(size);
    shape.setFillColor(fillColor);
}

void Paddle::reset()
{
    posX = defPosX;
    posY = defPosY;
    speed = speedDef;
}

// Textobj
Textobj::Textobj(std::string string, sf::Font &font, unsigned short fontSize, float posX, float posY, sf::Color fillColor)
{
    shape.setString(string);
    shape.setFont(font);
    shape.setCharacterSize(fontSize);
    shape.setPosition(posX, posY);
    shape.setFillColor(fillColor);
}

Textobj::Textobj(std::string string, sf::Font& font, unsigned short fontSize, sf::Color fillColor)
{
    shape.setString(string);
    shape.setFont(font);
    shape.setCharacterSize(fontSize);
    shape.setFillColor(fillColor);
}