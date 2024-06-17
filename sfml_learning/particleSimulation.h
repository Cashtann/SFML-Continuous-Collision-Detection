#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:
	// Some essentials
	sf::RenderWindow* pWindow;
	

	sf::CircleShape ballSprite;

	// Dynamics
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float borderCollisionDump;

	// Visuals
	sf::Vector3i* color;
	float radius;
	sf::Vector2f position;

	// Barriers
	sf::Vector2f hBound, vBound;


	Ball(sf::RenderWindow* pWin, 
		sf::Vector2f _position, float _radius, sf::Vector3i* _color,
		sf::Vector2f& horizontalBound, sf::Vector2f& verticalBound);
	
	void setPosition(float posX, float posY);
	sf::Vector2f getPosition() const;

	sf::CircleShape getSprite() const;

	void colorUpdate();

	void move(const sf::Time* deltaTime);

	void continousCollisionDetection(const sf::Time* deltaTime, sf::Vector2f& boundPos);

	void handleBoxCollision(const sf::Time* deltaTime);

	void update(const sf::Time* deltaTime);

	void draw();
};

class Simulation
{
private:
	std::vector<Ball> ballList;
	sf::RectangleShape mBarrier;
	sf::RenderWindow* mPWindow;
public:
	Simulation(sf::RenderWindow* pWin, 
		int count, float radius, sf::Vector3i* color, 
		sf::Vector2f horizontalBound, sf::Vector2f verticalBound);
	sf::Vector2f hBound, vBound;
	void update(const sf::Time* deltaTime);
	void draw();

};