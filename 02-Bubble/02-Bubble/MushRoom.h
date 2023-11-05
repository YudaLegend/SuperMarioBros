#ifndef _MUSHROOM_INCLUDE
#define _MUSHROOM_INCLUDE

#include "Entity.h"
#include "TileMap.h"

class MushRoom : public Entity
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void render();

	void setPosition(const glm::vec2& pos);

	void updateOnCollision();

protected:
	TileMap* collisionMap;


};


#endif


