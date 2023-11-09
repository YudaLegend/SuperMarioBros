#include "Block.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

void Block::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int DayNight) {
	tileMapDispl = tileMapPos;
	physics = true;
	breaking = false;
	die = false;
	spritesheet.resize(2);
	sprite.resize(2);
	spritesheet[0].loadFromFile("images/Block.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet[0].loadFromFile("images/BleakBlock.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite[0]->Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5f, 1.f), &spritesheet[0], &shaderProgram);
	sprite[0]->setNumberAnimations(2);

	sprite[0]->setAnimationSpeed(0, 1);
	sprite[0]->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite[0]->setAnimationSpeed(1, 1);
	sprite[0]->addKeyframe(0, glm::vec2(0.5f, 0.f));

	sprite[0]->changeAnimation(DayNight);
	sprite[0]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	sprite[1]->Sprite::createSprite(glm::ivec2(64, 96), glm::vec2(1/11.f, 1.f), &spritesheet[1], &shaderProgram);
	sprite[1]->setNumberAnimations(1);

	sprite[1]->setAnimationSpeed(0, 11);
	sprite[1]->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite[1]->addKeyframe(0, glm::vec2(1 / 11.f, 0.f));
	sprite[1]->addKeyframe(0, glm::vec2(2 / 11.f, 0.f));
	sprite[1]->addKeyframe(0, glm::vec2(3 / 11.f, 0.f));
	sprite[1]->addKeyframe(0, glm::vec2(4 / 11.f, 0.f));
	sprite[1]->addKeyframe(0, glm::vec2(5 / 11.f, 0.f));
	sprite[1]->addKeyframe(0, glm::vec2(6 / 11.f, 0.f));
	sprite[1]->addKeyframe(0, glm::vec2(7 / 11.f, 0.f));
	sprite[1]->addKeyframe(0, glm::vec2(8 / 11.f, 0.f));
	sprite[1]->addKeyframe(0, glm::vec2(9 / 11.f, 0.f));
	sprite[1]->addKeyframe(0, glm::vec2(10 / 11.f, 0.f));

	sprite[1]->changeAnimation(0);
	sprite[1]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}
void Block::update(int deltaTime, float scroll) {
	if (breaking) {
		sprite[1]->update(deltaTime, scroll);
		breakTimer -= deltaTime;
		if (breakTimer <= 0) {
			die = true;
			physics = false;
			breaking = false;
		}
	}
	else {
		sprite[0]->update(deltaTime, scroll);
	}
}
void Block::render() {
	if (breaking) {
		sprite[1]->render();
	}
	else {
		sprite[0]->render();
	}
}

void Block::breakBlock() {
	breakTimer = 1000;
	breaking = true;
	physics = false;
}

void Block::setPosition(const glm::vec2& pos) {
	posPlayer = pos;
	sprite[0]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

bool Block::getPhysics() {
	return physics;
}

bool Block::getDie() {
	return die;
}
