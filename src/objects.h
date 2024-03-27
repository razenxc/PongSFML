#pragma once

/* TO-DO avoid duplications in classes */

// Includes
#include <SFML/Graphics.hpp>

// Classes
class Ball
{
private:
    float defPosX    = 0.f;
    float defPosY    = 0.f;
    std::pair<float, float> speedDef = std::make_pair(1.f, 1.f);
public:
    float speedToAdd;
    float posX  = defPosX;
    float posY  = defPosY;
    std::pair<float, float> speed = speedDef;

    sf::CircleShape shape;

    Ball(float radius, float speedToAdd, sf::Color fillColor);
    void reset();
    void increaseSpeed();
};

class Paddle
{
private:
    float   speedDef = 0.f;
    float   defPosX  = 0.f;
    float   defPosY  = 0.f;
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