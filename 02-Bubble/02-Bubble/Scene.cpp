#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <algorithm>


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
	int_blocks.clear();
	jmoneys.clear();
	mush.clear();

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
	if (int_blocks.size() != 0)
		int_blocks.clear();
	if (jmoneys.size() != 0)
		jmoneys.clear();
	if (mush.size() != 0)
		mush.clear();

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


bool Scene::initIntBlocks() {
	
	for (int i = 0; i < pos_blocks.size(); ++i) {
		InterrogantBlock* block = new InterrogantBlock();
		block->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		block->setPosition(pos_blocks[i]*16);
		block->setSize(glm::vec2(16, 16));
		int_blocks.push_back(block);
	}

	return true;
}

bool Scene::initJmoneys() {

	for (int i = 0; i < pos_jmoneys.size(); ++i) {
		JumpingMoney* jcoins = new JumpingMoney();
		jcoins->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		jcoins->setPosition( (pos_jmoneys[i] * 16) + glm::ivec2(4,0) ) ;
		jcoins->setSize(glm::vec2(16, 16));
		jmoneys.push_back(jcoins);
	}

	return true;
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

	
	MushRoom* m = new MushRoom();
	m->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	m->setPosition(glm::ivec2(10,50));
	m->setSize(glm::vec2(16, 16));
	mush.push_back(m);


	initJmoneys();
	initIntBlocks();
	initEnemies();
	
	projection = glm::ortho(16.f, float(SCREEN_WIDTH)+16.f, float(SCREEN_HEIGHT)+16.f, 16.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	player->update(deltaTime,scroll);
	glm::ivec2 playerpos = player->getPosition();
	
	//Scroll la camara
	if (playerpos.x >= ( -scroll + 129.f) ) {
		scroll = (-playerpos.x + 128.f)+1;
	}

	player->update(deltaTime, scroll);

	//update bloques interrogantes
	for (unsigned int i = 0; i < int_blocks.size(); ++i) {
		int_blocks[i]->update(deltaTime, scroll);
	}
	
	//Jumping moneys
	for (unsigned int i = 0; i < jmoneys.size(); ++i) {
		jmoneys[i]->update(deltaTime, scroll);

		if (player->collisionInt() && jmoneys[i]->MarioDown(playerpos) ) {
			//moneda +1
			//player->setStartMode();
		}
		if (jmoneys[i]->needDelete()) {
			jmoneys.erase(std::remove(jmoneys.begin(), jmoneys.end(), jmoneys[i]), jmoneys.end());
		}
	}

	//Colision con los bloques interrogantes
	if (player->collisionInt()) {
		glm::ivec2 blockpos = player->posInt();
		for (unsigned int i = 0; i < int_blocks.size(); ++i) {
			if (! int_blocks[i] ->isUnlocked() ) {
				int_blocks[i]->unlock(blockpos);
			}	
		}	
	}
	
	// Para que los monstruos no se aparezcan cuando el mario este muy lejos
	for (unsigned int i = 0; i < enemies.size(); ++i) {
		glm::ivec2 enemypos = enemies[i]->getPosition();
		if (enemypos.x <= (-scroll + 320)) { //Aqui 272 son pixeles
			enemies[i]->update(deltaTime, scroll);

			if (enemies[i]->enemyKillMario(playerpos)) {
				player->setStartMode();
			}

			if (enemies[i]->MarioUp(playerpos, &playerpos.y)) {
				player->setJump();
			}
			if (enemies[i]->isDead()) {
				enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies[i]), enemies.end());
			}
		}
		
	}
	
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

	mush[0]->render();

	for (unsigned int i = 0; i < jmoneys.size(); ++i) {
		jmoneys[i]->render();
	}
	

	for (unsigned int i = 0; i < enemies.size(); ++i) {
		enemies[i]->render();
	}
	for (unsigned int i = 0; i < int_blocks.size(); ++i) {
		int_blocks[i]->render();
	}
	
	player->render();
	
}

bool Scene::MarioUpEnemy(Player& p, Enemy& e) {
	
	
	return false;

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
		bool isMush = line.compare(0, 11, "MUSHMONSTER") == 0;
		bool isTurtle = line.compare(0, 6, "TURTLE") == 0;

		if (isMush || isTurtle) {
			stringstream sstream;
			int n_enemies;
			getline(fin, line);
			sstream.str(line);
			sstream >> n_enemies;
			
			for (int i = 0; i < n_enemies; ++i) {
				stringstream sstream;
				float x_pos = 0;
				float y_pos = 0;
				char orientation;
				getline(fin, line);
				sstream.str(line);
				sstream >> x_pos >> y_pos >> orientation;
				
				if (isMush) {
					MushMonster* mushMons = new MushMonster();
					mushMons->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
					mushMons->setPosition(glm::vec2(x_pos * map->getTileSize(), y_pos * map->getTileSize()));
					mushMons->setOrientation(orientation);
					mushMons->setSize(glm::vec2(16, 16));
					mushMons->setCollisionMap(map);
					enemies.push_back(mushMons);
				}
				else if (isTurtle) {
					Turtle* turtle = new Turtle();
					turtle->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
					turtle->setPosition(glm::vec2(x_pos * map->getTileSize(), y_pos * map->getTileSize()));
					turtle->setOrientation(orientation);
					turtle->setSize(glm::vec2(16, 16));
					turtle->setCollisionMap(map);
					enemies.push_back(turtle);
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



