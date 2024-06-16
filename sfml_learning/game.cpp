#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include "error.h"
#include "bouncingBall.h"


Game::Game()
    : mWindow(sf::VideoMode(1920, 1080), "SFML Application"), mTexture(), mPlayer(), mFont(), TimePerFrame(sf::seconds(1.f / 144.0f)), 
    mHueColor(3600.0f), pMWindow(& mWindow), pMHueColors3i(& mHueColor.colorRGB), mBall1(pMWindow, sf::Vector2f(500.0f, 500.0f), 64.0f, pMHueColors3i)
{
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
    // Player texturing and setting spawn location
    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(100.f, 100.f);
    mPlayer.setOrigin((float)mTexture.getSize().x / 2, (float)mTexture.getSize().y / 2);
    
    // Setting player speed
    PlayerSpeed = 500.f;

    // Setting movement directions booleans
    mIsMovingUp = false;
    mIsMovingDown = false;
    mIsMovingRight = false;
    mIsMovingLeft = false;

    // Setting mouse input booleans to default (false)
    mIsLMBPressed = false;
    mIsRMBPressed = false;

    
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        std::cout << (1.0f / timeSinceLastUpdate.asSeconds()) << "\n";
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
        // Keyboard inputs
        case sf::Event::KeyPressed:
            handlePlayerInputKeyboard(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInputKeyboard(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        case sf::Event::Resized:
            std::cout << "New window width & height: " << event.size.width << ", " << event.size.height << "\n";
            break;

        // Mouse inputs
        case sf::Event::MouseButtonPressed:
            handlePlayerInputMouse(event.mouseButton.button, true);
            break;
        case sf::Event::MouseButtonReleased:
            handlePlayerInputMouse(event.mouseButton.button, false);
            break;
        }
    }
}

void Game::handlePlayerInputMouse(sf::Mouse::Button button, bool isPressed)
{
    if (button == sf::Mouse::Left)
    {
        mIsLMBPressed = isPressed;
    }
    if (button == sf::Mouse::Right)
    {
        mIsRMBPressed = isPressed;
    }
}

void Game::handlePlayerInputKeyboard(sf::Keyboard::Key key, bool isPressed)
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
    // Player movement
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

    // Mouse interaction
    if (mIsLMBPressed)
    {
        mousePos = sf::Mouse::getPosition(mWindow);
        mPlayer.setPosition((float)mousePos.x, (float)mousePos.y);
    } 
    if (mIsRMBPressed)
    {
        mousePos = sf::Mouse::getPosition(mWindow);
        mBall1.setPosition((float)mousePos.x, (float)mousePos.y);
    }
}

void Game::render()
{
    mHueColor.rotateHue(.5f);
    //mWindow.clear(sf::Color(mBgColor.colorRGB.x, mBgColor.colorRGB.y, mBgColor.colorRGB.z));
    mWindow.clear(sf::Color(30, 0, 30));
    mBall1.Draw();
    mWindow.draw(mPlayer);
    mWindow.display();
}