#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <typeinfo>
#include <fstream>
#include <sstream>


#define SCREEN_X 16
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25


Scene::Scene()
{
	map = NULL;
	player = NULL;
	mapBackground = NULL;
	enemies.clear();

}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (mapBackground != NULL)
		delete mapBackground;
	if (enemies.size() != 0)
		enemies.clear();

}


void Scene::initMap() {
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	map->setScene(this);

	mapBackground = BackgroundMap::createBackgroundMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

}

void Scene::reshape(int w, int h) {
	float scale = h / 480.f;
	float offset = (w - 8 * 16 * scale) / 2;

	projection = glm::ortho(16.f, w - offset, 240.f+16.f, 16.f);
	projection = glm::scale(projection, glm::vec3(scale));
}

void Scene::init()
{
	initShaders();
	
	initMap();
	
	this->fileName = "levels/level01.txt";

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	//player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setPosition(glm::vec2(10, 50));

	player->setTileMap(map);

	initEnemies();
	
	projection = glm::ortho(16.f, float(SCREEN_WIDTH)+16.f, float(SCREEN_HEIGHT)+16.f, 16.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	player->update(deltaTime);
	enemies[0]->update(deltaTime);

	glm::ivec2 playerpos = player->getPosition();
	scroll = -playerpos.x + 2.f;

}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(scroll, 0.f, 0.f)) * glm::mat4(1.0f);

	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	
	mapBackground->render();
	map->render();
	enemies[0]->render();
	player->render();
	
}

bool Scene::initEnemies() {
	ifstream fin;
	string line;
	stringstream sstream;
	fin.open(fileName.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	while (line.compare(0, 3, "END") != 0) {
		bool isSkeleton = line.compare(0, 11, "MUSHMONSTER") == 0;

		if (isSkeleton) {
			int n_enemies;
			getline(fin, line);
			sstream.str(line);
			sstream >> n_enemies;
			for (int i = 0; i < n_enemies; ++i) {
				stringstream sstream;
				int x_pos = 0;
				int y_pos = 0;
				char orientation;
				getline(fin, line);
				sstream.str(line);
				sstream >> x_pos >> y_pos >> orientation;
				
				if (isSkeleton) {
					MushMonster* mushMons = new MushMonster();
					mushMons->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
					mushMons->setPosition(glm::vec2(x_pos * map->getTileSize(), y_pos * map->getTileSize()));
					mushMons->setOrientation(orientation);
					mushMons->setSize(glm::vec2(16, 16));
					mushMons->setCollisionMap(map);
					enemies.push_back(mushMons);
				}
			}
		}
		getline(fin, line);
	}
	fin.close();
	return true;
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



