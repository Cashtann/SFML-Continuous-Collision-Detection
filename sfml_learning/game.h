#pragma once
#include <SFML/Graphics.hpp>
#include "colorHue.h"
#include "particleSimulation.h"
#include <vector>
#include "player.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(const sf::Time* deltaTime);
    void render();
    void handleInputMouse(sf::Mouse::Button button, bool isPressed);
    void handleInputKeyboard(sf::Keyboard::Key key, bool isPressed);

private:
    const sf::Time TimePerFrame;
    const sf::Time* pTimePerFrame;

    sf::RenderWindow mWindow;
    sf::RenderWindow* mPWindow;

    // Player 
    Player mPlayer;



    // Mouse input stuff
    sf::Vector2i mousePos;
    bool mIsLMBPressed, mIsRMBPressed;

    // Fun (colors and balls)
    CustomHueRotation::ColorHueRotation mHueColor;
    sf::Vector3i* pMHueColors3i;
    Simulation mSimulation;
};