#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "InterrogantBlock.h"
#include "Game.h"

enum BlockAnims
{
	NORMAL, BROKEN
};


void Block::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Block.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1 / 2.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);


	sprite->setAnimationSpeed(NORMAL, 1);
	sprite->addKeyframe(NORMAL, glm::vec2(0.f, 0));

	sprite->setAnimationSpeed(BROKEN, 1);
	sprite->addKeyframe(NORMAL, glm::vec2(1/2.f, 0));


	sprite->changeAnimation(NORMAL);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));

}

void Block::update(int deltaTime, float scroll)
{
	sprite->update(deltaTime, scroll);
}

void Block::render() {
	sprite->render();
}

void Block::unlock(glm::ivec2 pos) {
	if (sprite->animation() == NORMAL && (position.x / 16) == pos.x && (position.y / 16 == pos.y)) {

		sprite->changeAnimation(BROKEN);
	}

}

bool Block::isUnlocked() {
	return sprite->animation() == BROKEN;
}

bool Block::MarioDown(glm::ivec2 playerpos) {

	if (playerpos.x <= position.x + 16 && playerpos.x >= position.x - 16) {
		if (playerpos.y >= position.y && playerpos.y <= position.y + 20) {

			//Aqui funcion jump para hacer que salte
			sprite->changeAnimation(BROKEN);
			return true;
		}
	}
	return false;

}