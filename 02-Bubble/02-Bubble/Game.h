#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "MenuUI.h"
#include "OtherScenes.h"
#include "MediaPlayer.h"
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}

public:
	static Game& instance()
	{
		static Game G;

		return G;
	}

	void init();
	bool update(int deltaTime);
	void render();

	void reshape(int w, int h);

	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	void stopGame(int sec);

	void setMenuMode(int i);

	void die(int s, int c, int w, int t);
	void timeup(int s, int c, int w);
	void lifeup();

	void fastChangeLevel();

private:
	bool bPlay;                       // Continue to play game?
	Scene* scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	// we can have access at any time
	MenuUI* menu;
	MediaPlayer* mediaPlayer;
	OtherScenes* oscenes;
	int menumode;
	int secToStop;
	int deltTime;
	bool stopping;
	int life;
	int world;
	bool prelevel1;
	bool prelevel2;
};


#endif // _GAME_INCLUDE


