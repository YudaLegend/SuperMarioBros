#include "MenuUI.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <algorithm>

#define SCREEN_X 16
#define SCREEN_Y 16

MenuUI::MenuUI()
{

}

MenuUI::~MenuUI()
{

}

void Scene::init()
{
	initShaders();
	projection = glm::ortho(16.f, float(SCREEN_WIDTH) + 16.f, float(SCREEN_HEIGHT) + 16.f, 16.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
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
