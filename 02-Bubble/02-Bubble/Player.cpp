#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"

void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	sm = new SmallMario();
	sm->init(tileMapPos, shaderProgram);
	bm = new BigMario();
	bm->init(tileMapPos, shaderProgram);
	mode = false;
}

void Player::update(int deltaTime, float scroll)
{
	if (Game::instance().getKey(103) && mode) {
		mode = true;
	}
	if (mode)sm->update(deltaTime, scroll);
	else bm->update(deltaTime, scroll);

}

void Player::render()
{
	if (mode) {
		sm->render();
	}
	else {
		bm->render();
	}
	
}


void Player::setStartMode() {
	if (mode) {
		sm->setStartMode();
	}
	else {
		bm->setStartMode();
	}
	
}

void Player::setJump() {
	if (mode) {
		sm->setJump();
	}
	else {
		bm->setJump();
	}

}


void Player::setTileMap(TileMap* tileMap)
{
	if (mode) {
		sm->setTileMap(tileMap);
	}
	else {
		bm->setTileMap(tileMap);
	}
	
}

void Player::setPosition(const glm::vec2& pos)
{
	if (mode) {
		sm->setPosition(pos);
	}
	else {
		bm->setPosition(pos);
	}
	
}

bool Player::collisionInt() {
	if (mode) {
		return sm->collisionInt();
	}
	else {
		return bm->collisionInt();
	}
	
}

glm::ivec2 Player::posInt() {
	if (mode) {
		return sm->posInt();
	}
	else {
		return bm->posInt();
	}
	
}


glm::ivec2 Player::getPosition() {
	if (mode) {
		return sm->getPosition();
	}
	else {
		return bm->getPosition();
	}
}


void Player::setSmall() {
	mode = true;
}