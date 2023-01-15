#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class spaceship
{
private:
	friend class Game;
	sf::Texture *playerText;
	sf::Sprite playerSprite;
	int speed;
public:
	sf::Vector2f position;
	spaceship(sf::Texture* texture, sf::Vector2f pos) 
	{
		this->playerText = texture;
		this->playerSprite.setTexture(*playerText);
		position = pos;
		this->playerSprite.setScale(0.1f, 0.1f);
		this->playerSprite.setPosition(pos);
		this->speed = 0.5f;
	}
};

