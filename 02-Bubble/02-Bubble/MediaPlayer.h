#ifndef _MEDIAPLAYER_INCLUDE
#define _MEDIAPLAYER_INCLUDE
#include <irrKlang.h>
#include <string>
using namespace std;
class MediaPlayer
{
private:
	MediaPlayer();
	MediaPlayer(MediaPlayer const&) = delete;
	void operator=(MediaPlayer const&) = delete;
	irrklang::ISoundEngine* soundEngine;
	irrklang::ISoundEngine* musicEngine;
	static MediaPlayer* mediaPlayer;

	irrklang::ISoundSource* level1Sound;
	irrklang::ISoundSource* level2Sound;

	irrklang::ISoundSource* lifeup;
	irrklang::ISoundSource* breakblock;

	irrklang::ISoundSource* coin;
	irrklang::ISoundSource* flag;
	irrklang::ISoundSource* gameover;
	irrklang::ISoundSource* smallJump;
	irrklang::ISoundSource* bigJump;
	irrklang::ISoundSource* kick;
	irrklang::ISoundSource* die;
	irrklang::ISoundSource* pipe;

	irrklang::ISoundSource* powerup;
	irrklang::ISoundSource* powerup_appears;
	irrklang::ISoundSource* win;
public:
	static MediaPlayer* getInstance();

	void levelSound(int level);

	void lifeupSound();
	void breakblockSound();
	void coinSound();
	void flagSound();
	void gameoverSound();
	void smallJumpSound();
	void bigJumpSound();
	void kickSound();
	void dieSound();
	void pipeSound();
	void powerupSound();
	void powerup_appearsSound();
	void winSound();
	void stopAll();
	void stopLevelMusic(int level);
};


#endif