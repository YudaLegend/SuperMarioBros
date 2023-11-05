#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "JumpingMoney.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum jumpingMoneyAnim
{
	MONEY
};


void JumpingMoney::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	hit = false;

	spritesheet.loadFromFile("images/JumpingCoins.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(8, 16), glm::vec2(1 / 4.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(MONEY, 32);
	sprite->addKeyframe(MONEY, glm::vec2(0 / 4.f, 1));
	sprite->addKeyframe(MONEY, glm::vec2(1 / 4.f, 0.0f));
	sprite->addKeyframe(MONEY, glm::vec2(2 / 4.f, 0.0f));
	sprite->addKeyframe(MONEY, glm::vec2(0 / 4.f, 1));


	sprite->changeAnimation(MONEY);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

void JumpingMoney::update(int deltaTime, float scroll)
{
	sprite->update(deltaTime, scroll);

	/*
	if (bJumping && hit)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			position.y = startY;
		}
		else
		{
			position.y = int(startY - 10 * sin(3.14159f * jumpAngle / 180.f));
			
		}
	}
	else if (hit)
	{
		position.y += FALL_STEP;	
		
	}
	*/


	if (hit) {
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 360)
		{
			hit = false;
			position.y = startY;
		}
		else
		{
			position.y = int(startY - 10 * sin(3.14159f * jumpAngle / 360.f));

		}

	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));

}

bool JumpingMoney::MarioDown(glm::ivec2 playerpos) {

	if ( playerpos.x <= position.x && playerpos.x >= position.x - 8 ) {
		if (playerpos.y >= position.y && playerpos.y <= position.y +20) {

			//Aqui funcion jump para hacer que salte
			bJumping = true;
			hit = true;

			return true;
		}
	}

	return false;
}


void JumpingMoney::render() {
	sprite->render();
}
