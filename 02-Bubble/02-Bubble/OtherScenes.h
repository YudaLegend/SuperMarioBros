#pragma once
#ifndef _OTHERSCENES_INCLUDE
#define _OTHERSCENES_INCLUDE
#include "Sprite.h"
#include "TileMap.h"
class OtherScenes
{
public:
	OtherScenes();
	~OtherScenes();
	void init();
	void update(int deltaTime);
	void reshape(int w, int h);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	void setScore(int s);
	void setTime(int t);
	void setCoins(int c);
	void setWorld(int w);

	void setPausaMode(int p);

private:
	void initShaders();
	ShaderProgram texProgram;
	ShaderProgram* shaderProgram;
	float currentTime;
	glm::mat4 projection;
	float scroll = 0;
	glm::ivec2 tileMapDispl, posPlayer;
	vector <Texture> spritesheets;
	vector <Sprite*> scenes;
	//Sprite* coins;
	TileMap* map;
	int pausamode; //0-5 init scenes ,6 time up, 7 game over
	int score;
	int coins;
	int time;
	int world;
};

#endif
