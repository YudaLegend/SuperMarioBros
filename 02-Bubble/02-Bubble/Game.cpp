#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <iostream>


void Game::init()
{
	prelevel1 = false;
	prelevel2 = false;
	secToStop = 0;
	deltTime = 0;
	stopping = false;
	bPlay = true;
	life = 3;
	world = 1;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	menumode = 1;
	scene = new Scene();
	scene->init();
	menu = new MenuUI();
	menu->init();
	oscenes = new OtherScenes();
	oscenes->init();
}

void Game::stopGame(int sec) {
	secToStop = sec;
	deltTime = 0;
	stopping = true;
}

void Game::reshape(int w, int h) {
	if (menumode == 1) {
		menu->reshape(w, h);
	}
	else if(menumode == 0){
		scene->reshape(w, h);
	}
	else if (menumode == 2) {
		oscenes->reshape(w, h);
	}

}

bool Game::update(int deltaTime)
{
	fastChangeLevel();
	if (stopping) {
		deltTime += deltaTime;
		if (deltTime >= 1000) {
			deltTime -= 1000;
			secToStop--;
			if (secToStop == 0) {
				stopping = false;
				deltTime = 0;
			}
		}
	}
	else {
		//menumode = menu->getMode() != 0 && menu->getMode() != 1;
		if (menumode == 1 ) {
			menu->update(deltaTime);
		}
		else if (menumode == 0){
			scene->update(deltaTime);
		}
		else if (menumode == 2) {
			
			if (life == 0) {
				oscenes->setPausaMode(6);
				menu->clear();
				menumode = 1;
				life = 3;
			}
			else if (life == 3 && world == 1) {
				oscenes->setPausaMode(0);
				scene->init();
				menumode = 0;
			}
			else if (life == 2 && world == 1) {
				oscenes->setPausaMode(1);
				scene->init();
				menumode = 0;
			}
			else if (life == 1 && world == 2) {
				oscenes->setPausaMode(2);
				scene->init();
				menumode = 0;
			}
			else if (life == 3 && world == 2) {
				oscenes->setPausaMode(3);
				scene->init();
				menumode = 0;
			}
			else if (life == 2 && world == 2) {
				oscenes->setPausaMode(4);
				scene->init();
				menumode = 0;
			}
			else if (life == 1 && world == 1) {
				oscenes->setPausaMode(5);
				scene->init();
				menumode = 0;
			}
			oscenes->update(deltaTime);
		}
	}
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (menumode == 1) {
		menu->render();
	}
	else if (menumode == 0){
		scene->render();
	}
	else if (menumode == 2) {
		oscenes->render();
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


void Game::setMenuMode(int i) {
	menumode = i;
}

void Game::die(int s, int c, int w, int t) {
	life--;
	if (life == 0) {
		oscenes->setScore(s);
		oscenes->setCoins(c);
		oscenes->setWorld(w);
		oscenes->setTime(t);
	}
	menumode = 2;
}

void Game::lifeup() {
	life++;
}

void Game::timeup(int s, int c, int w) {
	life--;
	oscenes->setScore(s);
	oscenes->setCoins(c);
	oscenes->setWorld(w);
	oscenes->setPausaMode(7);
	setMenuMode(2);
	stopGame(2);
}

void Game::fastChangeLevel() {
	if (Game::instance().getKey(49) && !prelevel1) {
		prelevel1 = true;
	}
	else if (prelevel1) {
		prelevel1 = false;
		life = 3;
		world = 1;
		menumode = 2;
		scene->clear();
		scene->init();
		stopGame(2);
	}

	if (Game::instance().getKey(50) && !prelevel2) {
		prelevel2 = true;
	}
	else if (prelevel2) {
		prelevel2 = false;
	}
}