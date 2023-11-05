#ifndef _GAMEUI_INCLUDE
#define _GAMEUI_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class GameUI
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	void setFix();
	void setDinamic();
	void setPosPlayer(glm::ivec2 pos);

	void updateWorld(int w);
	void updateCoins();
	void updateScore(int s);
	void updateTime();
	glm::ivec2 getPosition();

private:
	glm::ivec2 tileMapDispl, posPlayer;
	vector <Texture> spritesheets;
	vector <Sprite*> row;
	vector <Sprite*> row2;
	//Sprite* coins;
	TileMap* map;

	int world, coins, score, time;
};


#endif 
