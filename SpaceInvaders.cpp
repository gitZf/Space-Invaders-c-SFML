#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "block.h"
#include "bullets.h"
#include "enemyBullets.h"
//#include "fields.h"
#include "enemy.h"
#include "enemyFly.h"
#include "lives.h"
#include "player.h"
#include <thread>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

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

void buildShelter(block blockObj[36], sf::Texture &meteor)
{
	float bblockX = 150;
	float bblockY = 450;
	float tempx = 0;
	float tempy = 0;
		int counter = 0;
		for(int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				bblockX += 20;
				if (bblockY == 480 && bblockX == 190 || bblockY == 480 && bblockX == 390 || bblockY == 480 && bblockX == 590)
				{
					//Do nothing
				}
				else
				{
					blockObj[counter] = block(bblockX, bblockY);
					blockObj[counter].setTexture(&meteor);
					counter++;
				}
				
			}
			bblockX += 140;
			if (bblockX == 750)
			{
				bblockX = 150;
				bblockY += 10;
			}
			
			if (bblockX == 0 && bblockY == -50)
			{
				bblockX = tempx;
				bblockY = tempy;
			}

		}
		
	
}

void resetBullets()
{
	int x = 0;
	int y = 60;
	enemyLeft = 52;

	playerLives = 3;

	countEnemyShoot = 0;
	countEnemyDeadBullets = 0;
	countShot = 0;
	countDeadBullets = 0;


	for (int i = 0; i < 52; i++)
	{
		
		x += 40;
		if (x >= 560)
		{
			x = 40;
			y += 50;
		}
		if (i > 39)
			obj[i].isFront = true;
		else
			obj[i].isFront = false;
		obj[i].setEnemyX(x);
		obj[i].setEnemyY(y);
		obj[i].isFired = false;
		obj[i].setEnemyDestroyed();
		obj[i].setPosition(x, y);

	}

	for (int i = 0; i < 2000; i++)
	{
		ebul[i].isFired = false;
		ebul[i].isDeath = false;
		if (i < 1000)
		{
			BObj[i].bulletsY = 563;
			BObj[i].bulletsX = 0;
			BObj[i].isDeath = false;
			BObj[i].isFired = true;
		}

	}

}

