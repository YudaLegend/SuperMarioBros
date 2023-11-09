#include "MenuUI.h"
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

MenuUI::MenuUI()
{

}

MenuUI::~MenuUI()
{

}

void MenuUI::init()
{
	mode = 0;
	scenemode = -1;
	preselectup = false;
	preselectdown = false;
	preinfo1 = false;
	preinfo2 = false;
	initShaders();
	initshowOptions();
	projection = glm::ortho(16.f, float(SCREEN_WIDTH) + 16.f, float(SCREEN_HEIGHT) + 16.f, 16.f);
	currentTime = 0.0f;
}

void MenuUI::update(int deltaTime)
{
	currentTime += deltaTime;
	updateshowOptions();
}

void MenuUI::reshape(int w, int h) {
	float scale = h / 480.f;
	float offset = (w - 8 * 16 * scale) / 2;

	projection = glm::ortho(16.f, w - offset, 240.f + 16.f, 16.f);
	projection = glm::scale(projection, glm::vec3(scale));
}

void MenuUI::render()
{

	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(scroll, 0.f, 0.f)) * glm::mat4(1.0f);

	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	if (scenemode == -1) {
		for (int i = 0; i < elements.size() - 2; i++) {
			elements[i]->render();
		}
	}
	else if (scenemode == 2) {
		elements[7]->render();
	}
	else if (scenemode == 3) {
		elements[8]->render();
	}
}

