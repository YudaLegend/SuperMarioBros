#ifndef _STAR_INCLUDE
#define _STAR_INCLUDE
#include "Sprite.h"
#include "TileMap.h"
class Star
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
