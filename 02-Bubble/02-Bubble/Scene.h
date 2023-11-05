#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "BigMario.h"
#include "Player.h"
#include "BackgroundMap.h"
#include "MushMonster.h"
#include "Turtle.h"
#include "InterrogantBlock.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void reshape(int w, int h);
	void initMap();
	bool initEnemies();
	bool initIntBlocks();
	
	bool MarioUpEnemy(Player& p, Enemy& e);

private:
	void initShaders();

private:
	string fileName;
	TileMap* map;
	BackgroundMap* mapBackground;
	Player* player;
	ShaderProgram texProgram;
	ShaderProgram* shaderProgram;
	float currentTime;
	glm::mat4 projection;

	vector<Enemy*> enemies;

	vector<InterrogantBlock*> int_blocks;
	vector<glm::ivec2> pos_blocks = {glm::vec2(16,9), glm::vec2(21,9), glm::vec2(22,5), glm::vec2(23,9),glm::vec2(78,9), glm::vec2(94,5),glm::vec2(106,9),glm::vec2(109,5),glm::vec2(109,9),glm::vec2(112,9),glm::vec2(129,5),glm::vec2(130,5),glm::vec2(170,9) };


	float scroll = 0;


};


#endif // _SCENE_INCLUDE

