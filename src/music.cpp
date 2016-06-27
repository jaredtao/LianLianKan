#include "music.h"
#include "audio.h"
Music::Music(QObject *parent): QObject(parent)
{
	mute = false;
	Audio::init();
}
Music::~Music()
{
	Audio::quit();

}
void Music::playBGM()
{
	static bool once = false;
	if (!once) {
		Audio::playBGM("Sounds/backgrand.mp3");
		once = true;
	}
}
void Music::stopBGM()
{
	Audio::stopBGM();
}
void Music::setBGMVolume(float volume)
{
	Audio::setBGMVolume(volume);
}

void Music::playLink()
{
	if(!mute)
		Audio::playBGM("Sounds/pair.wav");
}
void Music::playSelected()
{
	if(!mute)
		Audio::playBGM("Sounds/select.mp3");
}
void Music::playSelected2()
{
	if (!mute)
		Audio::playBGM("Sounds/select.wav");
}
void Music::setMute(bool b)
{
	mute = b;
}
