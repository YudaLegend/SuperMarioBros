#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 2
#define JUMP_HEIGHT 10
#define FALL_STEP 2

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_FALL_RIGHT, JUMP_FALL_LEFT, DELAY_CHANGE_DIRECTION_RIGHT, DELAY_CHANGE_DIRECTION_LEFT, DIE, FLAG, STAND_LEFT_STAR, STAND_RIGHT_STAR, MOVE_LEFT_STAR, MOVE_RIGHT_STAR, JUMP_FALL_RIGHT_STAR, JUMP_FALL_LEFT_STAR, DELAY_CHANGE_DIRECTION_RIGHT_STAR, DELAY_CHANGE_DIRECTION_LEFT_STAR, FLAG_STAR
};
enum SmallAnims
{
	B_STAND_LEFT, B_STAND_RIGHT, B_MOVE_LEFT, B_MOVE_RIGHT, B_JUMP_FALL_RIGHT, B_JUMP_FALL_LEFT, B_DELAY_CHANGE_DIRECTION_RIGHT, B_DELAY_CHANGE_DIRECTION_LEFT, B_DIE, B_FLAG, B_STAND_LEFT_STAR, B_STAND_RIGHT_STAR, B_MOVE_LEFT_STAR, B_MOVE_RIGHT_STAR, B_JUMP_FALL_RIGHT_STAR, B_JUMP_FALL_LEFT_STAR, B_DELAY_CHANGE_DIRECTION_RIGHT_STAR, B_DELAY_CHANGE_DIRECTION_LEFT_STAR, B_FLAG_STAR, MID_RIGHT, MID_LEFT, MID_RIGHT_STAR, MID_LEFT_STAR
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.resize(4);
	sprite.resize(4);
	bJumping = false;
	direction = false;
	firstJump = false;
	starmode = false;
	prestar = false;
	mariomode = false;
	convertionTime = 0;
	acces = 0;
	accomulation = 0;
	height = 0;
	speed = 1;
	spritesheet[0].loadFromFile("images/SmallMarioStar.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite[0] = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.111, 0.125), &spritesheet[0], &shaderProgram);
	sprite[0]->setNumberAnimations(20);

	sprite[0]->setAnimationSpeed(STAND_LEFT, 8);
	sprite[0]->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.875f));

	sprite[0]->setAnimationSpeed(STAND_RIGHT, 8);
	sprite[0]->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.75f));

	sprite[0]->setAnimationSpeed(MOVE_LEFT, 8);
	sprite[0]->addKeyframe(MOVE_LEFT, glm::vec2(0.111f, 0.875f));
	sprite[0]->addKeyframe(MOVE_LEFT, glm::vec2(0.222f, 0.875f));
	sprite[0]->addKeyframe(MOVE_LEFT, glm::vec2(0.333f, 0.875f));

	sprite[0]->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite[0]->addKeyframe(MOVE_RIGHT, glm::vec2(0.111f, 0.75f));
	sprite[0]->addKeyframe(MOVE_RIGHT, glm::vec2(0.222f, 0.75f));
	sprite[0]->addKeyframe(MOVE_RIGHT, glm::vec2(0.333f, 0.75f));

	sprite[0]->setAnimationSpeed(JUMP_FALL_RIGHT, 8);
	sprite[0]->addKeyframe(JUMP_FALL_RIGHT, glm::vec2(0.555f, 0.75f));

	sprite[0]->setAnimationSpeed(JUMP_FALL_LEFT, 8);
	sprite[0]->addKeyframe(JUMP_FALL_LEFT, glm::vec2(0.555f, 0.875f));

	sprite[0]->setAnimationSpeed(DELAY_CHANGE_DIRECTION_RIGHT, 8);
	sprite[0]->addKeyframe(DELAY_CHANGE_DIRECTION_RIGHT, glm::vec2(0.444f, 0.75f));

	sprite[0]->setAnimationSpeed(DELAY_CHANGE_DIRECTION_LEFT, 8);
	sprite[0]->addKeyframe(DELAY_CHANGE_DIRECTION_LEFT, glm::vec2(0.444f, 0.875f));

	sprite[0]->setAnimationSpeed(DIE, 8);
	sprite[0]->addKeyframe(DIE, glm::vec2(0.666f, 0.75f));

	sprite[0]->setAnimationSpeed(FLAG, 8);
	sprite[0]->addKeyframe(FLAG, glm::vec2(0.777f, 0.75f));
	sprite[0]->addKeyframe(FLAG, glm::vec2(0.888f, 0.75f));

	sprite[0]->setAnimationSpeed(STAND_LEFT_STAR, 2);
	sprite[0]->addKeyframe(STAND_LEFT_STAR, glm::vec2(0.f, 0.125f));
	sprite[0]->addKeyframe(STAND_LEFT_STAR, glm::vec2(0.f, 0.375f));
	sprite[0]->addKeyframe(STAND_LEFT_STAR, glm::vec2(0.f, 0.625f));

	sprite[0]->setAnimationSpeed(STAND_RIGHT_STAR, 2);
	sprite[0]->addKeyframe(STAND_RIGHT_STAR, glm::vec2(0.f, 0.f));
	sprite[0]->addKeyframe(STAND_RIGHT_STAR, glm::vec2(0.f, 0.25f));
	sprite[0]->addKeyframe(STAND_RIGHT_STAR, glm::vec2(0.f, 0.5));

	sprite[0]->setAnimationSpeed(MOVE_LEFT_STAR, 8);
	sprite[0]->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.111f, 0.125f));
	sprite[0]->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.111f, 0.375f));
	sprite[0]->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.111f, 0.625f));
	sprite[0]->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.222f, 0.125f));
	sprite[0]->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.222f, 0.375f));
	sprite[0]->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.222f, 0.625f));
	sprite[0]->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.333f, 0.125f));
	sprite[0]->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.333f, 0.375f));
	sprite[0]->addKeyframe(MOVE_LEFT_STAR, glm::vec2(0.333f, 0.625f));

	sprite[0]->setAnimationSpeed(MOVE_RIGHT_STAR, 8);
	sprite[0]->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.111f, 0.f));
	sprite[0]->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.111f, 0.25f));
	sprite[0]->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.111f, 0.5f));
	sprite[0]->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.222f, 0.0f));
	sprite[0]->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.222f, 0.25f));
	sprite[0]->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.222f, 0.5f));
	sprite[0]->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.333f, 0.f));
	sprite[0]->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.333f, 0.25f));
	sprite[0]->addKeyframe(MOVE_RIGHT_STAR, glm::vec2(0.333f, 0.5f));

	sprite[0]->setAnimationSpeed(JUMP_FALL_RIGHT_STAR, 8);
	sprite[0]->addKeyframe(JUMP_FALL_RIGHT_STAR, glm::vec2(0.555f, 0.f));
	sprite[0]->addKeyframe(JUMP_FALL_RIGHT_STAR, glm::vec2(0.555f, 0.25f));
	sprite[0]->addKeyframe(JUMP_FALL_RIGHT_STAR, glm::vec2(0.555f, 0.5f));

	sprite[0]->setAnimationSpeed(JUMP_FALL_LEFT_STAR, 8);
	sprite[0]->addKeyframe(JUMP_FALL_LEFT_STAR, glm::vec2(0.555f, 0.125f));
	sprite[0]->addKeyframe(JUMP_FALL_LEFT_STAR, glm::vec2(0.555f, 0.375f));
	sprite[0]->addKeyframe(JUMP_FALL_LEFT_STAR, glm::vec2(0.555f, 0.625f));

	sprite[0]->setAnimationSpeed(DELAY_CHANGE_DIRECTION_RIGHT_STAR, 8);
	sprite[0]->addKeyframe(DELAY_CHANGE_DIRECTION_RIGHT_STAR, glm::vec2(0.444f, 0.f));
	sprite[0]->addKeyframe(DELAY_CHANGE_DIRECTION_RIGHT_STAR, glm::vec2(0.444f, 0.25f));
	sprite[0]->addKeyframe(DELAY_CHANGE_DIRECTION_RIGHT_STAR, glm::vec2(0.444f, 0.5f));

	sprite[0]->setAnimationSpeed(DELAY_CHANGE_DIRECTION_LEFT_STAR, 8);
	sprite[0]->addKeyframe(DELAY_CHANGE_DIRECTION_LEFT_STAR, glm::vec2(0.444f, 0.125f));
	sprite[0]->addKeyframe(DELAY_CHANGE_DIRECTION_LEFT_STAR, glm::vec2(0.444f, 0.375f));
	sprite[0]->addKeyframe(DELAY_CHANGE_DIRECTION_LEFT_STAR, glm::vec2(0.444f, 0.625f));

	sprite[0]->setAnimationSpeed(FLAG_STAR, 8);
	sprite[0]->addKeyframe(FLAG_STAR, glm::vec2(0.777f, 0.f));
	sprite[0]->addKeyframe(FLAG_STAR, glm::vec2(0.777f, 0.25f));
	sprite[0]->addKeyframe(FLAG_STAR, glm::vec2(0.777f, 0.5f));
	sprite[0]->addKeyframe(FLAG_STAR, glm::vec2(0.888f, 0.f));
	sprite[0]->addKeyframe(FLAG_STAR, glm::vec2(0.888f, 0.25f));
	sprite[0]->addKeyframe(FLAG_STAR, glm::vec2(0.888f, 0.5f));

	sprite[0]->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite[0]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
	spritesheet[1].loadFromFile("images/BigMarioStar.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite[1] = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.111, 0.125), &spritesheet[1], &shaderProgram);
	sprite[1]->setNumberAnimations(24);

	sprite[1]->setAnimationSpeed(B_STAND_LEFT, 8);
	sprite[1]->addKeyframe(B_STAND_LEFT, glm::vec2(0.f, 0.875f));

	sprite[1]->setAnimationSpeed(B_STAND_RIGHT, 8);
	sprite[1]->addKeyframe(B_STAND_RIGHT, glm::vec2(0.f, 0.75f));

	sprite[1]->setAnimationSpeed(B_MOVE_LEFT, 8);
	sprite[1]->addKeyframe(B_MOVE_LEFT, glm::vec2(0.111f, 0.875f));
	sprite[1]->addKeyframe(B_MOVE_LEFT, glm::vec2(0.222f, 0.875f));
	sprite[1]->addKeyframe(B_MOVE_LEFT, glm::vec2(0.333f, 0.875f));

	sprite[1]->setAnimationSpeed(B_MOVE_RIGHT, 8);
	sprite[1]->addKeyframe(B_MOVE_RIGHT, glm::vec2(0.111f, 0.75f));
	sprite[1]->addKeyframe(B_MOVE_RIGHT, glm::vec2(0.222f, 0.75f));
	sprite[1]->addKeyframe(B_MOVE_RIGHT, glm::vec2(0.333f, 0.75f));

	sprite[1]->setAnimationSpeed(B_JUMP_FALL_RIGHT, 8);
	sprite[1]->addKeyframe(B_JUMP_FALL_RIGHT, glm::vec2(0.555f, 0.75f));

	sprite[1]->setAnimationSpeed(B_JUMP_FALL_LEFT, 8);
	sprite[1]->addKeyframe(B_JUMP_FALL_LEFT, glm::vec2(0.555f, 0.875f));

	sprite[1]->setAnimationSpeed(B_DELAY_CHANGE_DIRECTION_RIGHT, 8);
	sprite[1]->addKeyframe(B_DELAY_CHANGE_DIRECTION_RIGHT, glm::vec2(0.444f, 0.75f));

	sprite[1]->setAnimationSpeed(B_DELAY_CHANGE_DIRECTION_LEFT, 8);
	sprite[1]->addKeyframe(B_DELAY_CHANGE_DIRECTION_LEFT, glm::vec2(0.444f, 0.875f));

	sprite[1]->setAnimationSpeed(B_DIE, 8);
	sprite[1]->addKeyframe(B_DIE, glm::vec2(0.666f, 0.75f));

	sprite[1]->setAnimationSpeed(B_FLAG, 8);
	sprite[1]->addKeyframe(B_FLAG, glm::vec2(0.777f, 0.75f));
	sprite[1]->addKeyframe(B_FLAG, glm::vec2(0.888f, 0.75f));

	sprite[1]->setAnimationSpeed(MID_RIGHT, 8);
	sprite[1]->addKeyframe(MID_RIGHT, glm::vec2(0.888f, 0.75f));

	sprite[1]->setAnimationSpeed(MID_LEFT, 8);
	sprite[1]->addKeyframe(MID_LEFT, glm::vec2(0.888f, 0.875f));

	sprite[1]->setAnimationSpeed(B_STAND_LEFT_STAR, 2);
	sprite[1]->addKeyframe(B_STAND_LEFT_STAR, glm::vec2(0.f, 0.125f));
	sprite[1]->addKeyframe(B_STAND_LEFT_STAR, glm::vec2(0.f, 0.375f));
	sprite[1]->addKeyframe(B_STAND_LEFT_STAR, glm::vec2(0.f, 0.625f));

	sprite[1]->setAnimationSpeed(B_STAND_RIGHT_STAR, 2);
	sprite[1]->addKeyframe(B_STAND_RIGHT_STAR, glm::vec2(0.f, 0.f));
	sprite[1]->addKeyframe(B_STAND_RIGHT_STAR, glm::vec2(0.f, 0.25f));
	sprite[1]->addKeyframe(B_STAND_RIGHT_STAR, glm::vec2(0.f, 0.5));

	sprite[1]->setAnimationSpeed(B_MOVE_LEFT_STAR, 8);
	sprite[1]->addKeyframe(B_MOVE_LEFT_STAR, glm::vec2(0.111f, 0.125f));
	sprite[1]->addKeyframe(B_MOVE_LEFT_STAR, glm::vec2(0.111f, 0.375f));
	sprite[1]->addKeyframe(B_MOVE_LEFT_STAR, glm::vec2(0.111f, 0.625f));
	sprite[1]->addKeyframe(B_MOVE_LEFT_STAR, glm::vec2(0.222f, 0.125f));
	sprite[1]->addKeyframe(B_MOVE_LEFT_STAR, glm::vec2(0.222f, 0.375f));
	sprite[1]->addKeyframe(B_MOVE_LEFT_STAR, glm::vec2(0.222f, 0.625f));
	sprite[1]->addKeyframe(B_MOVE_LEFT_STAR, glm::vec2(0.333f, 0.125f));
	sprite[1]->addKeyframe(B_MOVE_LEFT_STAR, glm::vec2(0.333f, 0.375f));
	sprite[1]->addKeyframe(B_MOVE_LEFT_STAR, glm::vec2(0.333f, 0.625f));

	sprite[1]->setAnimationSpeed(B_MOVE_RIGHT_STAR, 8);
	sprite[1]->addKeyframe(B_MOVE_RIGHT_STAR, glm::vec2(0.111f, 0.f));
	sprite[1]->addKeyframe(B_MOVE_RIGHT_STAR, glm::vec2(0.111f, 0.25f));
	sprite[1]->addKeyframe(B_MOVE_RIGHT_STAR, glm::vec2(0.111f, 0.5f));
	sprite[1]->addKeyframe(B_MOVE_RIGHT_STAR, glm::vec2(0.222f, 0.0f));
	sprite[1]->addKeyframe(B_MOVE_RIGHT_STAR, glm::vec2(0.222f, 0.25f));
	sprite[1]->addKeyframe(B_MOVE_RIGHT_STAR, glm::vec2(0.222f, 0.5f));
	sprite[1]->addKeyframe(B_MOVE_RIGHT_STAR, glm::vec2(0.333f, 0.f));
	sprite[1]->addKeyframe(B_MOVE_RIGHT_STAR, glm::vec2(0.333f, 0.25f));
	sprite[1]->addKeyframe(B_MOVE_RIGHT_STAR, glm::vec2(0.333f, 0.5f));

	sprite[1]->setAnimationSpeed(B_JUMP_FALL_RIGHT_STAR, 8);
	sprite[1]->addKeyframe(B_JUMP_FALL_RIGHT_STAR, glm::vec2(0.555f, 0.f));
	sprite[1]->addKeyframe(B_JUMP_FALL_RIGHT_STAR, glm::vec2(0.555f, 0.25f));
	sprite[1]->addKeyframe(B_JUMP_FALL_RIGHT_STAR, glm::vec2(0.555f, 0.5f));

	sprite[1]->setAnimationSpeed(B_JUMP_FALL_LEFT_STAR, 8);
	sprite[1]->addKeyframe(B_JUMP_FALL_LEFT_STAR, glm::vec2(0.555f, 0.125f));
	sprite[1]->addKeyframe(B_JUMP_FALL_LEFT_STAR, glm::vec2(0.555f, 0.375f));
	sprite[1]->addKeyframe(B_JUMP_FALL_LEFT_STAR, glm::vec2(0.555f, 0.625f));

	sprite[1]->setAnimationSpeed(B_DELAY_CHANGE_DIRECTION_RIGHT_STAR, 8);
	sprite[1]->addKeyframe(B_DELAY_CHANGE_DIRECTION_RIGHT_STAR, glm::vec2(0.444f, 0.f));
	sprite[1]->addKeyframe(B_DELAY_CHANGE_DIRECTION_RIGHT_STAR, glm::vec2(0.444f, 0.25f));
	sprite[1]->addKeyframe(B_DELAY_CHANGE_DIRECTION_RIGHT_STAR, glm::vec2(0.444f, 0.5f));

	sprite[1]->setAnimationSpeed(B_DELAY_CHANGE_DIRECTION_LEFT_STAR, 8);
	sprite[1]->addKeyframe(B_DELAY_CHANGE_DIRECTION_LEFT_STAR, glm::vec2(0.444f, 0.125f));
	sprite[1]->addKeyframe(B_DELAY_CHANGE_DIRECTION_LEFT_STAR, glm::vec2(0.444f, 0.375f));
	sprite[1]->addKeyframe(B_DELAY_CHANGE_DIRECTION_LEFT_STAR, glm::vec2(0.444f, 0.625f));

	sprite[1]->setAnimationSpeed(B_FLAG_STAR, 8);
	sprite[1]->addKeyframe(B_FLAG_STAR, glm::vec2(0.777f, 0.f));
	sprite[1]->addKeyframe(B_FLAG_STAR, glm::vec2(0.777f, 0.25f));
	sprite[1]->addKeyframe(B_FLAG_STAR, glm::vec2(0.777f, 0.5f));
	sprite[1]->addKeyframe(B_FLAG_STAR, glm::vec2(0.888f, 0.f));
	sprite[1]->addKeyframe(B_FLAG_STAR, glm::vec2(0.888f, 0.25f));
	sprite[1]->addKeyframe(B_FLAG_STAR, glm::vec2(0.888f, 0.5f));

	sprite[1]->setAnimationSpeed(MID_RIGHT_STAR, 8);
	sprite[1]->addKeyframe(MID_RIGHT_STAR, glm::vec2(0.888f, 0.f));
	sprite[1]->addKeyframe(MID_RIGHT_STAR, glm::vec2(0.888f, 0.25f));
	sprite[1]->addKeyframe(MID_RIGHT_STAR, glm::vec2(0.888f, 0.5f));

	sprite[1]->setAnimationSpeed(MID_LEFT_STAR, 8);
	sprite[1]->addKeyframe(MID_LEFT_STAR, glm::vec2(0.888f, 0.125f));
	sprite[1]->addKeyframe(MID_LEFT_STAR, glm::vec2(0.888f, 0.375f));
	sprite[1]->addKeyframe(MID_LEFT_STAR, glm::vec2(0.888f, 0.625f));


	sprite[1]->changeAnimation(0);
	sprite[1]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	spritesheet[2].loadFromFile("images/16_8Score.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite[2] = Sprite::createSprite(glm::ivec2(16, 8), glm::vec2(1.f, 1/11.f), &spritesheet[2], &shaderProgram);
	sprite[2]->setNumberAnimations(11);

	sprite[2]->setAnimationSpeed(0, 2);
	sprite[2]->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite[2]->setAnimationSpeed(1, 2);
	sprite[2]->addKeyframe(1, glm::vec2(0.f, 1/11.f));

	sprite[2]->setAnimationSpeed(2, 2);
	sprite[2]->addKeyframe(2, glm::vec2(0.f, 2 / 11.f));

	sprite[2]->setAnimationSpeed(3, 2);
	sprite[2]->addKeyframe(3, glm::vec2(0.f, 3 / 11.f));

	sprite[2]->setAnimationSpeed(4, 2);
	sprite[2]->addKeyframe(4, glm::vec2(0.f, 4 / 11.f));

	sprite[2]->setAnimationSpeed(5, 2);
	sprite[2]->addKeyframe(5, glm::vec2(0.f, 5 / 11.f));

	sprite[2]->setAnimationSpeed(6, 2);
	sprite[2]->addKeyframe(6, glm::vec2(0.f, 6 / 11.f));

	sprite[2]->setAnimationSpeed(7, 2);
	sprite[2]->addKeyframe(7, glm::vec2(0.f, 7 / 11.f));

	sprite[2]->setAnimationSpeed(8, 2);
	sprite[2]->addKeyframe(8, glm::vec2(0.f, 8 / 11.f));

	sprite[2]->setAnimationSpeed(9, 2);
	sprite[2]->addKeyframe(9, glm::vec2(0.f, 9 / 11.f));

	sprite[2]->setAnimationSpeed(10, 2);
	sprite[2]->addKeyframe(10, glm::vec2(0.f, 10 / 11.f));

	sprite[2]->changeAnimation(0);
	sprite[2]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y - 16)));

	spritesheet[3].loadFromFile("images/MarioConvertion.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite[3] = Sprite::createSprite(glm::ivec2(16,32), glm::vec2(1/7.f, 1 / 2.f), &spritesheet[3], &shaderProgram);
	sprite[3]->setNumberAnimations(4);

	sprite[3]->setAnimationSpeed(0, 8);
	sprite[3]->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite[3]->addKeyframe(0, glm::vec2(1/7.f, 0.f));
	sprite[3]->addKeyframe(0, glm::vec2(2/7.f, 0.f));
	sprite[3]->addKeyframe(0, glm::vec2(3/7.f, 0.f));

	sprite[3]->setAnimationSpeed(1, 8);
	sprite[3]->addKeyframe(1, glm::vec2(3/7.f, 0.f));
	sprite[3]->addKeyframe(1, glm::vec2(4/7.f, 0.f));
	sprite[3]->addKeyframe(1, glm::vec2(5/7.f, 0.f));
	sprite[3]->addKeyframe(1, glm::vec2(6/7.f, 0.f));

	sprite[3]->setAnimationSpeed(2, 8);
	sprite[3]->addKeyframe(2, glm::vec2(0.f, 0.5f));
	sprite[3]->addKeyframe(2, glm::vec2(1 / 7.f, 0.5f));
	sprite[3]->addKeyframe(2, glm::vec2(2 / 7.f, 0.5f));
	sprite[3]->addKeyframe(2, glm::vec2(3 / 7.f, 0.5f));

	sprite[3]->setAnimationSpeed(3, 8);
	sprite[3]->addKeyframe(3, glm::vec2(3 / 7.f, 0.5f));
	sprite[3]->addKeyframe(3, glm::vec2(4 / 7.f, 0.5f));
	sprite[3]->addKeyframe(3, glm::vec2(5 / 7.f, 0.5f));
	sprite[3]->addKeyframe(3, glm::vec2(6 / 7.f, 0.5f));

	sprite[3]->changeAnimation(0);
	sprite[3]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y - 16)));
}

