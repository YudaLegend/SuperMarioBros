#ifndef _BLOCK_INCLUDE
#define _BLOCK_INCLUDE

#include "Entity.h"

class Block : public Entity
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void render();
	void unlock(glm::ivec2 pos);
	bool isUnlocked();
	bool MarioDown(glm::ivec2 playerpos);

	Texture desSpritesheet;

private:

};


#endif


