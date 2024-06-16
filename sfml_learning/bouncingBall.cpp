#include <SFML/Graphics.hpp>
#include "bouncingBall.h"
#include <iostream>


Ball::Ball(sf::RenderWindow* window, sf::Vector2f position, float radius, sf::Vector3i* color)
	: mBall()
{
	mWindow = window;
	mAcceleration = sf::Vector2f(1.0f, 1.0f);
	mGForce = 10;
	mGainSpeedRatio = 0.5f;

	mPosition = position;
	mRadius = radius;
	mColor = color;

	// Setting the ball
	mBall.setOrigin(mRadius, mRadius);
	mBall.setRadius(mRadius);
	mBall.setPosition(mPosition.x, mPosition.y);
	mBall.setFillColor(sf::Color(mColor->x, mColor->y, mColor->z));
}


void Ball::setPosition(float posX, float posY)
{
	mBall.setPosition(posX, posY);
}

void Ball::colorUpdate()
{
	mBall.setFillColor(sf::Color(mColor->x, mColor->y, mColor->z));
}

void Ball::Draw()
{
	colorUpdate();
	mWindow->draw(mBall);
}
