#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <math.h>

float RandVelocityX()
{
    float velocityX;
    bool directionRight;

    srand(time(NULL));

    directionRight = rand() % 2;

    if (directionRight)
    {
        velocityX = (rand() % 6) + 3;
    } else
        velocityX = ((rand() % 6) + 3) * (-1);
    return velocityX;
}

float RandVelocityY(float velocityX)
{
    float velocityY;
    bool directionUp;

    srand(time(NULL));

    directionUp = rand() % 2;

    if (directionUp)
    {
        velocityY = sqrt((10*10) - (abs(velocityX)) * (abs(velocityX))) * (-1);
    } else
        velocityY = sqrt((10*10) - (abs(velocityX)) * (abs(velocityX)));
    

    return velocityY;
}

bool collidesWithTop(int VelocityY, int BallY)
{
    int topline = 66;

    if (BallY + VelocityY < topline)
        return true;

    return (false);
}

bool collidesWithBottom(int bottom, int VelocityY, int BallY)
{

    if(BallY + VelocityY > bottom)
        return true;

    return (false);
}

bool collidesWithLeftWall(int VelocityX, int BallX)
{
    if(BallX + VelocityX < 0)
        return true;
    return (false);
}

bool collidesWithRightWall(int VelocityX, int BallX, int WINDOW_WIDTH)
{
    if(BallX + VelocityX > WINDOW_WIDTH)
        return true;
    return (false);
}

bool collidesWithPlayer(float VelocityX, float VelocityY, float BallX, float BallY, float PlayerX, float PlayerY, float PLAYER_WIDTH, float PLAYER_HEIGHT)
{
    int steps = std::max(abs(VelocityX), abs(VelocityY));
    float stepX = VelocityX / steps;
    float stepY = VelocityY / steps;

    for (int i = 0; i <= steps; i++)
    {
        float checkX = BallX + stepX * i;
        float checkY = BallY + stepY * i;

        if (checkX <= PlayerX + PLAYER_WIDTH && checkX >= PlayerX)
        {
            if (checkY >= PlayerY && checkY <= PlayerY + PLAYER_HEIGHT)
            {
                return true;
            }
        }
    }

    return false;
}


float incrementVelocityY(float velocity_x, float velocity_y)
{
    float ratio = velocity_y / velocity_x;

    return (velocity_y + ratio * 1.2);
}

