#include"player.h"

player::player()
{

}
player::~player()
{

}
player::player(float x, float y, sf::Texture &texture)
{
	playerX = 0;
	playerY = 530;
	playerSpeed = 2.0f;
	setSize(sf::Vector2f(70, 70));
	setPosition(playerX, playerY);
	setTexture(&texture);
}

