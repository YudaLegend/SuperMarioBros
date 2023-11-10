#ifndef _COINS_INCLUDE
#define _COINS_INCLUDE

#include "Entity.h"

class Coins : public Entity
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void render();

	bool MarioCollide(glm::ivec2 playerpos);
	bool needDelete();

private:

	bool delet;

};


#endif


