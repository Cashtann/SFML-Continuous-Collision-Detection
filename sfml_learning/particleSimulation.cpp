#include <SFML/Graphics.hpp>
#include "particleSimulation.h"
#include <iostream>
#include <random>
#include <ctime>
#include <math.h>
#include <cassert>



Ball::Ball(sf::RenderWindow* pWin,  
	sf::Vector2f _position, float _radius, sf::Vector3i* _color,
	sf::Vector2f& horizontalBound, sf::Vector2f& verticalBound)
	: ballSprite()
{
	// Essentials
	pWindow = pWin;

	// Dynamics
	acceleration = sf::Vector2f(0.0f, 0.0f);
	borderCollisionDump = 0.7f;
	velocity = sf::Vector2f(0.0f, -200.0f);

	// Visuals
	position = _position;
	radius = _radius;
	color = _color;

	// Setting the ball
	ballSprite.setOrigin(radius, radius);
	ballSprite.setRadius(radius);
	ballSprite.setPosition(position.x, position.y);
	ballSprite.setFillColor(sf::Color(color->x, color->y, color->z));

	// Barriers
	hBound = horizontalBound;
	vBound = verticalBound;
}

// Getters and setters
void Ball::setPosition(float posX, float posY)
{
	ballSprite.setPosition(posX, posY);
}

sf::Vector2f Ball::getPosition() const
{
	return ballSprite.getPosition();
}

sf::CircleShape Ball::getSprite() const
{
	return ballSprite;
}


// Movement
void Ball::move(const sf::Time* deltaTime)
{
	/*
	ballSprite.move(sf::Vector2f(velocity.x * (*deltaTime).asSeconds(), 
		velocity.y * (*deltaTime).asSeconds()));
	*/
	position = ballSprite.getPosition();

	velocity += acceleration * (*deltaTime).asSeconds();
	ballSprite.move(velocity * (*deltaTime).asSeconds());
	handleBoxCollision(deltaTime);
	
}

void Ball::handleBoxCollision(const sf::Time* deltaTime)
{

	/// Discrete Collision Detection
	/*
	if ((position.x - radius) <= hBound.x) // Left barrier
	{
		velocity.x = -velocity.x;
		velocity *= borderCollisionDump;
	}
	if ((position.x + radius) >= hBound.y) // Right barrier
	{
		velocity.x = -velocity.x;
		velocity *= borderCollisionDump;
	}
	if ((position.y - radius) <= vBound.x) // Upper barrier
	{
		velocity.y = -velocity.y;
		velocity /= borderCollisionDump;
	}
	if ((position.y + radius) >= vBound.y) // Lower barrier
	{
		velocity.y = -velocity.y;
		velocity *= borderCollisionDump;
	}
	*/

	/// Continous Collision Detection
	continousCollisionDetection(deltaTime, vBound);


}

void Ball::continousCollisionDetection(const sf::Time* deltaTime, sf::Vector2f& boundPos)
{
	float collideTime;
	/// Vertical Collision Detection

	if (position.y + (velocity.y * (*deltaTime).asSeconds() - radius) <= boundPos.x) // Upper barrier
	{
		collideTime = (position.y - boundPos.x - radius)
			/ (position.y - velocity.y * (*deltaTime).asSeconds());
		std::cout << collideTime << " up\n";
		while (true){}
		
	}
	if (position.y + (velocity.y * (*deltaTime).asSeconds() + radius) >= boundPos.y) // Lower barrier
	{
		collideTime = (boundPos.y - radius - position.y)
			/ (velocity.y * (*deltaTime).asSeconds() - position.y);
		std::cout << collideTime << " down\n";
		while (true) {}
	}
	

}

// Updating
void Ball::draw()
{
	pWindow->draw(ballSprite);
}

void Ball::colorUpdate()
{
	ballSprite.setFillColor(sf::Color(color->x, color->y, color->z));
}

void Ball::update(const sf::Time* deltaTime)
{
	move(deltaTime);
	colorUpdate();
}

Simulation::Simulation(sf::RenderWindow* pWin,  
	int count, float radius, sf::Vector3i* color,
	sf::Vector2f horizontalBound, sf::Vector2f verticalBound)
{
	mPWindow = pWin;
	hBound = horizontalBound;
	vBound = verticalBound;

	mBarrier.setSize(sf::Vector2f(hBound.y - hBound.x, vBound.y - vBound.x));
	mBarrier.setPosition(sf::Vector2f(hBound.x, vBound.x));
	mBarrier.setOutlineThickness(10.0f);
	mBarrier.setFillColor(sf::Color::Transparent);
	mBarrier.setOutlineColor(sf::Color(255, 255, 255));


	ballList.reserve(count);
	std::mt19937 mt(time(nullptr));
	int particlesPerRow = (int)std::sqrt(count);
	int particlesPerCol = (count - 1) / particlesPerRow + 1;
	float spacing = radius * 2 + radius;
	for (int i = 0; i < count; i++)
	{
		float x = (i % particlesPerRow - particlesPerRow / 5.5f + 1.0f) * spacing;
		float y = (i / particlesPerRow - particlesPerCol / 5.5f + 1.0f) * spacing;

		ballList.emplace_back(pWin, 
			sf::Vector2f({x + 100.0f, y + 100.0f}),
			radius, color, hBound, vBound);
	}
}

void Simulation::update(const sf::Time* deltaTime)
{
	int vecsize = (int)ballList.size();
	for (int i = 0; i < vecsize; i++)
	{
		ballList[i].update(deltaTime);
	}
}

void Simulation::draw()
{
	int vecsize = (int)ballList.size();
	for (int i = 0; i < vecsize; i++)
	{
		ballList[i].draw();
	}
	mPWindow->draw(mBarrier);
}