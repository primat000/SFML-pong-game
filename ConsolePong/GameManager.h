#pragma once
#include <time.h>
#include <string> 
#include "Paddle.h"
#include "Ball.h"

class GameManager
{
private:
	const float pi = 3.14159f;
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	bool isPlaying;
	Ball *ball;
	Paddle *player1;
	Paddle *player2;
	sf::RenderWindow* window;
	sf::Text pauseMessage;
	sf::Text scoreMessage;
	sf::Font font;


public:
	GameManager(sf::RenderWindow* window);

	void ScoreUp(Paddle * player);
	
	void Draw();
	
	void  NextMove(float deltaTime);
	
	void DetectAndFixCollisions();

	void Reset();
	
	void run();

	~GameManager();
};

