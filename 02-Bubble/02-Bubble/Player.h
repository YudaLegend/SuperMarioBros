#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

//#include "Entity.h"
//#include "Sprite.h"
//#include "TileMap.h"
#include "SmallMario.h"
#include "BigMario.h"
// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player : public Entity
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	bool collisionInt();

	glm::ivec2 posInt();

	glm::ivec2 getPosition();

	void setJump();
	void setStartMode();

	void setSmall();
private:
	SmallMario* sm;
	BigMario* bm;
	bool mode; //false = small, true = true
};


#endif // _PLAYER_INCLUDE

