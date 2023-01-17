#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
class Bullet
{
public:
	sf::Sprite bulletSprite;
	sf::Vector2f flyPosition;
	Bullet(sf::Texture* texture, sf::Vector2f pos)
	{
		this->bulletSprite.setTexture(*texture);
		this->bulletSprite.setScale(0.08f, 0.08f);
		this->flyPosition = pos;
		this->bulletSprite.setPosition(this->flyPosition);
	}
	virtual ~Bullet(){}

	const sf::FloatRect getBounds() const;

	void moveBullet();

	void renderBullet(sf::RenderTarget* target);
};

