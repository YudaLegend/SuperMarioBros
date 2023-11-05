#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Entity.h"
#include "TileMap.h"


class Enemy : public Entity
{
public:
	virtual void updateOnCollision() = 0;
	virtual bool isDead() = 0;

	void setCollisionMap(TileMap* collisionMap);
	void setOrientation(char orientation);
	void changeOrientation();
	bool MarioUp(glm::ivec2 pos, int* posY);
	bool enemyKillMario(glm::ivec2 pos);


protected:
	TileMap* collisionMap;
};

#endif

