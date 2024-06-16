#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::RenderWindow* mWindow;
	sf::CircleShape mBall;

	sf::Vector2f mAcceleration;
	float mGForce;
	float mGainSpeedRatio;
	sf::Vector2f mPosition;
	float mRadius;
	sf::Vector3i* mColor;
public:
	Ball(sf::RenderWindow* window, sf::Vector2f position, float radius, sf::Vector3i* color);
	void setPosition(float posX, float posY);

	void colorUpdate();
	void Draw();
};