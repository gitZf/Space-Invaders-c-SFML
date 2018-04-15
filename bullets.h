#pragma once

#include <SFML/Graphics.hpp>

class bullets :public sf::RectangleShape {

public:
	float bulletsSpeed;
	float bulletsX;
	float bulletsY;
	bool isFired;
	bool isDeath;
	int countBullet;

	bullets();
	~bullets();
	bullets(float x, float y);
};
