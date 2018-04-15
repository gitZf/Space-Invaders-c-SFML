#pragma once
#ifndef FIELDS_H
#define FILEDS_H

#include <SFML/Graphics.hpp>
#include "block.h"
#include "bullets.h"
#include "enemyBullets.h"
#include "enemy.h"
//#include "enemyFly.h"

bool leftRight = false;
bool moveDown = false;
bool isSpacePressed = false;
int countEnemyShoot = 0;
int countEnemyDeadBullets = 0;
int countShot = 0;
int countDeadBullets = 0;
int countDeadEnemy = 0;
int playerLives = 3;
bool game = true;
int isFrontCounter = 0;
//int shootEnemy[13];
int bullettsStartX = 0;
int bulletStartMoveUp = 563;
int enemyShoot = 0;
int loop = 1;
int selectEnemyToShoot = 0;
int enemyLeft = 52;
int upTo = 12;
int decrease = 1;
//bool dead = true;
bool notShoot = true;
int randomEnemy = 0;
int nextLevel = 1;
int countEnemyShootDifference = 0;

enemyBullets ebul[2000];
enemy obj[52];
enemyFly fly;
//enemy shootingEnemy[13];
bullets BObj[1000];
#endif




