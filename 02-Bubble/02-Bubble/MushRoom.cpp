#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MushRoom.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 1
#define JUMP_HEIGHT 96
#define FALL_STEP 4

enum MushRoomAnims
{
	MOVE_RIGHT, MOVE_LEFT, COLLECTED, HIT
};

void MushRoom::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	hit = false;
	delet = false;
	activated = false;


	spritesheet.loadFromFile("images/Mushroom1.png", TEXTURE_PIXEL_FORMAT_RGBA);

	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(MOVE_RIGHT, 2);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f,0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 2);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));


	sprite->changeAnimation(MOVE_RIGHT);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));

}


void MushRoom::update(int deltaTime, float scroll) {
	
	
		sprite->update(deltaTime, scroll);

		position.y += FALL_STEP;

		bool collisionDown = collisionMap->collisionMoveDown(position, glm::ivec2(16, 16), &position.y);
		bool collisionLeft = (sprite->animation() == MOVE_LEFT) && collisionMap->collisionMoveLeft(position + glm::ivec2(-1, 0), size);
		bool collisionRight = (sprite->animation() == MOVE_RIGHT) && collisionMap->collisionMoveRight(position + glm::ivec2(1, 0), size);

	
		if (hit) {
			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180)
			{
				hit = false;
				//position.y = startY;
			}
			else if (jumpAngle > 90) {
				hit = !collisionDown;
			}
			else
			{
				position.y = int(startY - 16 * sin(3.14159f * jumpAngle / 180.f));
			}
		}
		else {
			if (!(collisionDown) || collisionLeft || collisionRight) {
				if (sprite->animation() == MOVE_RIGHT) {
					sprite->changeAnimation(MOVE_LEFT);
				}
				else {
					sprite->changeAnimation(MOVE_RIGHT);
				}
			}

			if (collisionDown && (sprite->animation() != COLLECTED)) {
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
		}

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
	
		
}

void MushRoom::render() {
	sprite->render();
}

void MushRoom::setPosition(const glm::vec2& pos)
{
	position = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

void MushRoom::setCollisionMap(TileMap* collisionMap)
{
	this->collisionMap = collisionMap;
}


void MushRoom::setHit() {
	hit = true;
	startY = position.y;
}

bool MushRoom::isActivated() {
	return activated == true;
}

void MushRoom::setActivate(bool t) {
	activated = t;
}

bool MushRoom::isTouch() {
	return delet == true;
}

bool MushRoom::touchMario(glm::ivec2 playerpos) {
	if (activated) {
		if (position.x <= playerpos.x + 16 && playerpos.x <= position.x + 16) {
			if (position.y <= playerpos.y  && playerpos.y <= position.y + 16 && !hit) {

				delet = true;
				return true;
			}
		}
	}

	return false;
}


void MushRoom::updateOnCollision() {

	if (sprite->animation() == MOVE_RIGHT) {
		sprite->changeAnimation(MOVE_LEFT);
	}
	else
		sprite->changeAnimation(MOVE_RIGHT);
}
