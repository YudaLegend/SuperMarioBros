#include "OtherScenes.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <GL/glew.h>
#include <GL/glut.h>
#define SCREEN_X 16
#define SCREEN_Y 16
OtherScenes::OtherScenes() {}
OtherScenes::~OtherScenes() {}
void OtherScenes::reshape(int w, int h) {
	float scale = h / 480.f;
	float offset = (w - 8 * 16 * scale) / 2;

	projection = glm::ortho(16.f, w - offset, 240.f + 16.f, 16.f);
	projection = glm::scale(projection, glm::vec3(scale));
}
void OtherScenes::init()
{
	pausamode = 0;
	
	spritesheets.resize(9);
	initShaders();
	spritesheets[0].loadFromFile("images/IniLevel1-1_life3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[0].setMagFilter(GL_NEAREST);
	spritesheets[0].setMinFilter(GL_NEAREST);
	spritesheets[1].loadFromFile("images/IniLevel1-1_life2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[1].setMagFilter(GL_NEAREST);
	spritesheets[1].setMinFilter(GL_NEAREST);
	spritesheets[2].loadFromFile("images/IniLevel1-1_life1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[2].setMagFilter(GL_NEAREST);
	spritesheets[2].setMinFilter(GL_NEAREST);
	spritesheets[3].loadFromFile("images/IniLevel1-2_life3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[3].setMagFilter(GL_NEAREST);
	spritesheets[3].setMinFilter(GL_NEAREST);
	spritesheets[4].loadFromFile("images/IniLevel1-2_life2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[4].setMagFilter(GL_NEAREST);
	spritesheets[4].setMinFilter(GL_NEAREST);
	spritesheets[5].loadFromFile("images/IniLevel1-2_life1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[5].setMagFilter(GL_NEAREST);
	spritesheets[5].setMinFilter(GL_NEAREST);
	spritesheets[6].loadFromFile("images/MarioGameOver.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[6].setMagFilter(GL_NEAREST);
	spritesheets[6].setMinFilter(GL_NEAREST);
	spritesheets[7].loadFromFile("images/Timeup.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[7].setMagFilter(GL_NEAREST);
	spritesheets[7].setMinFilter(GL_NEAREST);
	spritesheets[8].loadFromFile("images/BlackNumber.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[8].setMagFilter(GL_NEAREST);
	spritesheets[8].setMinFilter(GL_NEAREST);

	scenes.resize(20);
	scenes[0] = Sprite::createSprite(glm::ivec2(256, 240), glm::vec2(1.f, 1.f), &spritesheets[0], &texProgram);
	scenes[0]->setNumberAnimations(1);
	scenes[0]->setAnimationSpeed(0, 1);
	scenes[0]->addKeyframe(0, glm::vec2(0.f, 0.f));
	scenes[0]->changeAnimation(0);
	tileMapDispl = glm::vec2(float(SCREEN_X), float(SCREEN_Y));
	scenes[0]->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));


	scenes[1] = Sprite::createSprite(glm::ivec2(256, 240), glm::vec2(1.f, 1.f), &spritesheets[1], &texProgram);
	scenes[1]->setNumberAnimations(1);
	scenes[1]->setAnimationSpeed(0, 1);
	scenes[1]->addKeyframe(0, glm::vec2(0.f, 0.f));
	scenes[1]->changeAnimation(0);
	scenes[1]->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

	scenes[2] = Sprite::createSprite(glm::ivec2(256, 240), glm::vec2(1.f, 1.f), &spritesheets[2], &texProgram);
	scenes[2]->setNumberAnimations(1);
	scenes[2]->setAnimationSpeed(0, 1);
	scenes[2]->addKeyframe(0, glm::vec2(0.f, 0.f));
	scenes[2]->changeAnimation(0);
	scenes[2]->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

	scenes[3] = Sprite::createSprite(glm::ivec2(256, 240), glm::vec2(1.f, 1.f), &spritesheets[3], &texProgram);
	scenes[3]->setNumberAnimations(1);
	scenes[3]->setAnimationSpeed(0, 1);
	scenes[3]->addKeyframe(0, glm::vec2(0.f, 0.f));
	scenes[3]->changeAnimation(0);
	scenes[3]->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

	scenes[4] = Sprite::createSprite(glm::ivec2(256, 240), glm::vec2(1.f, 1.f), &spritesheets[4], &texProgram);
	scenes[4]->setNumberAnimations(1);
	scenes[4]->setAnimationSpeed(0, 1);
	scenes[4]->addKeyframe(0, glm::vec2(0.f, 0.f));
	scenes[4]->changeAnimation(0);
	scenes[4]->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

	scenes[5] = Sprite::createSprite(glm::ivec2(256, 240), glm::vec2(1.f, 1.f), &spritesheets[5], &texProgram);
	scenes[5]->setNumberAnimations(1);
	scenes[5]->setAnimationSpeed(0, 1);
	scenes[5]->addKeyframe(0, glm::vec2(0.f, 0.f));
	scenes[5]->changeAnimation(0);
	scenes[5]->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

	scenes[6] = Sprite::createSprite(glm::ivec2(256, 240), glm::vec2(1.f, 1.f), &spritesheets[6], &texProgram);
	scenes[6]->setNumberAnimations(1);
	scenes[6]->setAnimationSpeed(0, 1);
	scenes[6]->addKeyframe(0, glm::vec2(0.f, 0.f));
	scenes[6]->changeAnimation(0);
	scenes[6]->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

	scenes[7] = Sprite::createSprite(glm::ivec2(256, 240), glm::vec2(1.f, 1.f), &spritesheets[7], &texProgram);
	scenes[7]->setNumberAnimations(1);
	scenes[7]->setAnimationSpeed(0, 1);
	scenes[7]->addKeyframe(0, glm::vec2(0.f, 0.f));
	scenes[7]->changeAnimation(0);
	scenes[7]->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

	for (int i = 8; i < scenes.size(); i++) {
		scenes[i] = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0.1f, 1.f), &spritesheets[8], &texProgram);
		scenes[i]->setNumberAnimations(10);

		scenes[i]->setAnimationSpeed(0, 2);
		scenes[i]->addKeyframe(0, glm::vec2(0.f, 0.f));

		scenes[i]->setAnimationSpeed(1, 2);
		scenes[i]->addKeyframe(1, glm::vec2(0.1f, 0.f));

		scenes[i]->setAnimationSpeed(2, 2);
		scenes[i]->addKeyframe(2, glm::vec2(0.2f, 0.f));

		scenes[i]->setAnimationSpeed(3, 2);
		scenes[i]->addKeyframe(3, glm::vec2(0.3f, 0.f));

		scenes[i]->setAnimationSpeed(4, 2);
		scenes[i]->addKeyframe(4, glm::vec2(0.4f, 0.f));

		scenes[i]->setAnimationSpeed(5, 2);
		scenes[i]->addKeyframe(5, glm::vec2(0.5f, 0.f));

		scenes[i]->setAnimationSpeed(6, 2);
		scenes[i]->addKeyframe(6, glm::vec2(0.6f, 0.f));

		scenes[i]->setAnimationSpeed(7, 2);
		scenes[i]->addKeyframe(7, glm::vec2(0.7f, 0.f));

		scenes[i]->setAnimationSpeed(8, 2);
		scenes[i]->addKeyframe(8, glm::vec2(0.8f, 0.f));

		scenes[i]->setAnimationSpeed(9, 2);
		scenes[i]->addKeyframe(9, glm::vec2(0.9f, 0.f));

		scenes[i]->changeAnimation(0);
		
	}
	scenes[8]->setPosition(glm::vec2(float(tileMapDispl.x + 3 * 8), float(tileMapDispl.y+24)));
	scenes[9]->setPosition(glm::vec2(float(tileMapDispl.x + 4 * 8), float(tileMapDispl.y + 24)));
	scenes[10]->setPosition(glm::vec2(float(tileMapDispl.x + 5 * 8), float(tileMapDispl.y + 24)));
	scenes[11]->setPosition(glm::vec2(float(tileMapDispl.x + 6 * 8), float(tileMapDispl.y + 24)));
	scenes[12]->setPosition(glm::vec2(float(tileMapDispl.x + 7 * 8), float(tileMapDispl.y + 24)));
	scenes[13]->setPosition(glm::vec2(float(tileMapDispl.x + 13 * 8), float(tileMapDispl.y + 24)));
	scenes[14]->setPosition(glm::vec2(float(tileMapDispl.x + 14 * 8), float(tileMapDispl.y + 24)));
	scenes[15]->setPosition(glm::vec2(float(tileMapDispl.x + 19 * 8), float(tileMapDispl.y + 24)));
	scenes[16]->setPosition(glm::vec2(float(tileMapDispl.x + 21 * 8), float(tileMapDispl.y + 24)));
	scenes[17]->setPosition(glm::vec2(float(tileMapDispl.x + 26 * 8), float(tileMapDispl.y + 24)));
	scenes[18]->setPosition(glm::vec2(float(tileMapDispl.x + 27 * 8), float(tileMapDispl.y + 24)));
	scenes[19]->setPosition(glm::vec2(float(tileMapDispl.x + 28 * 8), float(tileMapDispl.y + 24)));
	projection = glm::ortho(16.f, float(SCREEN_WIDTH) + 16.f, float(SCREEN_HEIGHT) + 16.f, 16.f);
	currentTime = 0.0f;
}

void OtherScenes::update(int deltaTime)
{
	currentTime += deltaTime;
	for (int i = 0; i < 20; i++) {
		scenes[i]->update(deltaTime, 0);
		//row[i]->setPosition(glm::vec2(float(tileMapDispl.x + i * 8), float(tileMapDispl.y + 16)));
	}
}

void OtherScenes::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(scroll, 0.f, 0.f)) * glm::mat4(1.0f);

	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	switch (pausamode) {
	case(0):
		scenes[pausamode]->render();
		break;
	case(1):
		scenes[pausamode]->render();
		break;
	case(2):
		scenes[pausamode]->render();
		break;
	case(3):
		scenes[pausamode]->render();
		break;
	case(4):
		scenes[pausamode]->render();
		break;
	case(5):
		scenes[pausamode]->render();
		break;
	case(6):
		scenes[pausamode]->render();
		scenes[8]->render();
		scenes[9]->render();
		scenes[10]->render();
		scenes[11]->render();
		scenes[12]->render();
		scenes[13]->render();
		scenes[14]->render();
		scenes[15]->render();
		scenes[16]->render();
		scenes[17]->render();
		scenes[18]->render();
		scenes[19]->render();
		break;
	case(7):
		scenes[pausamode]->render();
		scenes[8]->render();
		scenes[9]->render();
		scenes[10]->render();
		scenes[11]->render();
		scenes[12]->render();
		scenes[13]->render();
		scenes[14]->render();
		scenes[15]->render();
		scenes[16]->render();
		break;
	}
}

void OtherScenes::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void OtherScenes::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
}

void OtherScenes::setScore(int s) {
	score = s;
	scenes[8]->changeAnimation(score / 10000);
	scenes[9]->changeAnimation((score / 1000) % 10);
	scenes[10]->changeAnimation((score / 100) % 10);
	scenes[11]->changeAnimation((score / 10) % 10);
	scenes[12]->changeAnimation(score % 10);

}

void OtherScenes::setCoins(int c) {
	coins = c;
	scenes[13]->changeAnimation(coins / 10);
	scenes[14]->changeAnimation(coins % 10);
}

void OtherScenes::setWorld(int w) {
	scenes[15]->changeAnimation(1);
	scenes[16]->changeAnimation(w);
}

void OtherScenes::setTime(int t) {
	time = t;
	scenes[17]->changeAnimation(time / 100);
	scenes[18]->changeAnimation((time / 10) % 10);
	scenes[19]->changeAnimation(time % 10);
}

void OtherScenes::setPausaMode(int p) {
	pausamode = p;
}

void OtherScenes::initShaders() {
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}