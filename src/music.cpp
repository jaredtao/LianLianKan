#include "music.h"
#include "audio.h"
Music::Music(QObject *parent): QObject(parent)
{
	mute = false;
#ifdef AUDIO_SUPPORT
	Audio::init();
#endif
}
Music::~Music()
{
#ifdef AUDIO_SUPPORT
	Audio::quit();
#endif

}
void Music::playBGM()
{
	static bool once = false;
	if (!once) {
#ifdef AUDIO_SUPPORT
		Audio::playBGM("Sounds/backgrand.mp3");
#endif
		once = true;
	}
}
void Music::stopBGM()
{
#ifdef AUDIO_SUPPORT
	Audio::stopBGM();
#endif
}
void Music::setBGMVolume(float volume)
{
	Q_UNUSED(volume)
#ifdef AUDIO_SUPPORT
	Audio::setBGMVolume(volume);
#endif
}

void Music::playLink()
{
#ifdef AUDIO_SUPPORT
	if(!mute)
		Audio::play("Sounds/pair.wav");
#endif
}
void Music::playSelected()
{
#ifdef AUDIO_SUPPORT
	if(!mute)
		Audio::play("Sounds/select.mp3");
#endif
}
void Music::playSelected2()
{
#ifdef AUDIO_SUPPORT
	if (!mute)
		Audio::play("Sounds/select.wav");
#endif
}
void Music::setMute(bool b)
{
	mute = b;
}
