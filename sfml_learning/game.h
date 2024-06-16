#pragma once
#include <SFML/Graphics.hpp>
#include "colorHue.h"
#include "bouncingBall.h"
#include <vector>
#include "player.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handleInputMouse(sf::Mouse::Button button, bool isPressed);
    void handleInputKeyboard(sf::Keyboard::Key key, bool isPressed);

private:
    const sf::Time TimePerFrame;
    const sf::Time* pTimePerFrame;

    sf::RenderWindow mWindow;
    sf::RenderWindow* mPWindow;
    /*sf::Texture mTexture;
    sf::Sprite mPlayer;*/
    sf::Font mFont;

    Player mPlayer;

    sf::Vector2i mousePos;

    bool mIsLMBPressed, mIsRMBPressed;

    // Fun
    CustomHueRotation::ColorHueRotation mHueColor;
    sf::Vector3i mHueColors3i;
    sf::Vector3i* pMHueColors3i;
    Ball mBall1;
};