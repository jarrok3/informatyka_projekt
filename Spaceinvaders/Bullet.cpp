#include "Bullet.h"

void Bullet::moveBullet() {
	this->flyPosition.y -= 10;
	this->bulletSprite.setPosition(this->flyPosition);
}

const sf::FloatRect Bullet::getBounds() const {
	return this->bulletSprite.getGlobalBounds();
}

void Bullet::renderBullet(sf::RenderTarget* target)
{
	target->draw(this->bulletSprite);
}