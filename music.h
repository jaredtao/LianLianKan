#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>
class Music: public QObject
{
	Q_OBJECT
public:
	Music(QObject *parent = 0);
	~Music();
	Q_INVOKABLE void playBGM();
	Q_INVOKABLE void stopBGM();
	Q_INVOKABLE void setBGMVolume(float volume);

	Q_INVOKABLE void playLink();
	Q_INVOKABLE void playSelected();
	Q_INVOKABLE void playSelected2();

};

#endif // MUSIC_H
