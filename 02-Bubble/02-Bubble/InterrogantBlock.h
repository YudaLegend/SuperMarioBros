#ifndef _INTERROGANTBLOCK_INCLUDE
#define _INTERROGANTBLOCK_INCLUDE

#include "Entity.h"

class InterrogantBlock : public Entity
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void unlock();
	bool isUnlocked();

private:
};


#endif


