#ifndef AUDIO_H
#define AUDIO_H
#include <QString>
#ifdef AUDIO_SUPPORT
class Audio
{
public:
	static void init();
	static void quit();

	static void play(const QString &filename, bool superpose = true);
	static void stop();

	static void playBGM(const QString &filename);
	static void setBGMVolume(float volume);
	static void stopBGM();

	static QString getVersion();
};
#endif //AUDIO_SUPPORT
#endif // AUDIO_H
