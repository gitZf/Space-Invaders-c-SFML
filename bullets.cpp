#include"bullets.h"


	bullets::bullets()
	{

	}
	bullets::~bullets()
	{

	}
	bullets::bullets(float x, float y)
	{
		isFired = false;
		setSize(sf::Vector2f(3, 7));
		setFillColor(sf::Color::Yellow);
		bulletsX = x;
		bulletsY = y;
		setPosition(bulletsX, bulletsY);
		bulletsSpeed = 4.0f;
		isDeath = false;
	}

