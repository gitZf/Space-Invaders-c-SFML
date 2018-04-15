#pragma once
#include <SFML/Graphics.hpp>

class enemyFly :public sf::RectangleShape {



public:
	float enemySpeed;
	float enemyX;
	float enemyY;
	bool enemyDeath;
	enemyFly();
	~enemyFly();
	enemyFly(float x, float y);

};
