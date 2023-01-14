#include "Enemy.h"

void Enemy::moveEnemy(int *direction) {
	position.x += speed * *direction;
	enemySprite.setPosition(position);
}

void Enemy::updateEnemy() {
	//moveEnemy();
}

