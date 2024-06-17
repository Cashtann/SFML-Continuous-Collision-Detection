#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public: 
	sf::Sprite playerSprite;
	Player(sf::RenderWindow* pWindow, const char* txtPath, sf::Vector2f pos);
private:
	sf::RenderWindow* mPWindow;
	sf::Vector2f mPos;
	sf::Texture mTexture;

	bool mIsMovingUp, mIsMovingDown, mIsMovingRight, mIsMovingLeft;
	bool mIsLMBPressed, mIsRMBPressed;

public:
	float playerSpeed;

	sf::Vector2f getPosition() const;

	void inputHandleKeyboard(sf::Keyboard::Key key, bool isPressed);
	void inputHandleMouse(sf::Mouse::Button button, bool isPressed);
	void inputManager();

	void move(const sf::Time* deltaTime);

	void update(const sf::Time* deltaTime);

	void draw();

};