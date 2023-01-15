#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
private:
	
public:
	float speed;
	sf::Vector2f position;
	sf::Sprite enemySprite;
	sf::Texture *texture;
	Enemy(sf::Texture *texture, sf::Vector2f pos)
	{
		this->texture = texture;
		this->enemySprite.setTexture(*texture);
		position = pos;
		this->enemySprite.setScale(0.1f, 0.1f);
		this->enemySprite.setPosition(pos);
		speed = 0.5f;
	};
	~Enemy(){}
	void moveEnemy(int *direction);
	void updateEnemy();
};
