#ifndef _BIGMARIO_INCLUDE
#define _BIGMARIO_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class BigMario
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	void normalAction(bool starmode);
	void middleAction();

	glm::ivec2 getPosition();

	bool collisionInt();

	glm::ivec2 posInt();

	void setJump();
	void setStartMode();

private:
	bool middle;
	bool bJumping;
	bool direction;//false right true left
	bool starmode;
	bool prestar;
	int acces;
	int accomulation;
	int height;
	bool firstJump;
	int speed;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif 

