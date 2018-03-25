#include "stdafx.h"
#include "Ball.h"


Ball::Ball(int posX, int posY)
{
	ball.setRadius(ballRadius - 3);
	ball.setOutlineThickness(3);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	originalX = posX;
	originalY = posY;
	ball.setPosition(originalX, originalY);
}
void Ball::Reset()
{
	ball.setPosition(originalX, originalY);
	ballSpeed = 400.f;
	ballAngle = 0.f;
}
void Ball::setPosition(float x, float y)
{
	ball.setPosition(x, y);
}

void Ball::Move(float deltaTime)
{
	float factor = ballSpeed * deltaTime;
	ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);
}

