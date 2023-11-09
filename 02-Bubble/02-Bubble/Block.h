#ifndef _BLOCK_INCLUDE
#define _BLOCK_INCLUDE
#include "Sprite.h"
#include "TileMap.h"
class Block
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void render();
private:
	vector <Texture> spritesheet;
	vector <Sprite*> sprite;
};

#endif // _PLAYER_INCLUDE