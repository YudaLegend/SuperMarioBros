#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Entity.h"
#include "TileMap.h"


class Enemy : public Entity
{
public:
	virtual void updateOnCollision() = 0;
	void setCollisionMap(TileMap* collisionMap);
	void setOrientation(char orientation);
	void changeOrientation();
protected:
	TileMap* collisionMap;
};

#endif

