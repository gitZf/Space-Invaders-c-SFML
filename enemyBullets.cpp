#include "enemyBullets.h"

	enemyBullets::enemyBullets()
	{

	}
	enemyBullets::~enemyBullets()
	{

	}
	enemyBullets::enemyBullets(float x, float y)
	{
		isFired = false;
		setSize(sf::Vector2f(3, 7));
		setFillColor(sf::Color::Yellow);
		bulletsX = x;
		bulletsY = y;
		setPosition(bulletsX, bulletsY);
		bulletsSpeed = 3.0f;
		isDeath = false;
	}

