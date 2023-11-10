#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Coins.h"
#include "Game.h"



enum jumpingMoneyAnim
{
	COIN
};


void Coins::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	delet = false;

	spritesheet.loadFromFile("images/Coin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1/3.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(COIN, 8);
	sprite->addKeyframe(COIN, glm::vec2(0 / 3.f, 1));
	sprite->addKeyframe(COIN, glm::vec2(1 / 3.f, 1.0f));
	sprite->addKeyframe(COIN, glm::vec2(2 / 3.f, 1.0f));
	sprite->addKeyframe(COIN, glm::vec2(0 / 3.f, 1));
	sprite->addKeyframe(COIN, glm::vec2(0 / 3.f, 1));


	sprite->changeAnimation(COIN);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

void Coins::update(int deltaTime, float scroll)
{
	sprite->update(deltaTime, scroll);

}

bool Coins::MarioCollide(glm::ivec2 playerpos) {

	if (playerpos.x <= position.x + 16 && playerpos.x >= position.x - 16) {
		if (playerpos.y >= position.y && playerpos.y <= position.y + 20) {
			delet = true;
			return true;
		}
	}

	return false;
}


bool Coins::needDelete() {
	return delet == true;
}

void Coins::render() {
	sprite->render();
}
