#include "Enemy.h"

void Enemy::moveEnemy(sf::Vector2f direction, float speed) {
	this->enemySprite.move(direction * speed);
}

void Enemy::updateEnemy() {

}

void Enemy::renderEnemy(sf::RenderWindow& window)
{
	window.draw(this->enemySprite);
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->enemySprite.getGlobalBounds();
}

