#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 1
#define JUMP_HEIGHT 10
#define FALL_STEP 1


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_FALL_RIGHT, JUMP_FALL_LEFT, DELAY_CHANGE_DIRECTION_RIGHT, DELAY_CHANGE_DIRECTION_LEFT, DIE, FLAG
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	direction = false;
	firstJump = false;
	acces = 0;
	accomulation = 0;
	life = 3;
	height = 0;
	spritesheet.loadFromFile("images/SmallMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.111, 0.50), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.111f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.222f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.333f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.111f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.222f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.333f, 0.f));

	sprite->setAnimationSpeed(JUMP_FALL_RIGHT, 8);
	sprite->addKeyframe(JUMP_FALL_RIGHT, glm::vec2(0.555f, 0.f));

	sprite->setAnimationSpeed(JUMP_FALL_LEFT, 8);
	sprite->addKeyframe(JUMP_FALL_LEFT, glm::vec2(0.555f, 0.5f));

	sprite->setAnimationSpeed(DELAY_CHANGE_DIRECTION_RIGHT, 8);
	sprite->addKeyframe(DELAY_CHANGE_DIRECTION_RIGHT, glm::vec2(0.444f, 0.f));

	sprite->setAnimationSpeed(DELAY_CHANGE_DIRECTION_LEFT, 8);
	sprite->addKeyframe(DELAY_CHANGE_DIRECTION_LEFT, glm::vec2(0.444f, 0.5f));

	sprite->setAnimationSpeed(DIE, 8);
	sprite->addKeyframe(DIE, glm::vec2(0.666f, 0.f));

	sprite->setAnimationSpeed(FLAG, 8);
	sprite->addKeyframe(FLAG, glm::vec2(0.777f, 0.f));
	sprite->addKeyframe(FLAG, glm::vec2(0.888f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime, float scroll)
{
	sprite->update(deltaTime, scroll);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (acces > -100) acces -= 2;

		if (!direction) direction = true;
		
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		if (acces > 50) sprite->changeAnimation(DELAY_CHANGE_DIRECTION_LEFT);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (acces < 100) acces += 2;

		if (direction) direction = false;

		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		if (acces < -50) 
			sprite->changeAnimation(DELAY_CHANGE_DIRECTION_RIGHT);
	}
	else
	{
		if (acces > 0) acces -= 2;
		else if (acces < 0) acces += 2;
		
		if (acces == 0 && direction)
			sprite->changeAnimation(STAND_LEFT);
		else if (acces == 0 && !direction)
			sprite->changeAnimation(STAND_RIGHT);
	}
	accomulation += (acces);
	if (accomulation >= 100) {
		posPlayer.x += 1;
		accomulation = 0;
	}
	else if (accomulation <= -100) {
		posPlayer.x -= 1;
		accomulation = 0;
	}
		

	if (map->collisionMoveLeft(posPlayer, glm::ivec2(16, 16)))
	{
		posPlayer.x += 1;
		sprite->changeAnimation(STAND_LEFT);
	}
	else if (map->collisionMoveRight(posPlayer, glm::ivec2(16, 16)))
	{
		posPlayer.x -= 1;
		sprite->changeAnimation(STAND_RIGHT);
	}

	if (bJumping || (firstJump && !Game::instance().getSpecialKey(GLUT_KEY_UP)))
	{
		if (direction) sprite->changeAnimation(JUMP_FALL_LEFT);
		else  sprite->changeAnimation(JUMP_FALL_RIGHT);
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			firstJump = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - height * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90) {
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(16, 16), &posPlayer.y);
				firstJump = bJumping;
			}
				
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(16, 16), &posPlayer.y))
		{
			if (sprite->animation() == JUMP_FALL_LEFT) sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == JUMP_FALL_RIGHT)sprite->changeAnimation(STAND_RIGHT);
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				if (!firstJump) {
					height = 50;
					firstJump = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
				else {
					height += 2;
					if(height >= 100)
						bJumping = true;
				}
			}
		}
		else {
			if (direction) sprite->changeAnimation(JUMP_FALL_LEFT);
			else sprite->changeAnimation(JUMP_FALL_RIGHT);
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Player::getPosition() {
	return posPlayer;
}


