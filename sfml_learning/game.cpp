#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include "error.h"
#include "particleSimulation.h"

static const float SCREEN_WIDTH = 1920.0f;
static const float SCREEN_HEIGHT = 1080.0f;

void Game::resizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(SCREEN_HEIGHT * aspectRatio, SCREEN_HEIGHT);
}


Game::Game()
    : mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Application"), 
        mPWindow(& mWindow), 
        mView(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT)),
        mPlayer(mPWindow, "res/img/player.png", sf::Vector2f(500.0f, 500.0f)), 
        TimePerFrame(sf::seconds(1.f / 144.0f)), 
        pTimePerFrame(&TimePerFrame),
        mHueColor(90.0f), 
        pMHueColors3i(& mHueColor.colorRGB), 
        mSimulation(mPWindow, 1, 24.0f, pMHueColors3i,
            sf::Vector2f(0.0f, 800.0f), sf::Vector2f(0.0f, 800.0f))
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
            if (!mIsLMBPressed)
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
            resizeView(mWindow, mView);
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
    // RGB Hue rotation update
    mHueColor.rotateHue(.5f);
    // Player logic update
    mPlayer.update(deltaTime);
    // Simulation update
    mSimulation.update(deltaTime);
    
}

void Game::render()
{
    //mWindow.clear(sf::Color(mBgColor.colorRGB.x, mBgColor.colorRGB.y, mBgColor.colorRGB.z));
    
    mWindow.setView(mView);
    mView.setCenter(mPlayer.getPosition());

    mWindow.clear(sf::Color(30, 0, 30));


    mSimulation.draw();
    mPlayer.draw();

    mWindow.display();
}