#include "GameUI.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


enum LN
{
	Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, MIDLINE, MULTIPLICATION, INTERROGANT, DOT, CICLEC, NOTHING

};

void GameUI::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	finish = false;
	ti = 0;
	coins = 0;
	time = 300;
	score = 0;
	world = 0;
	spritesheets.resize(2);
	row.resize(14);
	row2.resize(15);
	spritesheets[0].loadFromFile("images/LetterNumber.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[0].setMagFilter(GL_NEAREST);
	spritesheets[0].setMinFilter(GL_NEAREST);
	spritesheets[1].loadFromFile("images/GameUI-Coins8x8.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[1].setMagFilter(GL_NEAREST);
	spritesheets[1].setMinFilter(GL_NEAREST);
	for (int i = 0; i < row.size(); i++) {
		row[i] = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0.0625, 1 / 6.f), &spritesheets[0], &shaderProgram);
		row[i]->setNumberAnimations(42);

		row[i]->setAnimationSpeed(0, 4);
		row[i]->addKeyframe(0, glm::vec2(0.f, 0.f));

		row[i]->setAnimationSpeed(1, 4);
		row[i]->addKeyframe(1, glm::vec2(0.0625, 0.f));

		row[i]->setAnimationSpeed(2, 4);
		row[i]->addKeyframe(2, glm::vec2(0.125f, 0.f));

		row[i]->setAnimationSpeed(3, 4);
		row[i]->addKeyframe(3, glm::vec2(0.1875f, 0.f));

		row[i]->setAnimationSpeed(4, 4);
		row[i]->addKeyframe(4, glm::vec2(0.25f, 0.f));

		row[i]->setAnimationSpeed(5, 4);
		row[i]->addKeyframe(5, glm::vec2(0.3125f, 0.f));

		row[i]->setAnimationSpeed(6, 4);
		row[i]->addKeyframe(6, glm::vec2(0.375f, 0.f));

		row[i]->setAnimationSpeed(7, 4);
		row[i]->addKeyframe(7, glm::vec2(0.4375f, 0.f));

		row[i]->setAnimationSpeed(8, 4);
		row[i]->addKeyframe(8, glm::vec2(0.5f, 0.f));

		row[i]->setAnimationSpeed(9, 4);
		row[i]->addKeyframe(9, glm::vec2(0.5625f, 0.f));

		row[i]->setAnimationSpeed(10, 4);
		row[i]->addKeyframe(10, glm::vec2(0.625f, 0.f));

		row[i]->setAnimationSpeed(11, 4);
		row[i]->addKeyframe(11, glm::vec2(0.6875, 0 / 6.f));

		row[i]->setAnimationSpeed(12, 4);
		row[i]->addKeyframe(12, glm::vec2(0.75f, 0 / 6.f));

		row[i]->setAnimationSpeed(13, 4);
		row[i]->addKeyframe(13, glm::vec2(0.8125f, 0 / 6.f));

		row[i]->setAnimationSpeed(14, 4);
		row[i]->addKeyframe(14, glm::vec2(0.875f, 0 / 6.f));

		row[i]->setAnimationSpeed(15, 4);
		row[i]->addKeyframe(15, glm::vec2(0.9375f, 0 / 6.f));

		row[i]->setAnimationSpeed(16, 4);
		row[i]->addKeyframe(16, glm::vec2(0.f, 1 / 6.f));

		row[i]->setAnimationSpeed(17, 4);
		row[i]->addKeyframe(17, glm::vec2(0.0625, 1 / 6.f));

		row[i]->setAnimationSpeed(18, 4);
		row[i]->addKeyframe(18, glm::vec2(0.125f, 1 / 6.f));

		row[i]->setAnimationSpeed(19, 4);
		row[i]->addKeyframe(19, glm::vec2(0.1875f, 1 / 6.f));

		row[i]->setAnimationSpeed(20, 4);
		row[i]->addKeyframe(20, glm::vec2(0.25f, 1 / 6.f));

		row[i]->setAnimationSpeed(21, 4);
		row[i]->addKeyframe(21, glm::vec2(0.3125f, 1 / 6.f));

		row[i]->setAnimationSpeed(22, 4);
		row[i]->addKeyframe(22, glm::vec2(0.375f, 1 / 6.f));

		row[i]->setAnimationSpeed(23, 4);
		row[i]->addKeyframe(23, glm::vec2(0.4375f, 1 / 6.f));

		row[i]->setAnimationSpeed(24, 4);
		row[i]->addKeyframe(24, glm::vec2(0.5f, 1 / 6.f));

		row[i]->setAnimationSpeed(25, 4);
		row[i]->addKeyframe(25, glm::vec2(0.5625f, 1 / 6.f));

		row[i]->setAnimationSpeed(26, 4);
		row[i]->addKeyframe(26, glm::vec2(0.625f, 1 / 6.f));

		row[i]->setAnimationSpeed(27, 4);
		row[i]->addKeyframe(27, glm::vec2(0.6875, 1 / 6.f));

		row[i]->setAnimationSpeed(28, 4);
		row[i]->addKeyframe(28, glm::vec2(0.75f, 1 / 6.f));

		row[i]->setAnimationSpeed(29, 4);
		row[i]->addKeyframe(29, glm::vec2(0.8125f, 1 / 6.f));

		row[i]->setAnimationSpeed(30, 4);
		row[i]->addKeyframe(30, glm::vec2(0.875f, 1 / 6.f));

		row[i]->setAnimationSpeed(31, 4);
		row[i]->addKeyframe(31, glm::vec2(0.9375f, 1 / 6.f));

		row[i]->setAnimationSpeed(32, 4);
		row[i]->addKeyframe(32, glm::vec2(0.f, 2 / 6.f));

		row[i]->setAnimationSpeed(33, 4);
		row[i]->addKeyframe(33, glm::vec2(0.0625, 2 / 6.f));

		row[i]->setAnimationSpeed(34, 4);
		row[i]->addKeyframe(34, glm::vec2(0.125f, 2 / 6.f));

		row[i]->setAnimationSpeed(35, 4);
		row[i]->addKeyframe(35, glm::vec2(0.1875f, 2 / 6.f));

		row[i]->setAnimationSpeed(36, 4);
		row[i]->addKeyframe(36, glm::vec2(0.25f, 2 / 6.f));

		row[i]->setAnimationSpeed(37, 4);
		row[i]->addKeyframe(37, glm::vec2(0.3125f, 2 / 6.f));

		row[i]->setAnimationSpeed(38, 4);
		row[i]->addKeyframe(38, glm::vec2(0.375f, 2 / 6.f));

		row[i]->setAnimationSpeed(39, 4);
		row[i]->addKeyframe(39, glm::vec2(0.4375f, 2 / 6.f));

		row[i]->setAnimationSpeed(40, 4);
		row[i]->addKeyframe(40, glm::vec2(0.5f, 2 / 6.f));

		row[i]->setAnimationSpeed(41, 4);
		row[i]->addKeyframe(41, glm::vec2(0.5625f, 2 / 6.f));

		row[i]->changeAnimation(40);
		tileMapDispl = tileMapPos;
		row[i]->setPosition(glm::vec2(float(tileMapDispl.x + i * 8), float(tileMapDispl.y + 16)));
	}
	for (int i = 0; i < row2.size(); i++) {
		if (i != 5) {
			row2[i] = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0.0625, 1 / 6.f), &spritesheets[0], &shaderProgram);
			row2[i]->setNumberAnimations(42);

			row2[i]->setAnimationSpeed(0, 4);
			row2[i]->addKeyframe(0, glm::vec2(0.f, 0.f));

			row2[i]->setAnimationSpeed(1, 4);
			row2[i]->addKeyframe(1, glm::vec2(0.0625, 0.f));

			row2[i]->setAnimationSpeed(2, 4);
			row2[i]->addKeyframe(2, glm::vec2(0.125f, 0.f));

			row2[i]->setAnimationSpeed(3, 4);
			row2[i]->addKeyframe(3, glm::vec2(0.1875f, 0.f));

			row2[i]->setAnimationSpeed(4, 4);
			row2[i]->addKeyframe(4, glm::vec2(0.25f, 0.f));

			row2[i]->setAnimationSpeed(5, 4);
			row2[i]->addKeyframe(5, glm::vec2(0.3125f, 0.f));

			row2[i]->setAnimationSpeed(6, 4);
			row2[i]->addKeyframe(6, glm::vec2(0.375f, 0.f));

			row2[i]->setAnimationSpeed(7, 4);
			row2[i]->addKeyframe(7, glm::vec2(0.4375f, 0.f));

			row2[i]->setAnimationSpeed(8, 4);
			row2[i]->addKeyframe(8, glm::vec2(0.5f, 0.f));

			row2[i]->setAnimationSpeed(9, 4);
			row2[i]->addKeyframe(9, glm::vec2(0.5625f, 0.f));

			row2[i]->setAnimationSpeed(10, 4);
			row2[i]->addKeyframe(10, glm::vec2(0.625f, 0.f));

			row2[i]->setAnimationSpeed(11, 4);
			row2[i]->addKeyframe(11, glm::vec2(0.6875, 0.f));

			row2[i]->setAnimationSpeed(12, 4);
			row2[i]->addKeyframe(12, glm::vec2(0.75f, 0.f));

			row2[i]->setAnimationSpeed(13, 4);
			row2[i]->addKeyframe(13, glm::vec2(0.8125f, 0.f));

			row2[i]->setAnimationSpeed(14, 4);
			row2[i]->addKeyframe(14, glm::vec2(0.875f, 0.f));

			row2[i]->setAnimationSpeed(15, 4);
			row2[i]->addKeyframe(15, glm::vec2(0.9375f, 0.f));

			row2[i]->setAnimationSpeed(16, 4);
			row2[i]->addKeyframe(16, glm::vec2(0.f, 1 / 6.f));

			row2[i]->setAnimationSpeed(17, 4);
			row2[i]->addKeyframe(17, glm::vec2(0.0625, 1 / 6.f));

			row2[i]->setAnimationSpeed(18, 4);
			row2[i]->addKeyframe(18, glm::vec2(0.125f, 1 / 6.f));

			row2[i]->setAnimationSpeed(19, 4);
			row2[i]->addKeyframe(19, glm::vec2(0.1875f, 1 / 6.f));

			row2[i]->setAnimationSpeed(20, 4);
			row2[i]->addKeyframe(20, glm::vec2(0.25f, 1 / 6.f));

			row2[i]->setAnimationSpeed(21, 4);
			row2[i]->addKeyframe(21, glm::vec2(0.3125f, 1 / 6.f));

			row2[i]->setAnimationSpeed(22, 4);
			row2[i]->addKeyframe(22, glm::vec2(0.375f, 1 / 6.f));

			row2[i]->setAnimationSpeed(23, 4);
			row2[i]->addKeyframe(23, glm::vec2(0.4375f, 1 / 6.f));

			row2[i]->setAnimationSpeed(24, 4);
			row2[i]->addKeyframe(24, glm::vec2(0.5f, 1 / 6.f));

			row2[i]->setAnimationSpeed(25, 4);
			row2[i]->addKeyframe(25, glm::vec2(0.5625f, 1 / 6.f));

			row2[i]->setAnimationSpeed(26, 4);
			row2[i]->addKeyframe(26, glm::vec2(0.625f, 1 / 6.f));

			row2[i]->setAnimationSpeed(27, 4);
			row2[i]->addKeyframe(27, glm::vec2(0.6875, 1 / 6.f));

			row2[i]->setAnimationSpeed(28, 4);
			row2[i]->addKeyframe(28, glm::vec2(0.75f, 1 / 6.f));

			row2[i]->setAnimationSpeed(29, 4);
			row2[i]->addKeyframe(29, glm::vec2(0.8125f, 1 / 6.f));

			row2[i]->setAnimationSpeed(30, 4);
			row2[i]->addKeyframe(30, glm::vec2(0.875f, 1 / 6.f));

			row2[i]->setAnimationSpeed(31, 4);
			row2[i]->addKeyframe(31, glm::vec2(0.9375f, 1 / 6.f));

			row2[i]->setAnimationSpeed(32, 4);
			row2[i]->addKeyframe(32, glm::vec2(0.f, 2 / 6.f));

			row2[i]->setAnimationSpeed(33, 4);
			row2[i]->addKeyframe(33, glm::vec2(0.0625, 2 / 6.f));

			row2[i]->setAnimationSpeed(34, 4);
			row2[i]->addKeyframe(34, glm::vec2(0.125f, 2 / 6.f));

			row2[i]->setAnimationSpeed(35, 4);
			row2[i]->addKeyframe(35, glm::vec2(0.1875f, 2 / 6.f));

			row2[i]->setAnimationSpeed(36, 4);
			row2[i]->addKeyframe(36, glm::vec2(0.25f, 2 / 6.f));

			row2[i]->setAnimationSpeed(37, 4);
			row2[i]->addKeyframe(37, glm::vec2(0.3125f, 2 / 6.f));

			row2[i]->setAnimationSpeed(38, 4);
			row2[i]->addKeyframe(38, glm::vec2(0.375f, 2 / 6.f));

			row2[i]->setAnimationSpeed(39, 4);
			row2[i]->addKeyframe(39, glm::vec2(0.4375f, 2 / 6.f));

			row2[i]->setAnimationSpeed(40, 4);
			row2[i]->addKeyframe(40, glm::vec2(0.5f, 2 / 6.f));

			row2[i]->setAnimationSpeed(41, 4);
			row2[i]->addKeyframe(41, glm::vec2(0.625f, 2 / 6.f));

			row2[i]->changeAnimation(40);
			tileMapDispl = tileMapPos;
			row2[i]->setPosition(glm::vec2(float(tileMapDispl.x + i * 8), float(tileMapDispl.y + 24)));
		}
		else {
			row2[i] = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(1 / 7.f, 1.0f), &spritesheets[1], &shaderProgram);
			row2[i]->setNumberAnimations(1);
			row2[i]->setAnimationSpeed(0, 10);
			row2[5]->addKeyframe(0, glm::vec2(0.f, 0.f));
			row2[i]->addKeyframe(0, glm::vec2(1 / 7.f, 0.f));
			row2[5]->addKeyframe(0, glm::vec2(2 / 7.f, 0.f));
			row2[5]->addKeyframe(0, glm::vec2(3 / 7.f, 0.f));
			row2[5]->addKeyframe(0, glm::vec2(4 / 7.f, 0.f));
			row2[5]->addKeyframe(0, glm::vec2(5 / 7.f, 0.f));
			row2[5]->addKeyframe(0, glm::vec2(6 / 7.f, 0.f));
			row2[i]->changeAnimation(0);
			tileMapDispl = tileMapPos;
			row2[i]->setPosition(glm::vec2(float(tileMapDispl.x + i * 8), float(tileMapDispl.y + 24)));
		}

	}

	setFix();
	setDinamic();
}

