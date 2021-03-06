#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "GameManager.h"

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");
	window.setVerticalSyncEnabled(true);
	GameManager game(&window);
	game.run();
	return 0;
}

