#include "Enemy.h"

enum Anims {
	MOVE_RIGHT, MOVE_LEFT , DEAD
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

bool Enemy::MarioUp(glm::ivec2 playerpos, int* posY) {
	

	if (position.x  <= playerpos.x && playerpos.x <= position.x + 16 ) {
		if ( position.y - 20 <= playerpos.y &&  playerpos.y  <= position.y ) {
			sprite->changeAnimation(DEAD);
			return true;
		}
	} 

	return false;
}

void Enemy::changeOrientation() {
	if (sprite->animation() == MOVE_RIGHT) {
		sprite->changeAnimation(MOVE_LEFT);
	}
	else
		sprite->changeAnimation(MOVE_RIGHT);
}