float incrementVelocityX(float velocity_y, float velocity_x)
{
    float ratio = velocity_y / velocity_x;

    return (velocity_x + ratio * 1.2);
}

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    //Program Start
    int WINDOW_WIDTH = 1287;
    int WINDOW_HEIGHT = 787;

    int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;
    int SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;

    int WINDOW_POSITION_X = SCREEN_WIDTH / 2 - (WINDOW_WIDTH / 2);
    int WINDOW_POSITION_Y = SCREEN_HEIGHT / 2 - (WINDOW_HEIGHT / 2) -50;

    int rectAmount = 52;

    int ScorePlayer1 = 0;
    int ScorePlayer2 = 0;

    int PLAYER_WIDTH = 7;
    int PLAYER_HEIGHT = 70;

    float Player1 = WINDOW_HEIGHT / 2 - PLAYER_HEIGHT/2;
    float Player2 = Player1;

    float BallR = 5.0f;
    float BallX = WINDOW_WIDTH / 2 - BallR;
    float BallY = WINDOW_HEIGHT / 2 - BallR;

    bool Move1Up = false;
    bool Move1Down = false;
    bool Move2Up = false;
    bool Move2Down = false;

    bool RundeOn = false;
    int BallWinkel = 0;
    int BallSpeed = 10;

    float VelocityX = 0;
    float VelocityY = 0;

    float fTemp;


    int PlayerSpeed = 10;

    sf::RectangleShape rectangle[rectAmount];

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Pong");

    window.setPosition(sf::Vector2i(WINDOW_POSITION_X,WINDOW_POSITION_Y));
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/Arial.ttf");


    while (window.isOpen())
    {
        window.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                    Move1Up = true;
                if (event.key.code == sf::Keyboard::S)
                    Move1Down = true;
                if (event.key.code == sf::Keyboard::Up)
                    Move2Up = true;
                if (event.key.code == sf::Keyboard::Down)
                    Move2Down = true;

                if (event.key.code == sf::Keyboard::Space && !RundeOn)
                {
                    VelocityX = RandVelocityX();
                    VelocityY = RandVelocityY(VelocityX);
                    RundeOn = true;
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::W)
                    Move1Up = false;
                if (event.key.code == sf::Keyboard::S)
                    Move1Down = false;
                if (event.key.code == sf::Keyboard::Up)
                    Move2Up = false;
                if (event.key.code == sf::Keyboard::Down)
                    Move2Down = false;
            }
        }

        if (Move1Up && ((Player1 - PlayerSpeed) > 66))
            Player1 -= (float)PlayerSpeed;
        if (Move1Down && ((Player1 + PLAYER_HEIGHT + PlayerSpeed) < WINDOW_HEIGHT + 2))
            Player1 += (float)PlayerSpeed;
        if (Move2Up && ((Player2 - PlayerSpeed) > 66))
            Player2 -= (float)PlayerSpeed;
        if (Move2Down && ((Player2 + PLAYER_HEIGHT + PlayerSpeed) < WINDOW_HEIGHT + 2))
            Player2 += (float)PlayerSpeed;



        if(collidesWithTop(VelocityY, BallY) || collidesWithBottom(WINDOW_HEIGHT, VelocityY, BallY))
            VelocityY = VelocityY * (-1);


        if (RundeOn)
        {
            BallX += VelocityX;
            BallY += VelocityY;
        }

        if (collidesWithLeftWall(VelocityX, BallX))
        {
            VelocityX = 0;
            VelocityY = 0;
            BallX = WINDOW_WIDTH / 2 - BallR;
            BallY = WINDOW_HEIGHT / 2 - BallR;
            RundeOn = false;
            ScorePlayer2 += 1;
        }
        if (collidesWithRightWall(VelocityX, BallX, WINDOW_WIDTH))
        {
            VelocityX = 0;
            VelocityY = 0;
            BallX = WINDOW_WIDTH / 2 - BallR;
            BallY = WINDOW_HEIGHT / 2 - BallR;
            RundeOn = false;
            ScorePlayer1 += 1;
        }

        if (collidesWithPlayer(VelocityX, VelocityY, BallX, BallY, 30, Player1, PLAYER_WIDTH, PLAYER_HEIGHT))
        {
            VelocityX *= -1;
            VelocityX *= 1.05;
            VelocityY *= 1.05;
        }

        if (collidesWithPlayer(VelocityX, VelocityY, BallX, BallY, WINDOW_WIDTH - 30 - PLAYER_WIDTH, Player2, PLAYER_WIDTH, PLAYER_HEIGHT))
        {
            VelocityX *= -1;
            VelocityX *= 1.05;
            VelocityY *= 1.05;
        }


        window.clear(sf::Color::Black);

        for (int i = 0; i < rectAmount; i++)
        {
            rectangle[i] = sf::RectangleShape(sf::Vector2f(2,8));
            rectangle[i].setPosition(sf::Vector2f(WINDOW_WIDTH/2 -1 ,60 + (i * 6) + (i * 8)));
            window.draw(rectangle[i]);
        }

        sf::RectangleShape topLine(sf::Vector2f(WINDOW_WIDTH,6));
        topLine.setPosition(sf::Vector2f(0,60));
        window.draw(topLine);

        sf::Text player1Text;
        player1Text.setString("Player 1");
        player1Text.setFont(font);
        player1Text.setCharacterSize(30);
        player1Text.setPosition(20,10);
        window.draw(player1Text);

        sf::Text player2Text;
        player2Text.setString("Player 2");
        player2Text.setFont(font);
        player2Text.setCharacterSize(30);
        player2Text.setPosition(WINDOW_WIDTH - 20 - player2Text.getLocalBounds().width,10);
        window.draw(player2Text);

        sf::Text scoreText;
        scoreText.setString(" : ");
        scoreText.setFont(font);
        scoreText.setCharacterSize(30);
        scoreText.setPosition(WINDOW_WIDTH/2 - scoreText.getLocalBounds().width/2 - 1,8);
        window.draw(scoreText);

        sf::Text player1ScoreText;
        player1ScoreText.setString(std::to_string(ScorePlayer1));
        player1ScoreText.setFont(font);
        player1ScoreText.setCharacterSize(30);
        player1ScoreText.setPosition(WINDOW_WIDTH/2 -13 - player1ScoreText.getLocalBounds().width,10);
        window.draw(player1ScoreText);

        sf::Text player2ScoreText;
        player2ScoreText.setString(std::to_string(ScorePlayer2));
        player2ScoreText.setFont(font);
        player2ScoreText.setCharacterSize(30);
        player2ScoreText.setPosition(WINDOW_WIDTH/2 + 10,10);
        window.draw(player2ScoreText);

        sf::RectangleShape player1Rect;
        player1Rect.setSize(sf::Vector2f(PLAYER_WIDTH,PLAYER_HEIGHT));
        player1Rect.setPosition(30,Player1);
        window.draw(player1Rect);

        sf::RectangleShape player2Rect;
        player2Rect.setSize(sf::Vector2f(PLAYER_WIDTH,PLAYER_HEIGHT));
        player2Rect.setPosition(WINDOW_WIDTH - 30 - PLAYER_WIDTH,Player2);
        window.draw(player2Rect);

        sf::CircleShape ball;
        ball.setPosition(sf::Vector2f(BallX,BallY));
        ball.setRadius(BallR);
        window.draw(ball);

        if (!RundeOn)
        {
            sf::Text startText;
            startText.setString("press space to start");
            startText.setFont(font);
            startText.setCharacterSize(17);
            startText.setPosition(WINDOW_WIDTH/2 - startText.getLocalBounds().width/2,430);
            window.draw(startText);
        }

        window.display();
    }

    //Program End

    return 0;
}