void MenuUI::initShaders()
{
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
void MenuUI::initshowOptions() {
	spritesheets.resize(9);
	elements.resize(9);
	spritesheets[0].loadFromFile("images/NINTENDO.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[0].setMagFilter(GL_NEAREST);
	spritesheets[0].setMinFilter(GL_NEAREST);
	spritesheets[1].loadFromFile("images/pantalla.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[1].setMagFilter(GL_NEAREST);
	spritesheets[1].setMinFilter(GL_NEAREST);
	spritesheets[2].loadFromFile("images/level_1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[2].setMagFilter(GL_NEAREST);
	spritesheets[2].setMinFilter(GL_NEAREST);
	spritesheets[3].loadFromFile("images/level_2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[3].setMagFilter(GL_NEAREST);
	spritesheets[3].setMinFilter(GL_NEAREST);
	spritesheets[4].loadFromFile("images/fletxa.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[4].setMagFilter(GL_NEAREST);
	spritesheets[4].setMinFilter(GL_NEAREST);
	spritesheets[5].loadFromFile("images/instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[5].setMagFilter(GL_NEAREST);
	spritesheets[5].setMinFilter(GL_NEAREST);
	spritesheets[6].loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[6].setMagFilter(GL_NEAREST);
	spritesheets[6].setMinFilter(GL_NEAREST);
	spritesheets[7].loadFromFile("images/instruct.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[7].setMagFilter(GL_NEAREST);
	spritesheets[7].setMinFilter(GL_NEAREST);
	spritesheets[8].loadFromFile("images/credit.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheets[8].setMagFilter(GL_NEAREST);
	spritesheets[8].setMinFilter(GL_NEAREST);

	elements[0] = Sprite::createSprite(glm::ivec2(152, 8), glm::vec2(1.f, 1.f), &spritesheets[0], &texProgram);
	elements[0]->setNumberAnimations(1);
	elements[0]->setAnimationSpeed(0, 1);
	elements[0]->addKeyframe(0, glm::vec2(0.f, 0.f));
	elements[0]->changeAnimation(0);
	elements[0]->setPosition(glm::vec2(float(SCREEN_X), float(SCREEN_Y)));
	elements[1] = Sprite::createSprite(glm::ivec2(256, 240), glm::vec2(1.f, 1.f), &spritesheets[1], &texProgram);
	elements[1]->setNumberAnimations(1);
	elements[1]->setAnimationSpeed(0, 1);
	elements[1]->addKeyframe(0, glm::vec2(0.f, 0.f));
	elements[1]->changeAnimation(0);
	elements[1]->setPosition(glm::vec2(float(SCREEN_X), float(SCREEN_Y)));
	elements[2] = Sprite::createSprite(glm::ivec2(56, 8), glm::vec2(1.f, 1.f), &spritesheets[2], &texProgram);
	elements[2]->setNumberAnimations(1);
	elements[2]->setAnimationSpeed(0, 1);
	elements[2]->addKeyframe(0, glm::vec2(0.f, 0.f));
	elements[2]->changeAnimation(0);
	elements[2]->setPosition(glm::vec2(float(SCREEN_X)+100, float(SCREEN_Y)+140));
	elements[3] = Sprite::createSprite(glm::ivec2(56, 8), glm::vec2(1.f, 1.f), &spritesheets[3], &texProgram);
	elements[3]->setNumberAnimations(1);
	elements[3]->setAnimationSpeed(0, 1);
	elements[3]->addKeyframe(0, glm::vec2(0.f, 0.f));
	elements[3]->changeAnimation(0);
	elements[3]->setPosition(glm::vec2(float(SCREEN_X)+100, float(SCREEN_Y)+160));
	elements[4] = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(1.f, 1.f), &spritesheets[4], &texProgram);
	elements[4]->setNumberAnimations(1);
	elements[4]->setAnimationSpeed(0, 1);
	elements[4]->addKeyframe(0, glm::vec2(0.f, 0.f));
	elements[4]->changeAnimation(0);
	elements[4]->setPosition(glm::vec2(float(SCREEN_X) + 80, float(SCREEN_Y)+140));
	elements[5] = Sprite::createSprite(glm::ivec2(96, 8), glm::vec2(1.f, 1.f), &spritesheets[5], &texProgram);
	elements[5]->setNumberAnimations(1);
	elements[5]->setAnimationSpeed(0, 1);
	elements[5]->addKeyframe(0, glm::vec2(0.f, 0.f));
	elements[5]->changeAnimation(0);
	elements[5]->setPosition(glm::vec2(float(SCREEN_X)+100, float(SCREEN_Y)+180));
	elements[6] = Sprite::createSprite(glm::ivec2(56, 8), glm::vec2(1.f, 1.f), &spritesheets[6], &texProgram);
	elements[6]->setNumberAnimations(1);
	elements[6]->setAnimationSpeed(0, 1);
	elements[6]->addKeyframe(0, glm::vec2(0.f, 0.f));
	elements[6]->changeAnimation(0);
	elements[6]->setPosition(glm::vec2(float(SCREEN_X)+100, float(SCREEN_Y)+200));
	elements[7] = Sprite::createSprite(glm::ivec2(256, 240), glm::vec2(1.f, 1.f), &spritesheets[7], &texProgram);
	elements[7]->setNumberAnimations(1);
	elements[7]->setAnimationSpeed(0, 1);
	elements[7]->addKeyframe(0, glm::vec2(0.f, 0.f));
	elements[7]->changeAnimation(0);
	elements[7]->setPosition(glm::vec2(float(SCREEN_X), float(SCREEN_Y)));
	elements[8] = Sprite::createSprite(glm::ivec2(256, 240), glm::vec2(1.f, 1.f), &spritesheets[8], &texProgram);
	elements[8]->setNumberAnimations(1);
	elements[8]->setAnimationSpeed(0, 1);
	elements[8]->addKeyframe(0, glm::vec2(0.f, 0.f));
	elements[8]->changeAnimation(0);
	elements[8]->setPosition(glm::vec2(float(SCREEN_X), float(SCREEN_Y)));
}
void MenuUI::updateshowOptions() {
	if (scenemode == -1) {
		if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			preselectup = true;
		}
		else if (preselectup) {
			preselectup = false;
			if (mode > 0) {
				mode--;
				if (mode == 0)elements[4]->setPosition(glm::vec2(float(SCREEN_X) + 80, float(SCREEN_Y) + 140));
				if (mode == 1)elements[4]->setPosition(glm::vec2(float(SCREEN_X) + 80, float(SCREEN_Y) + 160));
				if (mode == 2)elements[4]->setPosition(glm::vec2(float(SCREEN_X) + 80, float(SCREEN_Y) + 180));
				if (mode == 3)elements[4]->setPosition(glm::vec2(float(SCREEN_X) + 80, float(SCREEN_Y) + 200));
			}
		}

		if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			preselectdown = true;
		}
		else if (preselectdown) {
			preselectdown = false;
			if (mode < 3) {
				mode++;
				if (mode == 0)elements[4]->setPosition(glm::vec2(float(SCREEN_X) + 80, float(SCREEN_Y) + 140));
				if (mode == 1)elements[4]->setPosition(glm::vec2(float(SCREEN_X) + 80, float(SCREEN_Y) + 160));
				if (mode == 2)elements[4]->setPosition(glm::vec2(float(SCREEN_X) + 80, float(SCREEN_Y) + 180));
				if (mode == 3)elements[4]->setPosition(glm::vec2(float(SCREEN_X) + 80, float(SCREEN_Y) + 200));
			}
		}
	}


	if (Game::instance().getKey(13) && scenemode == -1) {
		preinfo1 = true;
	}
	else if (preinfo1) {
		preinfo1 = false;
		scenemode = mode;
		if (scenemode == 0 || scenemode == 1) {
			Game::instance().setMenuMode(2);
			Game::instance().stopGame(2);
		} 
	}
		
	if (Game::instance().getKey(13) && scenemode != -1) {
		preinfo2 = true;
	}
	else if (preinfo2) {
		preinfo2 = false;
		scenemode = -1;
	}
}
int MenuUI::getMode() {
	return scenemode;
}

void MenuUI::clear() {
	mode = 0;
	scenemode = -1;
	preselectup = false;
	preselectdown = false;
	preinfo1 = false;
	preinfo2 = false;
}

void MenuUI::finish() {

}