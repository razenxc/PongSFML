/* TO-DO rewrite collsion, game physics, drawing/updating game objects */

#include "fonts.h"
#include "game.h"

void runInstance()
{
    // ================
    // Class instances
    Fonts::Fonts fonts;
    GameScore playerScoreCounter;

    // =======
    // Window
    const unsigned int screen_width     = 1280;
    const unsigned int screen_height    = 720;
    auto window = sf::RenderWindow(sf::VideoMode(screen_width, screen_height), "SFML Pong", sf::Style::Close);
    window.setFramerateLimit(144);

    // ==========
    // Variables    

    // Default etc.
            bool    colFix          = false;    // because collision condition at start
                                                // gives true we use this var in condition with operator AN
            bool    debugState      = false;
            float   paddleHeight    = 100.0f;
    std::pair<bool, bool> col(false, false);    // X, Y; if false - goes down, if true - goes up;
    std::pair<bool, bool> colTouched(false, false); // preventing triple triggering when the ball and paddle collide

    // Ball
    Ball ball(10.0f, sf::Color::White);

    // Left paddle
    Paddle paddleL(10.0f, screen_height / 2 - 10, 4.0f, {10, paddleHeight}, sf::Color::White);

    // Right paddle
    Paddle paddleR(screen_width - 10 - 10, screen_height / 2 - 10, 4.0f, { 10, paddleHeight }, sf::Color::White);

    // ==========
    // Game loop
    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
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
            ball.posX += ball.speed;
        }
        else
        {
            ball.posX -= ball.speed;
        }

        if (col.second == false)
        {
            ball.posY += ball.speed;
        }
        else
        {
            ball.posY -= ball.speed;
        }

        // --------------------------------
        // Collision with end of view zone
        
        // Ball collision
        if (ball.posY >= screen_height - ball.shape.getRadius() * 2)
        {
            col.second = true;
        }

        if (ball.posY <= 0)
        {
            col.second = false;
        }

        // Paddle collision
        if (paddleL.posY >= screen_height - paddleHeight)
        {
            paddleL.posY = screen_height - paddleHeight;
        }
        else if (paddleL.posY <= 0)
        {
            paddleL.posY = 0;
        }

        if (paddleR.posY >= screen_height - paddleHeight)
        {
            paddleR.posY = screen_height - paddleHeight;
        }
        else if (paddleR.posY <= 0)
        {
            paddleR.posY = 0;
        }

        // --------------------------
        // Paddle and Ball collision
        
        // Left paddle
        if (paddleL.shape.getGlobalBounds().intersects(ball.shape.getGlobalBounds()) && colFix)
        {
            if (!colTouched.first)
            {
                colTouched.first    = true;
                colTouched.second   = false;

                playerScoreCounter.addScore('L');
                col.first = false;
                ball.speed += ball.speedToAdd;
            }   
        }

        // Right paddle
        if (paddleR.shape.getGlobalBounds().intersects(ball.shape.getGlobalBounds()) && colFix)
        {
            if (!colTouched.second)
            {
                colTouched.first    = false;
                colTouched.second   = true;

                playerScoreCounter.addScore('R');
                col.first = true;
                ball.speed += ball.speedToAdd;
            }
        }

        colFix = true;
        
        // ---------------
        // Moving paddles

        // Moving left paddle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
        {
            paddleL.posY -= paddleL.speed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
        {
            paddleL.posY += paddleL.speed;
        }
        // Moving right paddle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
        {
            paddleR.posY -= paddleR.speed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
        {
            paddleR.posY += paddleR.speed;
        }

        // -------
        // Events

        // Reset
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R))
        {
            col.first   = false;
            col.second  = false;
            ball.reset();
            paddleL.reset();
            paddleR.reset();
            playerScoreCounter.reset();
        }

        // Debug
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
        {
            (debugState) ? debugState = false : debugState = true;
        }

        // -----
        // Texts
        
        // Debug
        if (debugState)
        {
            Textobj ballInfo(
                "Ball X: " + std::to_string(ball.posX) + " | Y: " + std::to_string(ball.posY) +
                " | V: " + std::to_string(ball.speed),
                fonts.robotoMedium, 20, 10, 10
            );

            Textobj lPaddleInfo(
                "LPaddle X: " + std::to_string(paddleL.posX) + " | Y: " + std::to_string(paddleL.posY) +
                " | V: " + std::to_string(paddleL.speed),
                fonts.robotoMedium, 20, 10, 30
            );

            Textobj rPaddleInfo(
                "RPaddle X: " + std::to_string(paddleR.posX) + " | Y: " + std::to_string(paddleR.posY) +
                " | V: " + std::to_string(paddleR.speed),
                fonts.robotoMedium, 20, 10, 50
            );

            window.draw(ballInfo.shape);
            window.draw(lPaddleInfo.shape);
            window.draw(rPaddleInfo.shape);
        }

        // Score
        {
            Textobj lPlayerScore(std::to_string(playerScoreCounter.getScore('L')), fonts.madimiOne, 40);
            lPlayerScore.shape.setPosition(screen_width / 2 - lPlayerScore.shape.getLocalBounds().width*2, 30);

            Textobj rPlayerScore(std::to_string(playerScoreCounter.getScore('R')), fonts.madimiOne, 40);
            rPlayerScore.shape.setPosition(screen_width / 2 + rPlayerScore.shape.getLocalBounds().width, 30);

            window.draw(lPlayerScore.shape);
            window.draw(rPlayerScore.shape);

        }

        // Winner
        if (ball.posX > screen_width)
        {
            Textobj winnerText("Left player win", fonts.madimiOne, 100);
            winnerText.shape.setPosition(
                screen_width / 2 - (winnerText.shape.getLocalBounds().width / 2),
                screen_height / 2 - (winnerText.shape.getLocalBounds().height / 2)
            );
            window.draw(winnerText.shape);
        }
        else if (ball.posX < 0)
        {
            Textobj winnerText("Right player win", fonts.madimiOne, 100);
            winnerText.shape.setPosition(
                screen_width / 2 - (winnerText.shape.getLocalBounds().width / 2),
                screen_height / 2 - (winnerText.shape.getLocalBounds().height / 2)
            );
            window.draw(winnerText.shape);
        }


        // ---------
        // Drawable
        ball.shape.setPosition(ball.posX, ball.posY);
        window.draw(ball.shape);

        paddleL.shape.setPosition(paddleL.posX, paddleL.posY);
        window.draw(paddleL.shape);

        paddleR.shape.setPosition(paddleR.posX, paddleR.posY);
        window.draw(paddleR.shape);
        // =====================================

        window.display();
    }
}

void GameScore::reset()
{
    score.first  = 0;
    score.second = 0;
}

void GameScore::subTractScore(char player, int count)
{
    if (player == 'L')
        score.first -= count;
    else if (player == 'R')
        score.second -= count;
}

int GameScore::getScore(char player)
{
    if (player == 'L')
        return score.first;
    else if (player == 'R')
        return score.second;
}

void GameScore::addScore(char player)
{
    if (player == 'L')
    {
        score.first += 1;
    }
    else if (player == 'R')
    {
        score.second += 1;
    }
}
