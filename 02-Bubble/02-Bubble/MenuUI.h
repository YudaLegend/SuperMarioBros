#ifndef _MENUUI_INCLUDE
#define _MENUUI_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Sprite.h"
class MenuUI
{
private:
	void initShaders();
	ShaderProgram texProgram;
	ShaderProgram* shaderProgram;
	float currentTime;
	glm::mat4 projection;
	float scroll = 0;

	vector <Texture> spritesheets;
	vector <Sprite*> elements;

	int scenemode;
	int mode;
	bool preselectup;
	bool preselectdown;

	bool preinfo1;
	bool preinfo2;
public:
	MenuUI();
	~MenuUI();
	void init();
	void update(int deltaTime);
	void render();
	void reshape(int w, int h);

	void initshowOptions();
	void updateshowOptions();

	int getMode();

	void clear();
};

#endif