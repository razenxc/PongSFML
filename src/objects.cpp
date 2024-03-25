#include "objects.h"

// ==============
// Classes methods

// Ball
Ball::Ball(float radius, sf::Color fillColor)
{
    shape.setRadius(radius);
    shape.setFillColor(fillColor);
}

void Ball::reset()
{
    posX = defPosX;
    posY = defPosY;
    speed = speedDef;
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