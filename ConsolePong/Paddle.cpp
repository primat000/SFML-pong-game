#include "stdafx.h"
#include "Paddle.h"

Paddle::Paddle(sf::RenderWindow* window, int posX, int posY) 
{
	this->window = window;
	paddleSize.x = 25;
	paddleSize.y = 100;
	rectangle.setSize(paddleSize - sf::Vector2f(3, 3));
	rectangle.setOutlineThickness(3);
	rectangle.setOrigin(paddleSize / 2.f);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setFillColor(sf::Color(200, 100, 100));
	originalX = posX;
	originalY = posY;
	rectangle.setPosition(originalX, originalY);
}
void Paddle::Draw()
{
	this->window->draw(this->rectangle);
}
void Paddle::moveUp(float deltaTime)
{ 
	rectangle.move(0.f, -paddleSpeed * deltaTime);
}

void Paddle::moveDown(float deltaTime) {
	rectangle.move(0.f, paddleSpeed * deltaTime);
}
