#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "InterrogantBlock.h"
#include "Game.h"

enum InterrogantBlockAnims
{
	LOCKED_1, UNLOCKED
};


void InterrogantBlock::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	spritesheet.loadFromFile("images/daybox.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1/4.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(LOCKED_1, 6);
	sprite->addKeyframe(LOCKED_1, glm::vec2(0/4.f, 1));
	sprite->addKeyframe(LOCKED_1, glm::vec2(1 / 4.f, 0.0f));
	sprite->addKeyframe(LOCKED_1, glm::vec2(2 / 4.f, 0.0f));
	sprite->addKeyframe(LOCKED_1, glm::vec2(0 / 4.f, 1));
	sprite->addKeyframe(LOCKED_1, glm::vec2(0 / 4.f, 1));



	sprite->setAnimationSpeed(UNLOCKED, 1);
	sprite->addKeyframe(UNLOCKED, glm::vec2(3/4.f, 0.f));


	sprite->changeAnimation(LOCKED_1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

void InterrogantBlock::update(int deltaTime, float scroll)
{
	sprite->update(deltaTime,scroll);

}

void InterrogantBlock::render() {
	sprite->render();
}

void InterrogantBlock::unlock(glm::ivec2 pos) {
	if (sprite->animation() == LOCKED_1 && (position.x/16) == pos.x && (position.y /16 == pos.y )) {
		
		sprite->changeAnimation(UNLOCKED);
	}
}

bool InterrogantBlock::isUnlocked() {
	return sprite->animation() == UNLOCKED;
}