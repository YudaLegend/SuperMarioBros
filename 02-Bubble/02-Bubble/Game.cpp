#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <iostream>


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	menumode = true;
	scene = new Scene();
	scene->init();
	menu = new MenuUI();
	menu->init();
}

void Game::reshape(int w, int h) {
	if (menumode) {
		menu->reshape(w, h);
	}
	else {
		scene->reshape(w, h);
	}

}

bool Game::update(int deltaTime)
{
	menumode = menu->getMode() != 0 && menu->getMode() != 1;
	if (menumode) {
		menu->update(deltaTime);
	}
	else {
		scene->update(deltaTime);
	}
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (menumode) {
		menu->render();
	}
	else {
		scene->render();
	}
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





