#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
class Bullet
{
public:
	sf::Sprite bulletSprite;
	
	Bullet(sf::Texture* texture)
	{
		this->bulletSprite.setTexture(*texture);

		this->bulletSprite.setScale(0.08f, 0.08f);
	}
	
	~Bullet(){}
};

