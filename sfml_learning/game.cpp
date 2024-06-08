#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include "error.h"


Game::Game()
    : mWindow(sf::VideoMode(1920, 1080), "SFML Application"), mTexture(), mPlayer(), mFont()
{
    std::cout << "App initiallized successfully!\n";
    mWindow.setVerticalSyncEnabled(true); // VSync enabled

    // IBMPlex font loading
    if (!mFont.loadFromFile("res/font/IBMPlexMono.ttf"))
    {
        ConsoleError::throwError("Could not load the IBMPlexMono font!");
    }

    // player texture loading
    if (!mTexture.loadFromFile( "res/img/player.png" )) 
    {
        ConsoleError::throwError("Could not load the mPlayer texture!");
    }
    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(100.f, 100.f);
    PlayerSpeed = 500.f;
    mIsMovingUp = false;
    mIsMovingDown = false;
    mIsMovingRight = false;
    mIsMovingLeft = false;
    
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key,
    bool isPressed)
{
    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= PlayerSpeed;
    if (mIsMovingDown)
        movement.y += PlayerSpeed;
    if (mIsMovingLeft)
        movement.x -= PlayerSpeed;
    if (mIsMovingRight)
        movement.x += PlayerSpeed;
    mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}