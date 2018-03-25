#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager(sf::RenderWindow* window)
{
	isPlaying = false;
	this->window = window;
	score1 = score2 = 0;
	width = window->getSize().x; height = window->getSize().y;
	ball = new Ball(width / 2, height / 2);
	player1 = new Paddle(window, 16, window->getSize().y / 2);
	player2 = new Paddle(window, window->getSize().x - 12, window->getSize().y / 2);
	font.loadFromFile("ARIAL.TTF");
	pauseMessage.setFont(font);
	scoreMessage.setFont(font);
	pauseMessage.setCharacterSize(40);
	scoreMessage.setCharacterSize(20);
	pauseMessage.setPosition(170.f, 150.f);
	scoreMessage.setPosition(200.f, 40.f);
	pauseMessage.setFillColor(sf::Color::White);
	scoreMessage.setFillColor(sf::Color::Black);
	pauseMessage.setString("Welcome to SFML pong!\nPress space to start the game");
	scoreMessage.setString("Player1 = " + std::to_string(score1) + "\t\t\t\t\t\t\t\t\t Player2 = " + std::to_string(score2));
}
void GameManager::ScoreUp(Paddle * player)
{
	if (player == player1) score1++;
	else if (player == player2) score2++;
}
void GameManager::Draw()
{
	window->draw(*player1->getPaddle());
	window->draw(*player2->getPaddle());
	window->draw(*ball->getBall());
	window->draw(scoreMessage);
}
void GameManager::NextMove(float deltaTime)
{
	// Left paddle move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
		(player1->getPaddle()->getPosition().y - player1->getPaddle()->getSize().y / 2 > 5.f))
	{
		player1->moveUp(deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
		(player1->getPaddle()->getPosition().y + player1->getPaddle()->getSize().y / 2 < height - 5.f))
	{
		player1->moveDown(deltaTime);
	}

	// Right paddle move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		(player2->getPaddle()->getPosition().y - player2->getPaddle()->getSize().y / 2 > 5.f))
	{
		player2->moveUp(deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		(player2->getPaddle()->getPosition().y + player2->getPaddle()->getSize().y / 2 < height - 5.f))
	{
		player2->moveDown(deltaTime);
	}
	// Ball move
	ball->Move(deltaTime);
}
void GameManager::DetectAndFixCollisions()
{
	// Check collisions between the ball and the screen
	if (ball->getBall()->getPosition().x - ball->getRadius() < 0.f)
	{
		ScoreUp(player2);
		isPlaying = false;
		//pauseMessage.setString("You lost!\nPress space to restart or\nescape to exit");
		scoreMessage.setString("Player1 = " + std::to_string(score1) + "\t\t\t\t\t\t\t\t\t Player2 = " + std::to_string(score2));
	}
	if (ball->getBall()->getPosition().x + ball->getRadius() > width)
	{
		ScoreUp(player1);
		isPlaying = false;
		//pauseMessage.setString("You won!\nPress space to restart or\nescape to exit");
		scoreMessage.setString("Player1 = " + std::to_string(score1) + "\t\t\t\t\t\t\t\t\t Player2 = " + std::to_string(score2));
	}
	if (ball->getBall()->getPosition().y - ball->getRadius() < 0.f)
	{
		ball->setAngle(-ball->getAngle());
		ball->getBall()->setPosition(ball->getBall()->getPosition().x, ball->getRadius() + 0.1f);
	}
	if (ball->getBall()->getPosition().y + ball->getRadius() > height)
	{
		ball->setAngle(-ball->getAngle());
		ball->getBall()->setPosition(ball->getBall()->getPosition().x, height - ball->getRadius() - 0.1f);
	}
	// Ñollision between paddles and ball
	// Left Paddle
	if (ball->getPosition().x - ball->getRadius() < player1->getPosition().x + player1->getPaddleSize().x / 2 &&
		ball->getPosition().x - ball->getRadius() > player1->getPosition().x &&
		ball->getPosition().y + ball->getRadius() >= player1->getPosition().y - player1->getPaddleSize().y / 2 &&
		ball->getPosition().y - ball->getRadius() <= player1->getPosition().y + player1->getPaddleSize().y / 2)
	{
		if (ball->getPosition().y > player1->getPosition().y)
			ball->setAngle(pi - ball->getAngle() + (std::rand() % 20) * pi / 180);
		else
			ball->setAngle(pi - ball->getAngle() - (std::rand() % 20) * pi / 180);

		ball->setBallSpeed(ball->getBallSpeed() + 10.f); //increase ball speed
		ball->setPosition(player1->getPosition().x + ball->getRadius() + player1->getPaddleSize().x / 2 + 0.1f, ball->getPosition().y);
	}
	//Right Paddle
	if (ball->getPosition().x + ball->getRadius() > player2->getPosition().x - player2->getPaddleSize().x / 2 &&
		ball->getPosition().x + ball->getRadius() < player2->getPosition().x &&
		ball->getPosition().y + ball->getRadius() >= player2->getPosition().y - player2->getPaddleSize().y / 2 &&
		ball->getPosition().y - ball->getRadius() <= player2->getPosition().y + player2->getPaddleSize().y / 2)
	{
		if (ball->getPosition().y > player2->getPosition().y)
			ball->setAngle(pi - ball->getAngle() + (std::rand() % 20) * pi / 180);
		else
			ball->setAngle(pi - ball->getAngle() - (std::rand() % 20) * pi / 180);

		ball->setBallSpeed(ball->getBallSpeed() + 10.f); //increase ball speed
		ball->setPosition(player2->getPosition().x - ball->getRadius() - player2->getPaddleSize().x / 2 - 0.1f, ball->getPosition().y);
	}


}
void GameManager::Reset()
{
	player1->Reset();
	player2->Reset();
	ball->Reset();
}
void GameManager::run()
{
	sf::Clock clock;
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event)) // closed by Esc
		{
			if (event.type == sf::Event::Closed || 
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window->close();
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
				if (!isPlaying)
				{
					// (re)start the game
					isPlaying = true;
					clock.restart();
					// Reset the position of the paddles and ball
					Reset();
				}
		}

		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();
			NextMove(deltaTime);
			DetectAndFixCollisions();
		}

		// Clear
		window->clear(sf::Color(50, 200, 50));

		if (isPlaying)
			Draw();
		else
		{
			if (score1 != 0 || score2 != 0)
				pauseMessage.setString("Score " 
					+ std::to_string(score1) 
					+ ":" 
					+ std::to_string(score2));
			window->draw(pauseMessage);
		}

		window->display();
	}
}
GameManager::~GameManager()
{
	delete ball;
	delete player1;
	delete player2;
}
