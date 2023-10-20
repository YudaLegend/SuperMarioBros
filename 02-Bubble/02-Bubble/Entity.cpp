#include "Entity.h"
#include <iostream>

using namespace std;

void Entity::render()
{
	if (spawning) {
		spawnSprite->render();
	}
	else {
		sprite->render();
	}
}

void Entity::setPosition(const glm::vec2& pos)
{
	position = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

void Entity::setSpawnPosition(glm::vec2& spawnPosition) {
	this->spawnPosition = spawnPosition;
	spawnSprite->setPosition(glm::vec2(float(tileMapDispl.x + spawnPosition.x), float(tileMapDispl.y + spawnPosition.y)));
}

const glm::vec2 Entity::getPosition() {
	return this->position;
}

void Entity::setSize(const glm::vec2& size) {
	this->size = size;
}

const glm::vec2 Entity::getSize() {
	return this->size;
}

void Entity::initSpawn(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	spawnSpritesheet.loadFromFile("images/spawn.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spawnSpritesheet.setMinFilter(GL_NEAREST);
	spawnSpritesheet.setMagFilter(GL_NEAREST);
	spawnSprite = Sprite::createSprite(glm::ivec2(48, 48), glm::vec2(1.0, 0.5), &spawnSpritesheet, &shaderProgram);
	spawnSprite->setNumberAnimations(1);

	spawnSprite->setAnimationSpeed(0, 4);
	spawnSprite->addKeyframe(0, glm::vec2(0.f, 0.0f));
	spawnSprite->addKeyframe(0, glm::vec2(0.f, 0.5f));

	spawnSprite->changeAnimation(0);
}



bool Entity::isSpawning() {
	return spawning;
}