#ifndef _TURTLE_INCLUDE
#define _TURTLE_INCLUDE

#include "Enemy.h"

class Turtle : public Enemy
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void updateOnCollision();
	void render();

	bool isDead();

	int deadCounter = 0;

};

#endif