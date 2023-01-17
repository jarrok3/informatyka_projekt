#include "spaceship.h"

void spaceship::initText()
{
	if (!this->playerText.loadFromFile("player.png")) {
		std::cout << "blad wczytu tekstury gracza\n";
		return;
	}
	this->playerText.loadFromFile("player.png");
}

void spaceship::initSprite()
{
	this->playerSprite.setTexture(this->playerText);
	this->playerSprite.setScale(0.2f, 0.2f);
	this->playerSprite.setPosition(400, 500);
}

void spaceship::initVar()
{
	this->speed = 5.f;
	this->hp = 3;
	this->hpMax = 3;
}
