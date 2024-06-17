#include <SFML/Graphics.hpp>
#include "particleSimulation.h"
#include <iostream>


Ball::Ball(sf::RenderWindow* pWin,  
	sf::Vector2f _position, float _radius, sf::Vector3i* _color,
	sf::Vector2f& horizontalBound, sf::Vector2f& verticalBound)
	: ballSprite()
{
	// Essentials
	pWindow = pWin;

	// Dynamics
	acceleration = sf::Vector2f(0.0f, 1000.0f);
	collisionDump = 1.0f;
	velocity = sf::Vector2f(0.0f, 0.0f);

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

	/*barrier.setSize(sf::Vector2f(xLimit.y - xLimit.x, yLimit.y - yLimit.x));
	barrier.setPosition(sf::Vector2f(xLimit.x, yLimit.x));
	barrier.setOutlineThickness(10.0f);
	barrier.setFillColor(sf::Color::Transparent);
	barrier.setOutlineColor(sf::Color(255, 255, 255));*/
}

// Getters and setters
void Ball::setPosition(float posX, float posY)
{
	ballSprite.setPosition(posX, posY);
}

sf::Vector2f Ball::getPosition()
{
	return ballSprite.getPosition();
}

sf::CircleShape Ball::getSprite()
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
	velocity += acceleration * (*deltaTime).asSeconds();
	ballSprite.move(velocity * (*deltaTime).asSeconds());
	handleBoxCollision();
	
}

void Ball::handleBoxCollision()
{
	if ((position.x - radius <= hBound.x) || (position.x + radius >= hBound.y))
	{
		velocity.x = -velocity.x;
	}
	if ((position.x - radius <= vBound.x) || (position.x + radius >= vBound.y))
	{
		velocity.y = -velocity.y;
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
	hBound = horizontalBound;
	vBound = verticalBound;
	ballList.reserve(count);
	for (int i = 0; i < count; i++)
	{
		ballList.emplace_back(pWin, 
			sf::Vector2f((200.0f + 1.0f * i * radius), 300.0f), 
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
}