void Player::update(int deltaTime, float scroll)
{
	this->scroll = scroll;

	if (convertionTime > 0) {
		convertionTime -= deltaTime;
		sprite[3]->update(deltaTime, scroll);
	}
	else {
		sprite[0]->update(deltaTime, scroll);
		sprite[1]->update(deltaTime, scroll);
		sprite[2]->update(deltaTime, scroll);
		scoreAnimationTimer -= deltaTime;
		if (scoreAnimationTimer < 0) scoreAnimationTimer = 0;
		starButton();

		bigMarioButton();
		if (!mariomode) {
			SmallMario();
		}
		else {
			BigMario();
		}
	}
}

void Player::SmallMario() {
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (acces > -100) acces -= 2;

		if (!direction) direction = true;

		if (starmode && !bJumping) {
			if (sprite[0]->animation() != MOVE_LEFT_STAR)
				sprite[0]->changeAnimation(MOVE_LEFT_STAR);
		}
		else if (sprite[0]->animation() != MOVE_LEFT && !starmode)
			sprite[0]->changeAnimation(MOVE_LEFT);

		if (acces > 50 && !starmode && sprite[0]->animation() != DELAY_CHANGE_DIRECTION_LEFT && !bJumping) sprite[0]->changeAnimation(DELAY_CHANGE_DIRECTION_LEFT);
		else if (acces > 50 && starmode && sprite[0]->animation() != DELAY_CHANGE_DIRECTION_LEFT_STAR && !bJumping) sprite[0]->changeAnimation(DELAY_CHANGE_DIRECTION_LEFT_STAR);
		ScoreAnimation(0);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (acces < 100) acces += 2;

		if (direction) direction = false;

		if (starmode && !bJumping) {
			if (sprite[0]->animation() != MOVE_RIGHT_STAR)
				sprite[0]->changeAnimation(MOVE_RIGHT_STAR);
		}
		else if (sprite[0]->animation() != MOVE_RIGHT && !starmode)
			sprite[0]->changeAnimation(MOVE_RIGHT);

		if (acces < -50 && !starmode && sprite[0]->animation() != DELAY_CHANGE_DIRECTION_RIGHT && !bJumping) sprite[0]->changeAnimation(DELAY_CHANGE_DIRECTION_RIGHT);
		if (acces < -50 && starmode && sprite[0]->animation() != DELAY_CHANGE_DIRECTION_RIGHT_STAR && !bJumping) sprite[0]->changeAnimation(DELAY_CHANGE_DIRECTION_RIGHT_STAR);
	}
	else
	{
		if (acces > 0) acces -= 2;
		else if (acces < 0) acces += 2;

		if (acces == 0 && direction && !bJumping) {
			if (starmode && sprite[0]->animation() != STAND_LEFT_STAR) sprite[0]->changeAnimation(STAND_LEFT_STAR);
			else if (!starmode && sprite[0]->animation() != STAND_LEFT)
				sprite[0]->changeAnimation(STAND_LEFT);
		}
		else if (acces == 0 && !direction && !bJumping) {
			if (starmode && sprite[0]->animation() != STAND_RIGHT_STAR) sprite[0]->changeAnimation(STAND_RIGHT_STAR);
			else if (!starmode && sprite[0]->animation() != STAND_RIGHT)
				sprite[0]->changeAnimation(STAND_RIGHT);
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


	if (map->collisionMoveLeft(posPlayer, glm::ivec2(16, 16)) || posPlayer.x <= scroll)
	{
		posPlayer.x += speed;
		if (starmode && sprite[0]->animation() != STAND_LEFT_STAR) sprite[0]->changeAnimation(STAND_LEFT_STAR);
		else if (sprite[0]->animation() != STAND_LEFT) sprite[0]->changeAnimation(STAND_LEFT);
	}
	else if (map->collisionMoveRight(posPlayer, glm::ivec2(16, 16)))
	{
		posPlayer.x -= speed;
		if (starmode && sprite[0]->animation() != STAND_RIGHT_STAR) sprite[0]->changeAnimation(STAND_RIGHT_STAR);
		else if (sprite[0]->animation() != STAND_RIGHT)sprite[0]->changeAnimation(STAND_RIGHT);
	}

	if (bJumping)
	{
		if (direction && starmode && sprite[0]->animation() != JUMP_FALL_LEFT_STAR)
			sprite[0]->changeAnimation(JUMP_FALL_LEFT_STAR);
		else if (direction && !starmode && sprite[0]->animation() != JUMP_FALL_LEFT)
			sprite[0]->changeAnimation(JUMP_FALL_LEFT);
		else if (!direction && starmode && sprite[0]->animation() != JUMP_FALL_RIGHT_STAR)
			sprite[0]->changeAnimation(JUMP_FALL_RIGHT_STAR);
		else if (!direction && !starmode && sprite[0]->animation() != JUMP_FALL_RIGHT)
			sprite[0]->changeAnimation(JUMP_FALL_RIGHT);
		jumpAngle += JUMP_ANGLE_STEP;
		if (map->collisionMoveUp(posPlayer, glm::ivec2(16, 16), &posPlayer.y) && jumpAngle < 90) {
			jumpAngle = 180 - jumpAngle;
		}
		if (jumpAngle == 180)
		{
			bJumping = false;
			//posPlayer.y = startY;
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
			if (sprite[0]->animation() == JUMP_FALL_LEFT) sprite[0]->changeAnimation(STAND_LEFT);
			else if (sprite[0]->animation() == JUMP_FALL_RIGHT)sprite[0]->changeAnimation(STAND_RIGHT);
			else if (sprite[0]->animation() == JUMP_FALL_LEFT_STAR) sprite[0]->changeAnimation(STAND_LEFT_STAR);
			else if (sprite[0]->animation() == JUMP_FALL_RIGHT_STAR)sprite[0]->changeAnimation(STAND_RIGHT_STAR);

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
			if (direction && starmode && sprite[0]->animation() != JUMP_FALL_LEFT_STAR) sprite[0]->changeAnimation(JUMP_FALL_LEFT_STAR);
			else if (direction && !starmode && sprite[0]->animation() != JUMP_FALL_LEFT) sprite[0]->changeAnimation(JUMP_FALL_LEFT);
			else if (!direction && starmode && sprite[0]->animation() != JUMP_FALL_RIGHT_STAR) sprite[0]->changeAnimation(JUMP_FALL_RIGHT_STAR);
			else if (!direction && !starmode && sprite[0]->animation() != JUMP_FALL_RIGHT) sprite[0]->changeAnimation(JUMP_FALL_RIGHT);
		}
	}
	sprite[0]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::BigMario() {
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		BigMarioMiddle();
		if (direction && !starmode && sprite[1]->animation() != MID_LEFT)
			sprite[1]->changeAnimation(MID_LEFT);
		else if (direction && starmode && sprite[1]->animation() != MID_LEFT_STAR)
			sprite[1]->changeAnimation(MID_LEFT_STAR);
		else if (!direction && !starmode && sprite[1]->animation() != MID_RIGHT)
			sprite[1]->changeAnimation(MID_RIGHT);
		else if (!direction && starmode && sprite[1]->animation() != MID_RIGHT_STAR)
			sprite[1]->changeAnimation(MID_RIGHT_STAR);
	}
	else {
		BigMarioNormal(starmode);
	}
	sprite[1]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	if (convertionTime > 0)sprite[3]->render();
	else if (scoreAnimationTimer != 0) sprite[2]->render();
	else {
		if (!mariomode) {
			sprite[0]->render();
		}
		else {
			sprite[1]->render();
		}
	}
}


void Player::setStartMode(bool t) {
	starmode = t;
	
}

void Player::setJump() {
	bJumping = true;
	jumpAngle = 0;
	height = 15;
	startY = posPlayer.y;
}


void Player::setTileMap(TileMap* tileMap)
{
	map = tileMap;
	
}

void Player::setPosition(const glm::vec2& pos)
{

	if (!mariomode) {
		posPlayer = pos;
		sprite[0]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	}
	else {
		posPlayer = pos;
		sprite[1]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	}
}

bool Player::collisionInt() {
	if (!mariomode) {
		return map->collisionInt(posPlayer, glm::ivec2(16, 16), &posPlayer.y);
	}
	else {
		return map->collisionInt(posPlayer, glm::ivec2(16, 32), &posPlayer.y);
	}
	
	
}

glm::ivec2 Player::posInt() {
	if (!mariomode) {
		return map->posInt(posPlayer, glm::ivec2(16, 16), &posPlayer.y);
	}
	else {
		return map->posInt(posPlayer, glm::ivec2(16, 32), &posPlayer.y);
	}
}


glm::ivec2 Player::getPosition() {
	return posPlayer;
}


void Player::setSmall() {
	mariomode = false;
}

void Player::BigMarioNormal(bool st) {
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (acces > -100) acces -= 1;

		if (!direction) direction = true;
		if (st && !bJumping) {
			if (sprite[1]->animation() != B_MOVE_LEFT_STAR)
				sprite[1]->changeAnimation(B_MOVE_LEFT_STAR);
		}
		else if (sprite[1]->animation() != B_MOVE_LEFT && !st)
			sprite[1]->changeAnimation(B_MOVE_LEFT);

		if (acces > 50 && !st && sprite[1]->animation() != B_DELAY_CHANGE_DIRECTION_LEFT && !bJumping) sprite[1]->changeAnimation(B_DELAY_CHANGE_DIRECTION_LEFT);
		else if (acces > 50 && st && sprite[1]->animation() != B_DELAY_CHANGE_DIRECTION_LEFT_STAR && !bJumping) sprite[1]->changeAnimation(B_DELAY_CHANGE_DIRECTION_LEFT_STAR);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (acces < 100) acces += 1;

		if (direction) direction = false;
		if (st && !bJumping) {
			if (sprite[1]->animation() != B_MOVE_RIGHT_STAR)
				sprite[1]->changeAnimation(B_MOVE_RIGHT_STAR);
		}
		else if (sprite[1]->animation() != B_MOVE_RIGHT && !st)
			sprite[1]->changeAnimation(B_MOVE_RIGHT);

		if (acces < -50 && !st && sprite[1]->animation() != B_DELAY_CHANGE_DIRECTION_RIGHT && !bJumping) sprite[1]->changeAnimation(B_DELAY_CHANGE_DIRECTION_RIGHT);
		if (acces < -50 && st && sprite[1]->animation() != B_DELAY_CHANGE_DIRECTION_RIGHT_STAR && !bJumping) sprite[1]->changeAnimation(B_DELAY_CHANGE_DIRECTION_RIGHT_STAR);
	}
	else
	{
		if (acces > 0) acces -= 1;
		else if (acces < 0) acces += 1;

		if (acces == 0 && direction && !bJumping) {
			if (st && sprite[1]->animation() != B_STAND_LEFT_STAR) sprite[1]->changeAnimation(B_STAND_LEFT_STAR);
			else if (!st && sprite[1]->animation() != B_STAND_LEFT)
				sprite[1]->changeAnimation(B_STAND_LEFT);
		}
		else if (acces == 0 && !direction && !bJumping) {
			if (st && sprite[1]->animation() != B_STAND_RIGHT_STAR) sprite[1]->changeAnimation(B_STAND_RIGHT_STAR);
			else if (!st && sprite[1]->animation() != B_STAND_RIGHT)
				sprite[1]->changeAnimation(B_STAND_RIGHT);
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
		posPlayer.x += 1;
		accomulation = 0;
	}
	else if (accomulation <= -100) {
		posPlayer.x -= 1;
		accomulation = 0;
	}

	if (map->collisionMoveLeft(posPlayer, glm::ivec2(16, 32)) || posPlayer.x <= scroll)
	{
		posPlayer.x += speed;
		if (st && sprite[1]->animation() != B_STAND_LEFT_STAR) sprite[1]->changeAnimation(B_STAND_LEFT_STAR);
		else if (sprite[1]->animation() != B_STAND_LEFT) sprite[1]->changeAnimation(B_STAND_LEFT);
	}
	else if (map->collisionMoveRight(posPlayer, glm::ivec2(16, 32)))
	{
		posPlayer.x -= speed;
		if (st && sprite[1]->animation() != B_STAND_RIGHT_STAR) sprite[1]->changeAnimation(B_STAND_RIGHT_STAR);
		else if (sprite[1]->animation() != B_STAND_RIGHT)sprite[1]->changeAnimation(B_STAND_RIGHT);
	}

	if (bJumping)
	{
		if (direction && st && sprite[1]->animation() != B_JUMP_FALL_LEFT_STAR)
			sprite[1]->changeAnimation(B_JUMP_FALL_LEFT_STAR);
		else if (direction && !st && sprite[1]->animation() != B_JUMP_FALL_LEFT)
			sprite[1]->changeAnimation(B_JUMP_FALL_LEFT);
		else if (!direction && st && sprite[1]->animation() != B_JUMP_FALL_RIGHT_STAR)
			sprite[1]->changeAnimation(B_JUMP_FALL_RIGHT_STAR);
		else if (!direction && !st && sprite[1]->animation() != B_JUMP_FALL_RIGHT)
			sprite[1]->changeAnimation(B_JUMP_FALL_RIGHT);
		jumpAngle += JUMP_ANGLE_STEP;
		if (map->collisionMoveUp(posPlayer, glm::ivec2(16, 32), &posPlayer.y) && jumpAngle < 90) {
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
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(16, 32), &posPlayer.y);
			}

		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(16, 32), &posPlayer.y))
		{
			if (!firstJump && height != 0) height = 0;
			if (sprite[1]->animation() == B_JUMP_FALL_LEFT) sprite[1]->changeAnimation(B_STAND_LEFT);
			else if (sprite[1]->animation() == B_JUMP_FALL_RIGHT)sprite[1]->changeAnimation(B_STAND_RIGHT);
			else if (sprite[1]->animation() == B_JUMP_FALL_LEFT_STAR) sprite[1]->changeAnimation(B_STAND_LEFT_STAR);
			else if (sprite[1]->animation() == B_JUMP_FALL_RIGHT_STAR)sprite[1]->changeAnimation(B_STAND_RIGHT_STAR);

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
			if (direction && st && sprite[1]->animation() != B_JUMP_FALL_LEFT_STAR) sprite[1]->changeAnimation(B_JUMP_FALL_LEFT_STAR);
			else if (direction && !st && sprite[1]->animation() != B_JUMP_FALL_LEFT) sprite[1]->changeAnimation(B_JUMP_FALL_LEFT);
			else if (!direction && st && sprite[1]->animation() != B_JUMP_FALL_RIGHT_STAR) sprite[1]->changeAnimation(B_JUMP_FALL_RIGHT_STAR);
			else if (!direction && !st && sprite[1]->animation() != B_JUMP_FALL_RIGHT) sprite[1]->changeAnimation(B_JUMP_FALL_RIGHT);
		}
	}
}

