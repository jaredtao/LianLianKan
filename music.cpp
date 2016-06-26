#include "music.h"
#include "audio.h"
Music::Music(QObject *parent): QObject(parent)
{
	Audio::init();
}
Music::~Music()
{
	Audio::quit();

}
void Music::playBGM()
{
	Audio::playBGM("Sounds/backgrand.mp3");
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
	Audio::playBGM("Sounds/pair.wav");
}
void Music::playSelected()
{
	Audio::playBGM("Sounds/select.mp3");
}
void Music::playSelected2()
{
	Audio::playBGM("Sounds/select.wav");
}
