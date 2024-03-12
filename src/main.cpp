#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

int main()
{
    const unsigned int screen_width = 800;
    const unsigned int screen_height = 600;
    auto window = sf::RenderWindow(sf::VideoMode(screen_width, screen_height), "SFML Pong", sf::Style::Close);
    window.setFramerateLimit(144);

    // ==========
    // Variables
    bool    colFix          = false;            // because collision condition at start gives true we use this var in condition with operator AND
    float   ballSpeed       = 1.0f;
    float   ballSpeedToAdd  = 0.1f;
    float   paddleSpeed     = 4.0f;
    float   paddleHeight    = 100.0f;
    std::pair<bool, bool> col(false, false);    // X, Y; if false - goes down, if true - goes up;

    float   ballX = 0.0f;
    float   ballY = 0.0f;
    sf::CircleShape ball(10.0);
    ball.setFillColor(sf::Color::White);

    const   float   paddleLX    = 10.0f;
            float   paddleLY    = screen_height / 2 - 10;
    sf::RectangleShape paddleL;
    paddleL.setSize(sf::Vector2f{ 10, paddleHeight });
    paddleL.setFillColor(sf::Color::White);

    const   float   paddleRX = screen_width - 10 - 10;
            float   paddleRY = screen_height / 2 - 10;
    sf::RectangleShape paddleR;
    paddleR.setSize(sf::Vector2f{ 10, paddleHeight });
    paddleR.setFillColor(sf::Color::White);

    // ==========
    // Game loop
    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

        }
        window.clear(sf::Color::Black);

        // =====================================

        // ------------
        // Ball moving
        if (col.first == false)
        {
            ballX += ballSpeed;
        }
        else
        {
            ballX -= ballSpeed;
        }

        if (col.second == false)
        {
            ballY += ballSpeed;
        }
        else
        {
            ballY -= ballSpeed;
        }

        // --------------------------------
        // Collision with end of view zone
        
        // Ball collision
        if (ballY >= screen_height - ball.getRadius())
        {
            col.second = true;
        }

        if (ballY <= 0)
        {
            col.second = false;
        }

        // Paddle collision
        if (paddleLY >= screen_height - paddleHeight)
        {
            paddleLY = screen_height - paddleHeight;
        }
        else if (paddleLY <= 0)
        {
            paddleLY = 0;
        }

        if (paddleRY >= screen_height - paddleHeight)
        {
            paddleRY = screen_height - paddleHeight;
        }
        else if (paddleRY <= 0)
        {
            paddleRY = 0;
        }

        // Paddle and Ball collision
        // Left paddle
        if (paddleL.getGlobalBounds().intersects(ball.getGlobalBounds()) && colFix)
        {
            col.first = false;
            ballSpeed += ballSpeedToAdd;
        }

        // Right paddle
        if (paddleR.getGlobalBounds().intersects(ball.getGlobalBounds()) && colFix)
        {
            col.first = true;
            ballSpeed += ballSpeedToAdd;
        }

        colFix = true;
        
        // ---------------
        // Moving paddles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
        {
            paddleLY -= paddleSpeed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
        {
            paddleLY += paddleSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
        {
            paddleRY -= paddleSpeed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
        {
            paddleRY += paddleSpeed;
        }

        // ---------
        // Drawable
        ball.setPosition(ballX, ballY);
        window.draw(ball);

        paddleL.setPosition(paddleLX, paddleLY);
        window.draw(paddleL);

        paddleR.setPosition(paddleRX, paddleRY);
        window.draw(paddleR);
        // =====================================

        window.display();
    }
}