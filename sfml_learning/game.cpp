#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include "error.h"
#include "bouncingBall.h"


Game::Game()
    : mWindow(sf::VideoMode(1920, 1080), "SFML Application"), 
        mPWindow(& mWindow), 
        //mTexture(), 
        mPlayer(mPWindow, "res/img/player.png", sf::Vector2f(100.0f, 100.0f)),
        mFont(), 
        TimePerFrame(sf::seconds(1.f / 144.0f)), 
        pTimePerFrame(&TimePerFrame),
        mHueColor(3600.0f), 
        pMHueColors3i(& mHueColor.colorRGB), 
        mBall1(mPWindow, sf::Vector2f(500.0f, 500.0f), 64.0f, pMHueColors3i)
{
    mWindow.setVerticalSyncEnabled(true); // VSync enabled

    // IBMPlex font loading
    if (!mFont.loadFromFile("res/font/IBMPlexMono.ttf"))
    {
        ConsoleError::throwError("Could not load the IBMPlexMono font!");
    }

    

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
            handleInputKeyboard(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handleInputKeyboard(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        case sf::Event::Resized:
            std::cout << "New window width & height: " << event.size.width << ", " << event.size.height << "\n";
            break;

        // Mouse inputs
        case sf::Event::MouseButtonPressed:
            handleInputMouse(event.mouseButton.button, true);
            break;
        case sf::Event::MouseButtonReleased:
            handleInputMouse(event.mouseButton.button, false);
            break;
        }
    }
}

void Game::handleInputMouse(sf::Mouse::Button button, bool isPressed)
{
    // Player specific mouse input
    mPlayer.inputHandleMouse(button, isPressed);

    // Other input collection
    if (button == sf::Mouse::Left)
    {
        mIsLMBPressed = isPressed;
    }
    if (button == sf::Mouse::Right)
    {
        mIsRMBPressed = isPressed;
    }
}

void Game::handleInputKeyboard(sf::Keyboard::Key key, bool isPressed)
{
    // Player specific keyboard input
    mPlayer.inputHandleKeyboard(key, isPressed);
}

void Game::update(sf::Time deltaTime)
{
    
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
    mPlayer.update(pTimePerFrame);
    mWindow.display();
}