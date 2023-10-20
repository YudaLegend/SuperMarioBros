#include "Enemy.h"

enum Anims {
	MOVE_RIGHT, MOVE_LEFT
};

void Enemy::setCollisionMap(TileMap* collisionMap)
{
	this->collisionMap = collisionMap;
}

void Enemy::setOrientation(char orientation) {
	if (orientation == 'R') {
		if (sprite->animation() != MOVE_RIGHT) {
			sprite->changeAnimation(MOVE_RIGHT);
		}
	}
	else if (orientation == 'L') {
		if (sprite->animation() != MOVE_LEFT) {
			sprite->changeAnimation(MOVE_LEFT);
		}
	}
}

void Enemy::changeOrientation() {
	if (sprite->animation() == MOVE_RIGHT) {
		sprite->changeAnimation(MOVE_LEFT);
	}
	else
		sprite->changeAnimation(MOVE_RIGHT);
}