int main()
{
	
	// fly explosion sfml sound
		sf::SoundBuffer sfflySoundExplosion;
	if (!sfflySoundExplosion.loadFromFile("sound/flyExplosion.wav"))
	{
		//error load file
		cout << "Error load sfml audio fly sound" << endl;
	}
	sf::Sound soundFlyExplode;
	soundFlyExplode.setBuffer(sfflySoundExplosion);

	//fly sfml sound
	sf::SoundBuffer sfflySound;
	if (!sfflySound.loadFromFile("sound/fly.wav"))
	{
		//error load file
		cout << "Error load sfml audio fly sound" << endl;
	}
	sf::Sound soundFly;
	soundFly.setBuffer(sfflySound);
	//soundFly.play();

	//shoot sfml sound
	sf::SoundBuffer laser;
	if (!laser.loadFromFile("sound/shoot.wav"))
	{
		//error load file
		cout << "Error load sfml audio laser sound" << endl;
	}
	sf::Sound soundLaser;
	soundLaser.setBuffer(laser);
	//soundLaser.play();

	sf::SoundBuffer sfexplosion;
	if (!sfexplosion.loadFromFile("sound/invaderkilled.wav"))
	{
		//error load file
		cout << "Error load sfml audio explosion sound" << endl;
	}
	sf::Sound soundExplosion;
	soundExplosion.setBuffer(sfexplosion);
	//soundExplosion.play();

	sf::SoundBuffer sfinvaderkill;
	if (!sfinvaderkill.loadFromFile("sound/explosion.wav"))
	{
		//error load file
		cout << "Error load sfml audio invaderkill sound" << endl;
	}
	sf::Sound soundInvaderkilled;
	soundInvaderkilled.setBuffer(sfinvaderkill);
	//soundInvaderkilled.play();

	//enemy shoot sfml sound
	sf::SoundBuffer enemyShoot;
	if (!enemyShoot.loadFromFile("sound/enemyShoot.wav"))
	{
		//error load file
		cout << "Error load sfml audio enemyShoot sound" << endl;
	}
	sf::Sound soundEnemyShoot;
	soundEnemyShoot.setBuffer(enemyShoot);
	bool win = false;
	int score = 0;
	int kill = 30;
	int level = 1;
	bool levelUp = false;
	//bool gameWinner = false;
	bool playSound = false;
	int highScoreInt = 0;
	int flyCount = 0;
	//get High score from file score.txt
	std::ifstream file("score/score.txt");
	std::string str;
	int tempScore = 0;
	while (std::getline(file, str))
	{
		//cout << str<<"\n";
		tempScore = stoi(str);
		if (tempScore > highScoreInt)
			highScoreInt = tempScore;
	}
	sf::Vertex lineTop[] =//horizontal line
	{
		sf::Vertex(sf::Vector2f(0, 50)),
		sf::Vertex(sf::Vector2f(800, 50))
	};
	sf::Vertex line[] =//horizontal line
	{
		sf::Vertex(sf::Vector2f(0, 600)),
		sf::Vertex(sf::Vector2f(800, 600))
	};

	//font
	sf::Font font;
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Can't load font";
	}

	//Menu option
	sf::Text play;
	play.setFont(font);
	//play.setFillColor(sf::Color::Green);
	play.setCharacterSize(44);
	play.setStyle(sf::Text::Bold);
	play.setString("Play again");
	play.setPosition(sf::Vector2f(320, 350));
	sf::Text exit;
	exit.setFont(font);
	//exit.setFillColor(sf::Color::Red);
	exit.setCharacterSize(44);
	exit.setStyle(sf::Text::Bold);
	exit.setString("Exit game");
	exit.setPosition(sf::Vector2f(320, 450));
	
      	//Player score text
	sf::Text scoreText;
	//scoreText.setFillColor(sf::Color::Green);
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setPosition(sf::Vector2f(10, 10));
	scoreText.setString("Score : " + std::to_string(score));
	//Player Level text
	sf::Text playerLevel;
	//playerLevel.setFillColor(sf::Color::Green);
	playerLevel.setFont(font);
	playerLevel.setCharacterSize(24);
	playerLevel.setStyle(sf::Text::Bold);
	playerLevel.setPosition(sf::Vector2f(680, 10));
	playerLevel.setString("Level : " + std::to_string(level));
	//High Score message
	sf::Text highScore;
	//highScore.setFillColor(sf::Color::Red);
	highScore.setFont(font);
	highScore.setCharacterSize(24);
	highScore.setStyle(sf::Text::Bold);
	highScore.setPosition(sf::Vector2f(300, 10));
	highScore.setString("High Score : " + std::to_string(highScoreInt));
	//New High Score messasge
	sf::Text newHighScore;
	//newHighScore.setFillColor(sf::Color::Yellow);
	newHighScore.setFont(font);
	newHighScore.setCharacterSize(44);
	newHighScore.setStyle(sf::Text::Bold);
	newHighScore.setString("New Record : " + std::to_string(score));
	newHighScore.setPosition(sf::Vector2f(200, 100));
	//Game message
	sf::Text messageTXT;
	//messageTXT.setFillColor(sf::Color::Yellow);
	messageTXT.setFont(font);
	messageTXT.setCharacterSize(44);
	messageTXT.setStyle(sf::Text::Bold);
	messageTXT.setString("Default Message");
	messageTXT.setPosition(sf::Vector2f(320, 250));
	//Arrow up - Down
	sf::Texture upDown;
	if (!upDown.loadFromFile("images/UD.png"))
	{
		std::cout << "Error load image";
	}
	//lives arrow = lives(390, 420, upDown);
	sf::RectangleShape arrow(sf::Vector2f(100, 70));
	float arrowX = 370;
	float arrowY = 400;
	float playerSpeed = 1.0f;
	arrow.setPosition(arrowX, arrowY);
	arrow.setTexture(&upDown);

	
	//bool alreadyWin = false;

	enemy en;//static member of enemy class
	
	//create meteor objects
	sf::Texture meteor;
	if (!meteor.loadFromFile("images/meteor.png"))
	{
		std::cout << "Error load image";
	}
	//create blok array
	block blockObj[33];
	float bblockX = 150;
	float bblockY = 450;
	float tempx = 0;
	float tempy = 0;
	//build meteor objets
	buildShelter(blockObj, meteor);
	
	//create bulets objets
	for (int i = 0; i < 1000; i++)
	{
		BObj[i] = bullets(bullettsStartX, bulletStartMoveUp);
	}
	for (int i = 0; i < 2000; i++)
	{
		ebul[i] = enemyBullets(0, 0);
	}
	//create fly object
	sf::Texture flyTexture;
	if (!flyTexture.loadFromFile("images/enemyFly.png"))
	{
		std::cout << "Error load image";
	}
	fly = enemyFly(0, -60);
	fly.setTexture(&flyTexture);
	int x = 0;
	int y = 60;
	bool front = false;
	sf::Texture enemyTexture;
	sf::Texture enemyTexture1;
	if (!enemyTexture.loadFromFile("images/enemy1.png"))
	{
		std::cout << "Error load image";
	}
	if (!enemyTexture1.loadFromFile("images/enemy2.png"))
	{
		std::cout << "Error load image";
	}

	//create enemy objects
	for (int i = 0; i < 52; i++)
	{
		x += 40;
		if (x >= 560)
		{
			x = 40;
			y += 50;
		}
		if (i>39)
			front = true;
		else
			front = false;
		obj[i] = enemy(x, y, front);
		if (i % 2 == 0)
			obj[i].setTexture(&enemyTexture);
		else
			obj[i].setTexture(&enemyTexture1);

	}
	//******************************************************************************************
	sf::RenderWindow window(sf::VideoMode(800, 650), "Space Invaders C++");
	window.setMouseCursorVisible(false);

	// setup any shapes or variables.
	sf::Texture backgroundPic;
	sf::Sprite background;
	sf::Vector2u TextureSize;  //Added to store texture size.
	sf::Vector2u WindowSize;   //Added to store window size.
	if (!backgroundPic.loadFromFile("images/space.png"))
	{
		std::cout << "Error load image";
	}
	else
	{
		TextureSize = backgroundPic.getSize(); //Get size of texture.
		WindowSize = window.getSize();             //Get size of window.

		float ScaleX = (float)WindowSize.x / TextureSize.x;
		float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.

		background.setTexture(backgroundPic);
		background.setScale(ScaleX, ScaleY);      //Set scale.  
	}

	//sf::RectangleShape player(sf::Vector2f(70, 30));
	sf::Texture texture;
	if (!texture.loadFromFile("images/ship1.png"))
	{
		std::cout << "Error load image";
	}

	//player.setTexture(&texture);
	player player1 = player(0, 560, texture);
	lives live1 = lives(0, 610, texture);
	lives live2 = lives(100, 610, texture);
	lives live3 = lives(200, 610, texture);

	// set timepeFrame to 1 60th of a second. 60 frames per second
	sf::Time timePerFrame = sf::seconds(1.0f / 200.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	// the clock object keeps the time.
	sf::Clock clock;
	clock.restart();

	//window.setFramerateLimit(160);
	while (window.isOpen())
	{

		// chek if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();
		//update every 60th of a second
		//only when the time since last update is greate than 1/60 update the world.

		
		if (timeSinceLastUpdate > timePerFrame)
		{

			// get keyboard input.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				player1.playerX = player1.playerX - player1.playerSpeed;
				if (player1.playerX <= -30)
					player1.playerX = 730;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player1.playerX = player1.playerX + player1.playerSpeed;
				if (player1.playerX > 760)
					player1.playerX = 0;
			}
			// shoting to target
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isSpacePressed == false)
			{
				int bulletx = BObj[countShot].bulletsX = player1.playerX + 35;
				BObj[countShot].setPosition(bulletx, 563);
				BObj[countShot].isFired = true;
				countShot++;
				isSpacePressed = true;
				soundLaser.play();/*******************************player shot **********************************************/

			}
		
			// update player position
			player1.setPosition(player1.playerX, player1.playerY);
			// clear the screen and draw all the shapes
			window.clear();
			window.draw(background);
			//left to right and mov down control
			if (leftRight == false && game)
			{
				int mostRight = 0;
				float rx;
				float ry;
				for (int i = 0; i < 52; i++)
				{

					if (obj[i].enemyDeath == false)
					{
						rx = obj[i].getEnemyX() + en.getClassSpeed(); 
						ry = obj[i].getEnemyY();
						obj[i].setEnemyX(rx);
						obj[i].setEnemyY(ry);
						obj[i].setPosition(rx, ry);
					}
					if (rx > mostRight)
						mostRight = rx;
					if (mostRight >= 780)//if any object get to right side set true
					{
						leftRight = true;
						mostRight = 0;
						moveDown = true;
					}
				}

			}
			else if (leftRight&&game)
			{
				int mostLeft = 780;
				float lx;
				float ly;
				for (int i = 0; i < 52; i++)
				{
					if (obj[i].enemyDeath == false)
					{
						lx = obj[i].getEnemyX() - en.getClassSpeed();
						ly = obj[i].getEnemyY();
						obj[i].setEnemyX(lx);
						obj[i].setEnemyY(ly);
						obj[i].setPosition(lx, ly);
					}

					if (lx < mostLeft)
						mostLeft = lx;
					if (mostLeft <= 0)//if any object get to left side set false
					{
						leftRight = false;
						mostLeft = 800;
						moveDown = true;
					}
				}
			}
			if (moveDown&&game)//move down enemies
			{
				kill -= 2;
				float y = 0;
				for (int i = 0; i < 52; i++)
				{
					if (obj[i].enemyDeath == false)
					{
						y = obj[i].getEnemyY();
						obj[i].setEnemyY(y + 10);
						if (y > 600)//if enemy beyond player
						{
							game = false;
						}

					}

				}
				moveDown = false;
			}
			//player bullets position control
			for (int b = countDeadBullets; b < countShot; b++)
			{
				if (BObj[b].isFired)
				{
					if (BObj[b].bulletsY < 0)
					{
						BObj[b].isFired = false;
						countDeadBullets++;
					}
					else
					{
						if (BObj[b].isDeath == false)
						{
							BObj[b].bulletsY = BObj[b].bulletsY - BObj[0].bulletsSpeed;
							float by = BObj[b].bulletsY;
							float bx = BObj[b].bulletsX;
							BObj[b].setPosition(bx, by);
							window.draw(BObj[b]);
						}
					}
				}
			}

			for (int b = countDeadBullets; b < countShot; b++)//player bullet colision with walls
			{
				for (int i = 0; i < 33; i++)
				{
					if (BObj[b].getGlobalBounds().intersects(blockObj[i].getGlobalBounds()) && blockObj[i].isDestroyed == false)
					{
						BObj[b].isDeath = true;
						blockObj[i].isDestroyed = true;
 						blockObj[i].blockX = 400;
						blockObj[i].blockY = -50;
						blockObj[i].setPosition(bblockX, bblockY);
						countDeadBullets++;
					}
					else if (BObj[b].getGlobalBounds().intersects(ebul[i].getGlobalBounds()) && BObj[b].isDeath == false && ebul[i].isDeath == false)
					{
						BObj[b].isDeath = true;
						BObj[b].bulletsY = -50;
						ebul[i].bulletsY = 800;
						ebul[i].isDeath = true;
						score += 150;
						scoreText.setString("Score : " + std::to_string(score));
						countDeadBullets++;
					}

				}
			}
			for (int i = 0; i < 52; i++)//colision detection for enemy and player bullets and fly
			{
				for (int b = countDeadBullets; b < countShot; b++)
				{

					if (obj[i].getGlobalBounds().intersects(BObj[b].getGlobalBounds()) && obj[i].enemyDeath == false && BObj[b].isDeath == false)
					{
						enemyLeft--;
						en.increaseClassSpeed(0.07);
						if (enemyLeft < 10)
						{
							en.increaseClassSpeed(0.35);
						}
						if (game)
						{
							score += kill;
							scoreText.setString("Score : " + std::to_string(score));
						}

						obj[i].setPosition(50, -50);
						obj[i].enemyDeath = true;
						obj[i].isFront = false;
						if (i - 13>0)
							obj[i - 13].isFront = true;
						BObj[b].setPosition(50, -50);
						BObj[b].isDeath = true;
						window.draw(obj[i]);
						soundExplosion.play();/****************************enemy destroy********************************/
						countDeadBullets++;
					}
					else if (BObj[b].getGlobalBounds().intersects(fly.getGlobalBounds()) && fly.enemyDeath == false)
					{
						BObj[b].isDeath = true;
						fly.enemyX = 0;
						fly.enemyY = -60;
						if(game)
							score += 450;
						fly.enemyDeath = true;
						scoreText.setString("Score : " + std::to_string(score));
						flyCount = 500;
						countDeadBullets++;
						soundFly.stop();//stop playing sound
						soundFlyExplode.play();
					}
				}
			}

			if (loop % 50 == 0 && game)//enemy shoot every 50 iterations *************************************************enemy shooting
			{
				countEnemyShootDifference += 1;
				randomEnemy = enemyLeft;
				if (enemyLeft == 0)
					notShoot = false;
				while (notShoot)
				{
					if (obj[randomEnemy].enemyDeath == false && obj[randomEnemy].isFront == true && obj[randomEnemy].isFired == false)
					{
						obj[randomEnemy].isFired = true;
						ebul[countEnemyShoot].bulletsY = (obj[randomEnemy].getEnemyY() + 20) - BObj[0].bulletsSpeed;
						ebul[countEnemyShoot].bulletsX = obj[randomEnemy].getEnemyX() + 10;
						float by = ebul[countEnemyShoot].bulletsY;
						float bx = ebul[countEnemyShoot].bulletsX;
						ebul[countEnemyShoot].setPosition(bx, by);
						soundEnemyShoot.play();/************************************enemy shooting**********************************/
						ebul[countEnemyShoot].isFired = true;
						countEnemyShoot++;
						window.draw(ebul[countEnemyShoot]);
						notShoot = false;
					}
					randomEnemy--;
					if (randomEnemy <= 0)
						randomEnemy = 52;
					selectEnemyToShoot++;
					if (selectEnemyToShoot >= 52)
					{
						notShoot = false;
						selectEnemyToShoot = 0;
					}
				}
				notShoot = true;
			}
			if (countEnemyShootDifference == 12)
			{
				countEnemyShootDifference = 0;
				for (int i = 0; i < 52; i++)
				{
					obj[i].isFired = false;
				}
			}

			for (int b = countEnemyDeadBullets; b < countEnemyShoot; b++)//draw enemy bullets
			{
				if (ebul[b].isFired)
				{
					if (ebul[b].bulletsY >= 800)
					{
						ebul[b].isFired = false;
						countEnemyDeadBullets++;
					}
					else
					{
						if (ebul[b].isDeath == false)
						{
							ebul[b].bulletsY = ebul[b].bulletsY + ebul[0].bulletsSpeed;
							float by = ebul[b].bulletsY;
							float bx = ebul[b].bulletsX;
							ebul[b].setPosition(bx, by);
							window.draw(ebul[b]);
						}
					}
				}
			}

			for (int b = countEnemyDeadBullets; b < countEnemyShoot; b++)//enemy bullet intersect with player and walls
			{

				for (int i = 0; i < 33; i++)
				{
					if (ebul[b].getGlobalBounds().intersects(blockObj[i].getGlobalBounds()) && blockObj[i].isDestroyed == false)
					{
						ebul[b].isDeath = true;
						blockObj[i].isDestroyed = true;
						blockObj[i].blockX = 400;
						blockObj[i].blockY = -50;
						blockObj[i].setPosition(bblockX, bblockY);
					}
				}
				if (ebul[b].getGlobalBounds().intersects(player1.getGlobalBounds()) && ebul[b].isDeath == false)
				{
					playerLives -= 1;
					score -= 150;
					scoreText.setString("Score : " + std::to_string(score));
					player1.playerX = 0;
					player1.playerY = 530;
					soundInvaderkilled.play();/******************************** player died **************************/
					b = countEnemyShoot;
					if (playerLives == 0)
					{
						game = false;
					}

				}
			}

			window.draw(lineTop, 5, sf::Lines);


			window.draw(line, 5, sf::Lines);

			for (int i = 0; i < 52; i++)//draw alive enemies
			{
				if (obj[i].enemyDeath == false)
				{
					if (loop % 60 == 0)
					{
						if (i % 2 == 0)
							obj[i].setTexture(&enemyTexture);
						else
							obj[i].setTexture(&enemyTexture1);
					}
					else if (loop % 30 == 0)
					{
						if (i % 2 == 0)
							obj[i].setTexture(&enemyTexture1);
						else
							obj[i].setTexture(&enemyTexture);
					}
					window.draw(obj[i]);
				}
			}
			if (playerLives == 3)//player life display
			{
				window.draw(live1);
				window.draw(live2);
				window.draw(live3);
			}
			else if (playerLives == 2)
			{
				window.draw(live1);
				window.draw(live2);
			}
			else if (playerLives == 1)
			{
				window.draw(live1);
			}
			window.draw(player1);

			for (int i = 0; i < 33; i++)//draw walls
			{
				if (blockObj[i].isDestroyed == false)
					window.draw(blockObj[i]);
			}
			for (int b = 0; b < 52 - countDeadEnemy; b++)//if enemy reach player
			{
				if (obj[b].getGlobalBounds().intersects(player1.getGlobalBounds()) && obj[b].enemyDeath == false)
				{
					if (game)
					{
						score -= 150;
						scoreText.setString("Score : " + std::to_string(score));
					}

					game = false;
				}
			}
			if (enemyLeft == 0)//all enemy died
			{
				if (level >= 5)
				{
					game = false;
				}

				if (game)
				{

					level++;
					enemyLeft = 52;
					kill = 40 + level * 2;

					if (playerLives < 3)
						playerLives++;

					en.setClassSpeed(level);
					countEnemyShoot = 0;
					countEnemyDeadBullets = 0;
					countShot = 0;
					countDeadBullets = 0;
					score += 500;
					playerLevel.setString("Level : " + std::to_string(level));
					scoreText.setString("Score : " + std::to_string(score));
					resetBullets();
				}

			}
	

			window.draw(scoreText);
			//High score display control
			if (score > highScoreInt)
			{
				highScore.setString("High Score : " + std::to_string(score));
				//highScore.setFillColor(sf::Color::Blue);
			}
			else
			{
				highScore.setString("High Score : " + std::to_string(highScoreInt));
				//highScore.setFillColor(sf::Color::Red);
			}
				
			//fly control
			if (flyCount > 250 && flyCount < 500)
			{
				fly.enemyX = fly.enemyX + fly.enemySpeed;
				fly.enemyY = 60;
				if (!playSound)
				{					
					//crossFly.crossShip();
					soundFly.play();/*****************************************fly ****************************************************/
					playSound = true;
				}

			}
			else
			{
				if(soundFly.Playing)
					soundFly.stop();//stop playing sound
				fly.enemyX = 0;
				fly.enemyY = -60;
				playSound = false;
			}
			if (flyCount == 500)
			{
				flyCount = 0;
				fly.enemyDeath = false;
				//std::cout << "750" << loop << "<< loop";
			}
			fly.setPosition(fly.enemyX, fly.enemyY);

			window.draw(fly);
			
			window.draw(highScore);
			window.draw(playerLevel);
			
			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
			loop++;
			flyCount++;
		}
		//check if user released the space bar
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			isSpacePressed = false;
		}

		//Menu control Exit game or Play again
		if (game == false)
		{
			window.draw(messageTXT);
			window.draw(arrow);
			if (score > highScoreInt)
			{
				newHighScore.setString("New Record : " + std::to_string(score));
				window.draw(newHighScore);
				ofstream myfile;
				myfile.open("score/score.txt");
				myfile << std::to_string(score);
				myfile.close();
			}
			if (enemyLeft > 0)
			{
				messageTXT.setString("You Lose!");
				window.draw(messageTXT);
				win = true;
			}
			else if(win == false)
			{
				messageTXT.setString("You Won!");
				window.draw(messageTXT);
				win = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				win = false;
				level = 1;
				kill = 40;
				if(score>highScoreInt)
					highScoreInt = score;

			//	gameWinner = false;
				en.setClassSpeed(0.5f);
	
				score = 0;
				
				highScore.setString("High Score : " + std::to_string(highScoreInt));
				playerLevel.setString("Level : " + std::to_string(level));
				scoreText.setString("Score : " + std::to_string(score));
	
				flyCount = 0; 
				resetBullets();
			

				//rebuild all meteors
				buildShelter(blockObj, meteor);
		
				game = true;
			}
				
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				//exit game
				window.close();
			}
			window.draw(play);
			window.draw(exit);

		}
		
		window.display();

	}//while finish
	return 0;
}