#ifndef _BLOCK_INCLUDE
#define _BLOCK_INCLUDE
#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"

class Block 
{
public:
	
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int DayNight);
	void update(int deltaTime, float scroll);
	void render();
	void breakBlock();
	void setSize(const glm::vec2& size);
	void setPosition(const glm::vec2& pos);
	bool getPhysics();
	bool getDie();

private:
	glm::ivec2 tileMapDispl, position, size;
	int breakTimer;
	bool breaking;
	bool physics;
	bool die;
	vector <Texture> spritesheet;
	vector <Sprite*> sprite;
};

#endif // _PLAYER_INCLUDE