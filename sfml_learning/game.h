#pragma once
#include <SFML/Graphics.hpp>
#include "colorHue.h"
#include "bouncingBall.h"
#include <vector>

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInputMouse(sf::Mouse::Button button, bool isPressed);
    void handlePlayerInputKeyboard(sf::Keyboard::Key key, bool isPressed);

private:
    const sf::Time TimePerFrame;

    sf::RenderWindow mWindow;
    sf::RenderWindow* pMWindow;
    sf::Texture mTexture;
    sf::Sprite mPlayer;
    sf::Font mFont;

    sf::Vector2i mousePos;

    float PlayerSpeed;
    bool mIsMovingUp, mIsMovingDown, mIsMovingRight, mIsMovingLeft;
    bool mIsLMBPressed, mIsRMBPressed;

    // Fun
    CustomHueRotation::ColorHueRotation mHueColor;
    sf::Vector3i mHueColors3i;
    sf::Vector3i* pMHueColors3i;
    Ball mBall1;
};