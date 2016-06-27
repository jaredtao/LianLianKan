#ifndef GAME_H
#define GAME_H
#include <QPoint>
#include <QObject>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QQmlListProperty>
#include "tile.h"
class GamePrivate;
class Game : public QObject
{
	Q_OBJECT
	Q_ENUMS(GameState)
	Q_ENUMS(GameDifficulty)

	Q_PROPERTY(GameState state READ state WRITE setState NOTIFY stateChanged)
	Q_PROPERTY(GameDifficulty difficulty READ difficulty WRITE setDifficulty NOTIFY difficultyChanged)
	Q_PROPERTY(int level READ level WRITE setLevel NOTIFY levelChanged)
	Q_PROPERTY(int score READ score WRITE setScore NOTIFY scoreChanged)
	Q_PROPERTY(int tip READ tip WRITE setTip NOTIFY tipChanged)
	Q_PROPERTY(int w READ w WRITE setW NOTIFY wChanged)
	Q_PROPERTY(int h READ h WRITE setH NOTIFY hChanged)
	Q_PROPERTY(QQmlListProperty<Tile> tiles READ tiles CONSTANT)
	Q_PROPERTY(int gametime READ gametime WRITE setGametime NOTIFY gametimeChanged)
public:
	Game(QObject * parent = NULL);
	~Game();

	static const int MAXW = 100;
	static const int MAXH = 100;

	enum GameState{
		READY = 0,		//×Œ±ž
		PLAYING,	//ÓÎÏ·ÖÐ
		PAUSE,		//ÔÝÍ£
		WIN,		//Ê€Àû
		LOSE		//Ê§°Ü
	};

	enum GameDifficulty {
		EASY = 0,		//Œòµ¥
		MIDDLE,		//ÖÐµÈ
		HARD		//ŽóÊŠ
	};

public:
	Q_INVOKABLE bool startGame();
	Q_INVOKABLE bool reStart();
	Q_INVOKABLE void pauseGame(bool);


	Q_INVOKABLE int flip(int index);
	Q_INVOKABLE bool getTip();

	enum GameState state() const;
	void setState(GameState value);
	enum GameDifficulty difficulty() const;
	void setDifficulty(GameDifficulty value);
	int level() const;
	void setLevel(int value);
	int score() const;
	void setScore(int value);
	int tip() const;
	void setTip(int value);
	int w() const;
	void setW(int value);
	int h() const;
	void setH(int value);

	int gametime() const;
	void setGametime(int value);

	QQmlListProperty<Tile> tiles();

	Q_INVOKABLE void upParams()
	{
		emit paramsChanged();
	}
signals:
	void stateChanged();
	void difficultyChanged();
	void levelChanged();
	void scoreChanged();
	void tipChanged();
	void wChanged();
	void hChanged();
	void gametimeChanged();
	void paramsChanged();
public slots:
	void timeout();
private:
	Tile *tile(int index) const;

	bool tip(int &startX, int &startY, int &endX, int &endY);
	bool isWin();

	bool link(int startX, int startY, int endX, int endY);

	void random();
	bool needRandom();

	int map[MAXW][MAXH];		//±£ŽæµØÍŒ,  0±íÊŸ¿Õ°×£¬ Êý×Ö1-25±íÊŸÍŒÆ¬
	QList<QPoint> pathPoint;
	QList<Tile *> m_tiles;
	QPoint start, end;
	int clicked;
	//ÄÜ²»ÄÜÁ¬
	bool canLink(int startX, int startY, int endX, int endY);

	//ÄÜË®Æœ»òÕßŽ¹Ö± Ö±Á¬
	bool canVerOrHorLink(int startX, int startY, int endX, int endY);
	bool canVerticalLink(int X, int startY, int endY);
	bool canHorizontalLink(int Y, int startX, int endX);

	//ÄÜÒ»žö¹ÕÍäÁ¬
	bool canOneConnerLink(int startX, int startY, int endX, int endY);
	//ÄÜÁœžö¹ÕÍäÁ¬
	bool canDoubleConnerLink(int startX, int startY, int endX, int endY);
	GamePrivate *m_dptr;
};

#endif // GAME_H
