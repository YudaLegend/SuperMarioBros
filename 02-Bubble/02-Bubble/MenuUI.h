#ifndef _MENUUI_INCLUDE
#define _MUNUUI_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"

class MenuUI
{
private:
	void initShaders();
	ShaderProgram texProgram;
	ShaderProgram* shaderProgram;
	float currentTime;
	glm::mat4 projection;
	float scroll = 0;
public:
	MenuUI();
	~MenuUI();
	void init();
	void update(int deltaTime);
	void render();
	void reshape(int w, int h);

};

#endif