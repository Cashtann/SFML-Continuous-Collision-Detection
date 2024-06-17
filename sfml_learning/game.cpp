#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include "error.h"
#include "particleSimulation.h"


Game::Game()
    : mWindow(sf::VideoMode(1920, 1080), "SFML Application"), 
        mPWindow(& mWindow), 
        mPlayer(mPWindow, "res/img/player.png", sf::Vector2f(100.0f, 100.0f)), 
        TimePerFrame(sf::seconds(1.f / 144.0f)), 
        pTimePerFrame(&TimePerFrame),
        mHueColor(90.0f), 
        pMHueColors3i(& mHueColor.colorRGB), 
        mSimulation(mPWindow, 10, 32.0f, pMHueColors3i,
            sf::Vector2f(100.0f, 1000.0f), sf::Vector2f(100.0f, 600.0f))
{
    mWindow.setVerticalSyncEnabled(true); // VSync enabled

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
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(pTimePerFrame);
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

void Game::update(const sf::Time* deltaTime)
{
    // mBall moving to the cursor when rclicked
    if (mIsRMBPressed)
    {
        mousePos = sf::Mouse::getPosition(mWindow);
    }
    // Player logic update
    mPlayer.update(deltaTime);
    mSimulation.update(deltaTime);
    
}

void Game::render()
{
    mHueColor.rotateHue(.5f);
    //mWindow.clear(sf::Color(mBgColor.colorRGB.x, mBgColor.colorRGB.y, mBgColor.colorRGB.z));
    mWindow.clear(sf::Color(30, 0, 30));
    mSimulation.draw();
    mPlayer.draw();
    mWindow.display();
}