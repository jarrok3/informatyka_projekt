#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class spaceship
{
private:
	sf::Texture playerText;
	sf::Sprite playerSprite;
	
	int speed;
	int hp;
	int hpMax;

	void initText();
	void initSprite();
	void initVar();
public:
	sf::Vector2f position;
	spaceship() 
	{
		this->initVar();
		this->initText();
		this->initSprite();
	}
	virtual ~spaceship();

};

