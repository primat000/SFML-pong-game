#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Paddle
{
private:
	int originalX, originalY;
	sf::Vector2f paddleSize;
	sf::RenderWindow* window; 
	sf::RectangleShape rectangle; 
	const float paddleSpeed = 700.f;
	float ballAngle = 0.f;
public:
	Paddle(sf::RenderWindow* window, int posX, int posY);
	void Draw();
	inline void Reset() { rectangle.setPosition(originalX, originalY); }
	inline float getPaddleSpeed() { return paddleSpeed; }
	inline sf::Vector2f  getPaddleSize() { return paddleSize; }
	inline const sf::Vector2f & getPosition() { return rectangle.getPosition(); }
	void moveUp(float deltaTime);
	void moveDown(float deltaTime);
	inline sf::RectangleShape * getPaddle() { return &rectangle; }
};

