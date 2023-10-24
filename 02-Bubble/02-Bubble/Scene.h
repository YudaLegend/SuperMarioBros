#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "BackgroundMap.h"
#include "MushMonster.h"

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

	float scroll;


};


#endif // _SCENE_INCLUDE

