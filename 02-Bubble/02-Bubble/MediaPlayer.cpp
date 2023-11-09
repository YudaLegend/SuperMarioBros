#include "MediaPlayer.h"
MediaPlayer* MediaPlayer::mediaPlayer;
MediaPlayer::MediaPlayer() {
	soundEngine = irrklang::createIrrKlangDevice();
	musicEngine = irrklang::createIrrKlangDevice();
	musicEngine->setSoundVolume(irrklang::ik_f32(0.4));

	level1Sound = musicEngine->addSoundSourceFromFile("sounds/01. Ground Theme.mp3");
	level2Sound = musicEngine->addSoundSourceFromFile("sounds/02. Underground Theme.mp3");

	lifeup = soundEngine->addSoundSourceFromFile("sounds/smb_1-up.wav");
	breakblock = soundEngine->addSoundSourceFromFile("sounds/smb_breakblock.wav");

	coin = soundEngine->addSoundSourceFromFile("sounds/smb_coin.wav");
	flag = soundEngine->addSoundSourceFromFile("sounds/smb_flagpole.wav");
	gameover = soundEngine->addSoundSourceFromFile("sounds/smb_gameover.wav");
	smallJump = soundEngine->addSoundSourceFromFile("sounds/smb_jump-small.wav");
	bigJump = soundEngine->addSoundSourceFromFile("sounds/smb_jump-super.wav");
	kick = soundEngine->addSoundSourceFromFile("sounds/smb_kick.wav");
	die = soundEngine->addSoundSourceFromFile("sounds/smb_mariodie.wav");
	pipe = soundEngine->addSoundSourceFromFile("sounds/smb_pipe.wav");

	powerup = soundEngine->addSoundSourceFromFile("sounds/smb_powerup.wav");
	powerup_appears = soundEngine->addSoundSourceFromFile("sounds/smb_powerup_appears.wav");
	win = soundEngine->addSoundSourceFromFile("sounds/smb_stage_clear.wav");
}
MediaPlayer* MediaPlayer::getInstance() {
	if (mediaPlayer == nullptr) {
		mediaPlayer = new MediaPlayer();
	}
	return mediaPlayer;
}

void MediaPlayer::levelSound(int level) {
	if (level == 1) {
		if(!musicEngine->isCurrentlyPlaying(level1Sound))
			musicEngine->play2D(level1Sound, true);
	}
	else if (level == 2) {
		if (!musicEngine->isCurrentlyPlaying(level2Sound))
			musicEngine->play2D(level2Sound, true);
	}
}

void MediaPlayer::lifeupSound() {
	soundEngine->play2D(lifeup);
}
void MediaPlayer::breakblockSound() {
	soundEngine->play2D(breakblock);
}
void MediaPlayer::coinSound() {
	soundEngine->play2D(coin);
}
void MediaPlayer::flagSound() {
	soundEngine->play2D(flag);
}
void MediaPlayer::gameoverSound() {
	soundEngine->play2D(gameover);
}
void MediaPlayer::smallJumpSound() {
	soundEngine->play2D(smallJump);
}
void MediaPlayer::bigJumpSound() {
	soundEngine->play2D(bigJump);
}
void MediaPlayer::kickSound() {
	soundEngine->play2D(kick);
}
void MediaPlayer::dieSound() {
	soundEngine->play2D(die);
}
void MediaPlayer::pipeSound() {
	soundEngine->play2D(pipe);
}
void MediaPlayer::powerupSound() {
	soundEngine->play2D(powerup);
}
void MediaPlayer::powerup_appearsSound() {
	soundEngine->play2D(powerup_appears);
}
void MediaPlayer::winSound() {
	soundEngine->play2D(win);
}
void MediaPlayer::stopAll() {
	musicEngine->stopAllSounds();
	soundEngine->stopAllSounds();
}
void MediaPlayer::stopLevelMusic(int level) {
	if (level == 1) {
		musicEngine->stopAllSoundsOfSoundSource(level1Sound);
	}
	else if (level == 2) {
		musicEngine->stopAllSoundsOfSoundSource(level2Sound);
	}
}