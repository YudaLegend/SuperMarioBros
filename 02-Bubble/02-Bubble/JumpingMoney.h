#ifndef _JUMPINGMONEY_INCLUDE
#define _JUMPINGMONEY_INCLUDE

#include "Entity.h"

class JumpingMoney : public Entity
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void render();

	bool MarioDown(glm::ivec2 playerpos);

private:
	bool bJumping;
	bool hit;
	int jumpAngle, startY;
};


#endif


