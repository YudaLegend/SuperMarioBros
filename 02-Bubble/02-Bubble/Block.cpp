#include "Block.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

void Block::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
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

	sprite[1]->Sprite::createSprite(glm::ivec2(64, 96), glm::vec2(1/11.f, 1.f), &spritesheet[1], &shaderProgram);
	sprite[1]->setNumberAnimations(1);

	sprite[1]->setAnimationSpeed(0, 1);
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


}
void Block::update(int deltaTime, float scroll) {
	for (int i = 0; i < sprite.size(); i++) {
		sprite[i]->update(deltaTime, scroll);
	}
}
void Block::render() {
	for (int i = 0; i < sprite.size(); i++) {
		sprite[i]->render();
	}
}

