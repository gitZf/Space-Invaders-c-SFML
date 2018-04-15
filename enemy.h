#pragma once


#include <SFML/Graphics.hpp>

class enemy :public sf::RectangleShape {
	


public:
	float enemySpeed;
	float enemyX;
	float enemyY;
	float classSpeed = 0.5f;
	bool enemyDeath;
	bool isFront;
	bool isFired;

	enemy();
	~enemy();
	enemy(float x, float y, bool isF);

	void setEnemySpeed(float n);
	float getEnemySpeed();
	void setEnemyY(float n);
	void setEnemyX(float n);
	void setEnemyDestroyed();
	float getEnemyX();
	float getEnemyY();
	void setP(float x, float y);
	void increaseClassSpeed();
	void increaseClassSpeed(float number);
	float getClassSpeed();
	void setClassSpeed(float x);

};
