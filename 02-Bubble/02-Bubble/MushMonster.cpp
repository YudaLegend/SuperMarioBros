#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "MushMonster.h"

#define FALL_STEP 4

enum MushAnims
{
	MOVE_RIGHT, MOVE_LEFT, DEAD
};


void MushMonster::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/MushMonster.png", TEXTURE_PIXEL_FORMAT_RGBA);
	
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1/3.f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(MOVE_RIGHT, 2);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1/3.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 2);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(1/3.f , 0.f));
	

	sprite->setAnimationSpeed(DEAD, 1);
	sprite->addKeyframe(DEAD, glm::vec2(2/3.f, 0.f));

	sprite->changeAnimation(MOVE_RIGHT);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

void MushMonster::update(int deltaTime, float scroll)
{
	sprite->update(deltaTime, scroll);
	position.y += FALL_STEP;
	if (collisionMap->collisionMoveDown(position, glm::ivec2(16, 16), &position.y)){

		int shift = 0;
		if (sprite->animation() == MOVE_RIGHT)
			shift = size.x;
		if (sprite->animation() == MOVE_LEFT)
			shift = -size.x;
		if (sprite->animation() == MOVE_RIGHT) {
			position.x += 1;
		}
		else {
			position.x -= 1;
		}
	}

	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

void MushMonster::render() {
	sprite->render();
}

void MushMonster::updateOnCollision() {

	if (sprite->animation() == MOVE_RIGHT) {
		sprite->changeAnimation(MOVE_LEFT);
	}
	else
		sprite->changeAnimation(MOVE_RIGHT);
}
