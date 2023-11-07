#pragma once
#ifndef _SMALLMARIO_INCLUDE
#define _SMALLMARIO_INDLUDE

#include "Entity.h"
#include "Sprite.h"
#include "TileMap.h"

class SmallMario : public Entity
{
public:
	//SmallMario();
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

	

private:
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