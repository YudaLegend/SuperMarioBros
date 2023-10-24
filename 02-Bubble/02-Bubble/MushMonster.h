#ifndef _MUSHMONSTER_INCLUDE
#define _MUSHMONSTER_INCLUDE

#include "Enemy.h"

class MushMonster : public Enemy
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void updateOnCollision();
	void render();


};

#endif