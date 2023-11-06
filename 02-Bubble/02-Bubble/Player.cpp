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
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_FALL_RIGHT, JUMP_FALL_LEFT, DELAY_CHANGE_DIRECTION_RIGHT, DELAY_CHANGE_DIRECTION_LEFT, DIE, FLAG, STAND_LEFT_STAR, STAND_RIGHT_STAR, MOVE_LEFT_STAR, MOVE_RIGHT_STAR, JUMP_FALL_RIGHT_STAR, JUMP_FALL_LEFT_STAR, DELAY_CHANGE_DIRECTION_RIGHT_STAR, DELAY_CHANGE_DIRECTION_LEFT_STAR, FLAG_STAR
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	direction = false;
	firstJump = false;
	starmode = false;
	prestar = false;
	acces = 0;
	accomulation = 0;
	life = 3;
	height = 0;
	speed = 1;
	spritesheet.loadFromFile("images/SmallMarioStar.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.111, 0.125), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(20);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.875f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.75f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.111f, 0.875f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.222f, 0.875f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.333f, 0.875f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.111f, 0.75f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.222f, 0.75f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.333f, 0.75f));

	sprite->setAnimationSpeed(JUMP_FALL_RIGHT, 8);
	sprite->addKeyframe(JUMP_FALL_RIGHT, glm::vec2(0.555f, 0.75f));

	sprite->setAnimationSpeed(JUMP_FALL_LEFT, 8);
	sprite->addKeyframe(JUMP_FALL_LEFT, glm::vec2(0.555f, 0.875f));

	sprite->setAnimationSpeed(DELAY_CHANGE_DIRECTION_RIGHT, 8);
	sprite->addKeyframe(DELAY_CHANGE_DIRECTION_RIGHT, glm::vec2(0.444f, 0.75f));

	sprite->setAnimationSpeed(DELAY_CHANGE_DIRECTION_LEFT, 8);
	sprite->addKeyframe(DELAY_CHANGE_DIRECTION_LEFT, glm::vec2(0.444f, 0.875f));

	sprite->setAnimationSpeed(DIE, 8);
	sprite->addKeyframe(DIE, glm::vec2(0.666f, 0.75f));

	sprite->setAnimationSpeed(FLAG, 8);
	sprite->addKeyframe(FLAG, glm::vec2(0.777f, 0.75f));
	sprite->addKeyframe(FLAG, glm::vec2(0.888f, 0.75f));

	sprite->setAnimationSpeed(STAND_LEFT_STAR, 2);
	sprite->addKeyframe(STAND_LEFT_STAR, glm::vec2(0.f, 0.125f));
	sprite->addKeyframe(STAND_LEFT_STAR, glm::vec2(0.f, 0.375f));
	sprite->addKeyframe(STAND_LEFT_STAR, glm::vec2(0.f, 0.625f));

	sprite->setAnimationSpeed(STAND_RIGHT_STAR, 2);
	sprite->addKeyframe(STAND_RIGHT_STAR, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND_RIGHT_STAR, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(STAND_RIGHT_STAR, glm::vec2(0.f, 0.5));

	sprite->setAnimationSpeed(MOVE_LEFT_STAR, 8);
	sprite->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.111f, 0.125f));
	sprite->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.111f, 0.375f));
	sprite->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.111f, 0.625f));
	sprite->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.222f, 0.125f));
	sprite->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.222f, 0.375f));
	sprite->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.222f, 0.625f));
	sprite->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.333f, 0.125f));
	sprite->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.333f, 0.375f));
	sprite->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.333f, 0.625f));

	sprite->setAnimationSpeed(MOVE_RIGHT_STAR, 8);
	sprite->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.111f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.111f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.111f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.222f, 0.0f));
	sprite->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.222f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.222f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.333f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.333f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.333f, 0.5f));

	sprite->setAnimationSpeed(JUMP_FALL_RIGHT_STAR, 8);
	sprite->addKeyframe(JUMP_FALL_RIGHT_STAR, glm::vec2(0.555f, 0.f));
	sprite->addKeyframe(JUMP_FALL_RIGHT_STAR, glm::vec2(0.555f, 0.25f));
	sprite->addKeyframe(JUMP_FALL_RIGHT_STAR, glm::vec2(0.555f, 0.5f));

	sprite->setAnimationSpeed(JUMP_FALL_LEFT_STAR, 8);
	sprite->addKeyframe(JUMP_FALL_LEFT_STAR, glm::vec2(0.555f, 0.125f));
	sprite->addKeyframe(JUMP_FALL_LEFT_STAR, glm::vec2(0.555f, 0.375f));
	sprite->addKeyframe(JUMP_FALL_LEFT_STAR, glm::vec2(0.555f, 0.625f));

	sprite->setAnimationSpeed(DELAY_CHANGE_DIRECTION_RIGHT_STAR, 8);
	sprite->addKeyframe(DELAY_CHANGE_DIRECTION_RIGHT_STAR, glm::vec2(0.444f, 0.f));
	sprite->addKeyframe(DELAY_CHANGE_DIRECTION_RIGHT_STAR, glm::vec2(0.444f, 0.25f));
	sprite->addKeyframe(DELAY_CHANGE_DIRECTION_RIGHT_STAR, glm::vec2(0.444f, 0.5f));

	sprite->setAnimationSpeed(DELAY_CHANGE_DIRECTION_LEFT_STAR, 8);
	sprite->addKeyframe(DELAY_CHANGE_DIRECTION_LEFT_STAR, glm::vec2(0.444f, 0.125f));
	sprite->addKeyframe(DELAY_CHANGE_DIRECTION_LEFT_STAR, glm::vec2(0.444f, 0.375f));
	sprite->addKeyframe(DELAY_CHANGE_DIRECTION_LEFT_STAR, glm::vec2(0.444f, 0.625f));

	sprite->setAnimationSpeed(FLAG_STAR, 8);
	sprite->addKeyframe(FLAG_STAR, glm::vec2(0.777f, 0.f));
	sprite->addKeyframe(FLAG_STAR, glm::vec2(0.777f, 0.25f));
	sprite->addKeyframe(FLAG_STAR, glm::vec2(0.777f, 0.5f));
	sprite->addKeyframe(FLAG_STAR, glm::vec2(0.888f, 0.f));
	sprite->addKeyframe(FLAG_STAR, glm::vec2(0.888f, 0.25f));
	sprite->addKeyframe(FLAG_STAR, glm::vec2(0.888f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime, float scroll)
{
	sprite->update(deltaTime, scroll);

	if (Game::instance().getSpecialKey(GLUT_KEY_F1) && prestar && !starmode) {
		starmode = true;
		prestar = false;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_F1) && prestar && starmode) {
		starmode = false;
		prestar = false;
	}
	else if (!Game::instance().getSpecialKey(GLUT_KEY_F1) && !prestar) {
		prestar = true;
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (acces > -100) acces -= 2;

		if (!direction) direction = true;
		
		if (starmode && !bJumping) {
			if (sprite->animation() != MOVE_LEFT_STAR)
				sprite->changeAnimation(MOVE_LEFT_STAR);
		}
		else if (sprite->animation() != MOVE_LEFT && !starmode)
			sprite->changeAnimation(MOVE_LEFT);

		if (acces > 50 && !starmode && sprite->animation() != DELAY_CHANGE_DIRECTION_LEFT && !bJumping) sprite->changeAnimation(DELAY_CHANGE_DIRECTION_LEFT);
		else if (acces > 50 && starmode && sprite->animation() != DELAY_CHANGE_DIRECTION_LEFT_STAR && !bJumping) sprite->changeAnimation(DELAY_CHANGE_DIRECTION_LEFT_STAR);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (acces < 100) acces += 2;

		if (direction) direction = false;

		if (starmode && !bJumping) {
			if (sprite->animation() != MOVE_RIGHT_STAR)
				sprite->changeAnimation(MOVE_RIGHT_STAR);
		}
		else if (sprite->animation() != MOVE_RIGHT && !starmode)
			sprite->changeAnimation(MOVE_RIGHT);

		if (acces < -50 && !starmode && sprite->animation() != DELAY_CHANGE_DIRECTION_RIGHT && !bJumping) sprite->changeAnimation(DELAY_CHANGE_DIRECTION_RIGHT);
		if (acces < -50 && starmode && sprite->animation() != DELAY_CHANGE_DIRECTION_RIGHT_STAR && !bJumping) sprite->changeAnimation(DELAY_CHANGE_DIRECTION_RIGHT_STAR);
	}
	else
	{
		if (acces > 0) acces -= 2;
		else if (acces < 0) acces += 2;
		
		if (acces == 0 && direction && !bJumping) {
			if (starmode && sprite->animation() != STAND_LEFT_STAR) sprite->changeAnimation(STAND_LEFT_STAR);
			else if (!starmode && sprite->animation() != STAND_LEFT)
				sprite->changeAnimation(STAND_LEFT);
		}
		else if (acces == 0 && !direction && !bJumping) {
			if (starmode && sprite->animation() != STAND_RIGHT_STAR) sprite->changeAnimation(STAND_RIGHT_STAR);
			else if (!starmode && sprite->animation() != STAND_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}
	}
	if (Game::instance().getSpecialKey(112)) {
		speed = 2;
	}
	else {
		speed = 1;
	}
	accomulation += (acces);
	if (accomulation >= 100) {
		posPlayer.x += speed;
		accomulation = 0;
	}
	else if (accomulation <= -100) {
		posPlayer.x -= speed;
		accomulation = 0;
	}
		

	if (map->collisionMoveLeft(posPlayer, glm::ivec2(16, 16)))
	{
		posPlayer.x += speed;
		if (starmode && sprite->animation() != STAND_LEFT_STAR) sprite->changeAnimation(STAND_LEFT_STAR);
		else if (sprite->animation() != STAND_LEFT) sprite->changeAnimation(STAND_LEFT);
	}
	else if (map->collisionMoveRight(posPlayer, glm::ivec2(16, 16)))
	{
		posPlayer.x -= speed;
		if (starmode && sprite->animation() != STAND_RIGHT_STAR) sprite->changeAnimation(STAND_RIGHT_STAR);
		else if (sprite->animation() != STAND_RIGHT)sprite->changeAnimation(STAND_RIGHT);
	}

	if (bJumping)
	{
		if (direction && starmode && sprite->animation() != JUMP_FALL_LEFT_STAR)
			sprite->changeAnimation(JUMP_FALL_LEFT_STAR);
		else if (direction && !starmode && sprite->animation() != JUMP_FALL_LEFT)
			sprite->changeAnimation(JUMP_FALL_LEFT);
		else if (!direction && starmode && sprite->animation() != JUMP_FALL_RIGHT_STAR)
			sprite->changeAnimation(JUMP_FALL_RIGHT_STAR);
		else if (!direction && !starmode && sprite->animation() != JUMP_FALL_RIGHT)
			sprite->changeAnimation(JUMP_FALL_RIGHT);
		jumpAngle += JUMP_ANGLE_STEP;
		if (map->collisionMoveUp(posPlayer, glm::ivec2(16, 16), &posPlayer.y) && jumpAngle < 90) {
			jumpAngle = 180 - jumpAngle;
		}
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - height * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90) {
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(16, 16), &posPlayer.y);
			}

		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(16, 16), &posPlayer.y))
		{
			if (!firstJump && height != 0) height = 0;
			if (sprite->animation() == JUMP_FALL_LEFT) sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == JUMP_FALL_RIGHT)sprite->changeAnimation(STAND_RIGHT);
			else if (sprite->animation() == JUMP_FALL_LEFT_STAR) sprite->changeAnimation(STAND_LEFT_STAR);
			else if (sprite->animation() == JUMP_FALL_RIGHT_STAR)sprite->changeAnimation(STAND_RIGHT_STAR);

			if (Game::instance().getSpecialKey(GLUT_KEY_UP) || Game::instance().getKey(32))
			{
				if (!firstJump) {
					height = 50;
					firstJump = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
				else {
					height += 2;
					if (height >= 100) {
						bJumping = true;
						firstJump = false;
					}
				}
			}
			else if (firstJump) {
				bJumping = true;
				firstJump = false;
			}
		}
		else
		{
			height = 0;
			bJumping = false;
			firstJump = false;
			if (direction && starmode && sprite->animation() != JUMP_FALL_LEFT_STAR) sprite->changeAnimation(JUMP_FALL_LEFT_STAR);
			else if (direction && !starmode && sprite->animation() != JUMP_FALL_LEFT) sprite->changeAnimation(JUMP_FALL_LEFT);
			else if (!direction && starmode && sprite->animation() != JUMP_FALL_RIGHT_STAR) sprite->changeAnimation(JUMP_FALL_RIGHT_STAR);
			else if (!direction && !starmode && sprite->animation() != JUMP_FALL_RIGHT) sprite->changeAnimation(JUMP_FALL_RIGHT);
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}


void Player::setStartMode() {
	starmode = true;
}

void Player::setJump() {
	bJumping = true;
	jumpAngle = 0;
	height = 25;
	startY = posPlayer.y;

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

bool Player::collisionInt() {
	return map->collisionInt(posPlayer, glm::ivec2(16, 16), &posPlayer.y);
}

glm::ivec2 Player::posInt() {
	return map->posInt(posPlayer, glm::ivec2(16, 16), &posPlayer.y);
}


glm::ivec2 Player::getPosition() {
	return posPlayer;
}