void GameUI::update(int deltaTime, float scroll)
{
	if (finish) {
		updateTime();
		updateScore(10);
		updateTime();
		updateScore(10);
	}
	else {
		ti += deltaTime;
		if (ti >= 1000) {
			ti -= 1000;
			updateTime();
		}
		for (int i = 0; i < 14; i++) {
			row[i]->update(deltaTime, 0);
			//row[i]->setPosition(glm::vec2(float(tileMapDispl.x + i * 8), float(tileMapDispl.y + 16)));
		}
		for (int i = 0; i < 15; i++) {
			row2[i]->update(deltaTime, 0);
			//row2[i]->setPosition(glm::vec2(float(tileMapDispl.x + i * 8), float(tileMapDispl.y + 24)));
		}
	}

}
void GameUI::setFix() {
	row[0]->changeAnimation(M);
	row[0]->setPosition(glm::vec2(float(tileMapDispl.x + 3 * 8), float(tileMapDispl.y + 16)));
	row[1]->changeAnimation(A);
	row[1]->setPosition(glm::vec2(float(tileMapDispl.x + 4 * 8), float(tileMapDispl.y + 16)));
	row[2]->changeAnimation(R);
	row[2]->setPosition(glm::vec2(float(tileMapDispl.x + 5 * 8), float(tileMapDispl.y + 16)));
	row[3]->changeAnimation(I);
	row[3]->setPosition(glm::vec2(float(tileMapDispl.x + 6 * 8), float(tileMapDispl.y + 16)));
	row[4]->changeAnimation(O);
	row[4]->setPosition(glm::vec2(float(tileMapDispl.x + 7 * 8), float(tileMapDispl.y + 16)));
	row[5]->changeAnimation(W);
	row[5]->setPosition(glm::vec2(float(tileMapDispl.x + 17 * 8), float(tileMapDispl.y + 16)));
	row[6]->changeAnimation(O);
	row[6]->setPosition(glm::vec2(float(tileMapDispl.x + 18 * 8), float(tileMapDispl.y + 16)));
	row[7]->changeAnimation(R);
	row[7]->setPosition(glm::vec2(float(tileMapDispl.x + 19 * 8), float(tileMapDispl.y + 16)));
	row[8]->changeAnimation(L);
	row[8]->setPosition(glm::vec2(float(tileMapDispl.x + 20 * 8), float(tileMapDispl.y + 16)));
	row[9]->changeAnimation(D);
	row[9]->setPosition(glm::vec2(float(tileMapDispl.x + 21 * 8), float(tileMapDispl.y + 16)));
	row[10]->changeAnimation(T);
	row[10]->setPosition(glm::vec2(float(tileMapDispl.x + 24 * 8), float(tileMapDispl.y + 16)));
	row[11]->changeAnimation(I);
	row[11]->setPosition(glm::vec2(float(tileMapDispl.x + 25 * 8), float(tileMapDispl.y + 16)));
	row[12]->changeAnimation(M);
	row[12]->setPosition(glm::vec2(float(tileMapDispl.x + 26 * 8), float(tileMapDispl.y + 16)));
	row[13]->changeAnimation(E);
	row[13]->setPosition(glm::vec2(float(tileMapDispl.x + 27 * 8), float(tileMapDispl.y + 16)));
}