void Player::BigMarioMiddle() {
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (acces > -100) acces -= 2;

		if (!direction) direction = true;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (acces < 100) acces += 2;

		if (direction) direction = false;
	}
	else
	{
		if (acces > 0) acces -= 2;
		else if (acces < 0) acces += 2;
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

	if (map->collisionMoveLeft(posPlayer, glm::ivec2(16, 24)) || posPlayer.x <= scroll )
	{
		posPlayer.x += 1;
	}
	else if (map->collisionMoveRight(posPlayer, glm::ivec2(16, 24)))
	{
		posPlayer.x -= 1;
	}

	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		posPlayer.y += 8;
		if (map->collisionMoveUp(glm::ivec2(posPlayer.x, posPlayer.y), glm::ivec2(16, 24), &posPlayer.y) && jumpAngle < 90) {
			jumpAngle = 180 - jumpAngle;
		}
		posPlayer.y -= 8;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - height * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90) {
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(16, 32), &posPlayer.y);
			}

		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(16, 32), &posPlayer.y))
		{
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
	}
}

void Player::starButton() {
	if (Game::instance().getKey(103) && prestar && !starmode) {
		starmode = true;
		prestar = false;
	}
	else if (Game::instance().getKey(103) && prestar && starmode) {
		starmode = false;
		prestar = false;
	}
	else if (!Game::instance().getKey(103) && !prestar) {
		prestar = true;
	}
}

void Player::bigMarioButton() {
	if (Game::instance().getKey(109) && premario && !mariomode) {
		posPlayer.y -= 16;
		mariomode = true;
		premario = false;
	}
	else if (Game::instance().getKey(109) && premario && mariomode) {
		mariomode = false;
		premario = false;
	}
	else if (!Game::instance().getKey(109) && !premario) {
		premario = true;
	}
}

void Player::ScoreAnimation(int i) {
	if (scoreAnimationTimer == 0) {
		scoreAnimationTimer = 500;
		sprite[2]->changeAnimation(i);
		sprite[2]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y - 16)));
	}
}

void Player::convertion(int i) {
	convertionTime = 500;
	if (sprite[3]->animation() == 0)sprite[3]->changeAnimation(i);
	sprite[3]->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}