#ifndef _INTERROGANTBLOCK_INCLUDE
#define _INTERROGANTBLOCK_INCLUDE

#include "Entity.h"

class InterrogantBlock : public Entity
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void render();
	void unlock(glm::ivec2 pos);
	bool isUnlocked();

private:
};


#endif