void GameUI::setDinamic() {
	row2[0]->changeAnimation(Zero);
	row2[0]->setPosition(glm::vec2(float(tileMapDispl.x + 3 * 8), float(tileMapDispl.y + 24)));
	row2[1]->changeAnimation(Zero);
	row2[1]->setPosition(glm::vec2(float(tileMapDispl.x + 4 * 8), float(tileMapDispl.y + 24)));
	row2[2]->changeAnimation(Zero);
	row2[2]->setPosition(glm::vec2(float(tileMapDispl.x + 5 * 8), float(tileMapDispl.y + 24)));
	row2[3]->changeAnimation(Zero);
	row2[3]->setPosition(glm::vec2(float(tileMapDispl.x + 6 * 8), float(tileMapDispl.y + 24)));
	row2[4]->changeAnimation(Zero);
	row2[4]->setPosition(glm::vec2(float(tileMapDispl.x + 7 * 8), float(tileMapDispl.y + 24)));
	row2[5]->changeAnimation(0);
	row2[5]->setPosition(glm::vec2(float(tileMapDispl.x + 10 * 8), float(tileMapDispl.y + 24)));
	row2[6]->changeAnimation(MULTIPLICATION);
	row2[6]->setPosition(glm::vec2(float(tileMapDispl.x + 11 * 8), float(tileMapDispl.y + 24)));
	row2[7]->changeAnimation(Zero);
	row2[7]->setPosition(glm::vec2(float(tileMapDispl.x + 12 * 8), float(tileMapDispl.y + 24)));
	row2[8]->changeAnimation(Zero);
	row2[8]->setPosition(glm::vec2(float(tileMapDispl.x + 13 * 8), float(tileMapDispl.y + 24)));
	row2[9]->changeAnimation(One);
	row2[9]->setPosition(glm::vec2(float(tileMapDispl.x + 18 * 8), float(tileMapDispl.y + 24)));
	row2[10]->changeAnimation(MIDLINE);
	row2[10]->setPosition(glm::vec2(float(tileMapDispl.x + 19 * 8), float(tileMapDispl.y + 24)));
	row2[11]->changeAnimation(One);
	row2[11]->setPosition(glm::vec2(float(tileMapDispl.x + 20 * 8), float(tileMapDispl.y + 24)));
	row2[12]->changeAnimation(Zero);
	row2[12]->setPosition(glm::vec2(float(tileMapDispl.x + 25 * 8), float(tileMapDispl.y + 24)));
	row2[13]->changeAnimation(Zero);
	row2[13]->setPosition(glm::vec2(float(tileMapDispl.x + 26 * 8), float(tileMapDispl.y + 24)));
	row2[14]->changeAnimation(Zero);
	row2[14]->setPosition(glm::vec2(float(tileMapDispl.x + 27 * 8), float(tileMapDispl.y + 24)));
}

