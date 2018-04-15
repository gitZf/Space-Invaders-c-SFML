#pragma once
#include <SFML/Graphics.hpp>


class enemyBullets :public sf::RectangleShape {

public:
	float bulletsSpeed;
	float bulletsX;
	float bulletsY;
	bool isFired;
	bool isDeath;


	enemyBullets();
	~enemyBullets();
	enemyBullets(float x, float y);
};
