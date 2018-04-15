#include "enemy.h"

	enemy::enemy() 
	{

	}
	enemy::~enemy()
	{

	}
	enemy::enemy(float x, float y, bool isF)
	{
		setSize(sf::Vector2f(30, 30));
		setFillColor(sf::Color::Blue);
		enemyX = x;
		enemyY = y;
		isFront = isF;
		isFired = false;
		setPosition(enemyX, enemyY);
		enemySpeed = getClassSpeed();
		enemyDeath = false;
		//classSpeed = 1.0f;
	}
	void enemy::setClassSpeed(float x)
	{
		classSpeed = x;
	}
	void enemy::setEnemyDestroyed()
	{
		enemyDeath = false;
	}
	void enemy::setEnemySpeed(float n)
	{
		enemySpeed = n;
	}
	float enemy::getEnemySpeed()
	{
		return enemySpeed;
	}
	void enemy::setEnemyY(float n)
	{
		enemyY = n;
	}
	void enemy::setEnemyX(float n)
	{
		enemyX = n;
	}

	float enemy::getEnemyX()
	{
		return enemyX;
	}
	float enemy::getEnemyY()
	{
		return enemyY;
	}
	void enemy::setP(float x, float y)
	{
		setPosition(x, y);
	}
	void enemy::increaseClassSpeed()
	{
		classSpeed += 0.08f;
	}
	void enemy::increaseClassSpeed(float number)
	{
		classSpeed += number;
	}
	float enemy::getClassSpeed()
	{
		return classSpeed;
	}