void GameUI::render()
{
	for (int i = 0; i < 14; i++) {
		row[i]->render();
	}
	for (int i = 0; i < 15; i++) {
		row2[i]->render();
	}
}

void GameUI::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void GameUI::setPosPlayer(glm::ivec2 pos) {
	posPlayer = pos;
}

void GameUI::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
}

void GameUI::updateCoins() {
	coins++;
	row2[7]->changeAnimation(coins / 10);
	row2[8]->changeAnimation(coins % 10);
}
void GameUI::updateWorld(int w) {
	world = w;
	row2[11]->changeAnimation(w);
}
void GameUI::updateTime() {
	time--;
	row2[12]->changeAnimation(time / 100);
	row2[13]->changeAnimation((time / 10) % 10);
	row2[14]->changeAnimation(time % 10);
}
void GameUI::updateScore(int s) {
	score += s;
	row2[0]->changeAnimation(score / 10000);
	row2[1]->changeAnimation((score / 1000) % 10);
	row2[2]->changeAnimation((score / 100) % 10);
	row2[3]->changeAnimation((score / 10) % 10);
	row2[4]->changeAnimation(score % 10);
}


glm::ivec2 GameUI::getPosition() {
	return posPlayer;
}

void GameUI::clear() {
	coins = 0;
	time = 300;
	score = 0;
	world = 0;
}

void GameUI::reset(int s, int c, int w, int t) {
	score = s;
	coins = c;
	time = t;
	world = w;
}

void GameUI::setFinish() {
	finish = true;
}