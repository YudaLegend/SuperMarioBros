#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

//#include "Entity.h"
//#include "Sprite.h"
//#include "TileMap.h"
#include "SmallMario.h"
#include "BigMario.h"
// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player : public Entity
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float scroll);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	bool collisionInt();
	bool collisionBlock();

	glm::ivec2 posInt();

	glm::ivec2 getPosition();

	void setJump();
	void setStartMode(bool t);

	void setSmall();
	void bigMarioButton();

	void BigMarioNormal(bool st);
	void BigMarioMiddle();

	void starButton();

	void SmallMario();

	void BigMario();

	void ScoreAnimation(int i);

	void convertion(int i);
private:
	bool mariomode; //false = small, true = big
	bool premario;
	bool bJumping;
	bool direction;//false right true left
	bool starmode;
	bool prestar;
	int convertionTime;
	int acces;
	int accomulation;
	int height;
	bool firstJump;
	int speed;
	int scoreAnimationTimer;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	vector <Texture> spritesheet;
	vector <Sprite*> sprite;
	TileMap* map;

	float scroll = 0;
};


#endif // _PLAYER_INCLUDE

