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
	sf::Texture* texture;

	Enemy(sf::Texture *texture, sf::Vector2f pos)
	{
		this->texture = texture;
		this->enemySprite.setTexture(*texture);
		position = pos;
		this->enemySprite.setScale(0.1f, 0.1f);
		this->enemySprite.setPosition(pos);
	};
	virtual ~Enemy(){}

	void moveEnemy(sf::Vector2f direction, float speed);
	void updateEnemy();
	void renderEnemy(sf::RenderWindow& window);

	const sf::FloatRect getBounds() const;
};
