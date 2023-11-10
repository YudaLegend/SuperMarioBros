#ifndef _STAR_INCLUDE
#define _STAR_INCLUDE

#include "Entity.h"
#include "TileMap.h"

class Star : public Entity
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void render();



	void setPosition(const glm::vec2& pos);
	void setCollisionMap(TileMap* collisionMap);

	void updateOnCollision();
	void setHit();
	void setActivate(bool t);
	bool isActivated();
	bool touchMario(glm::ivec2 playerpos);
	bool isTouch();


	bool activated = false;
	bool hit = false;
	bool delet = false;

	int jumpAngle, startY;

protected:
	TileMap* collisionMap;


};


#endif


