#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Sprite.h"

class Entity
{
protected:
	Sprite* sprite;
	Sprite* spawnSprite;
	//Sprite* hitboxSprite;
	bool spawning = false;
	//bool showHitbox = false;
	glm::ivec2 tileMapDispl, position, size;
	Texture spritesheet;
	Texture spawnSpritesheet;
	//Texture hitboxSpritesheet;
	glm::vec2 spawnPosition;
	float spawningTime = 500;
	float spawningTimeElapsed = 0;
	//glm::vec2 hitboxOffset = glm::vec2(0, 0);
	

public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime, float scroll) = 0;
	//virtual const glm::vec2& getHitboxOffset();
	void initSpawn(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	//void initHitbox(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, string entityType);
	//void changeHitboxVisibility();
	virtual void render();
	void setPosition(const glm::vec2& pos);
	void setSpawnPosition(glm::vec2& spawnPosition);
	const glm::vec2 getPosition();
	void setSize(const glm::vec2& size);
	const glm::vec2 getSize();
	bool isSpawning();

};

#endif

