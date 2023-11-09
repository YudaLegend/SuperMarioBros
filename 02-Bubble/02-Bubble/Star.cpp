#include "Star.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

void Star::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	spritesheet.resize(1);
	sprite.resize(1);
	spritesheet[0].loadFromFile("images/Star.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite[0]->Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25f, 1.f), &spritesheet[0], &shaderProgram);
	sprite[0]->setNumberAnimations(1);

	sprite[0]->setAnimationSpeed(0, 8);
	sprite[0]->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite[0]->addKeyframe(0, glm::vec2(0.25f, 0.f));
	sprite[0]->addKeyframe(0, glm::vec2(0.5f, 0.f));
	sprite[0]->addKeyframe(0, glm::vec2(0.75f, 0.f));

}

void Star::update(int deltaTime, float scroll) {
	for (int i = 0; i < sprite.size(); i++) {
		sprite[i]->update(deltaTime, scroll);
	}
}
void Star::render() {
	for (int i = 0; i < sprite.size(); i++) {
		sprite[i]->render();
	}
}