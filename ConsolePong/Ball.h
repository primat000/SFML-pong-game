#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <conio.h>

class Ball
{
private:
	sf::CircleShape ball;
	int originalX, originalY;
	float ballRadius = 20.f;
	float ballAngle = 0.f; 
	float ballSpeed = 400.f;
public:
	Ball(int posX, int posY);
	void Reset();
	inline float getRadius() { return ballRadius; }
	inline float getBallSpeed() { return ballSpeed; }
	inline void setBallSpeed(float newSpeed) { ballSpeed = newSpeed; }
	inline sf::CircleShape* getBall() { return &ball; }
	inline float getAngle() { return ballAngle; }
	inline void setAngle(float newAngle) { ballAngle = newAngle; }
	inline const sf::Vector2f & getPosition() { return ball.getPosition(); }
	void setPosition(float x, float y);
	void Move(float deltaTime);
};
