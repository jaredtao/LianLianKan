#ifndef GAME_H
#define GAME_H
#include <QPoint>
#include <QObject>
#include <QString>
#include <QVector>
#include <QQmlListProperty>
#include "tile.h"
class GamePrivate;
class Game : public QObject
{
	Q_OBJECT

	Q_PROPERTY(GameState state READ state WRITE setState NOTIFY stateChanged)
	Q_PROPERTY(GameDifficulty difficulty READ difficulty WRITE setDifficulty NOTIFY difficultyChanged)
	Q_PROPERTY(int level READ level WRITE setLevel NOTIFY levelChanged)
	Q_PROPERTY(int score READ score WRITE setScore NOTIFY scoreChanged)
	Q_PROPERTY(int tip READ tip WRITE setTip NOTIFY tipChanged)
	Q_PROPERTY(int w READ w WRITE setW NOTIFY wChanged)
	Q_PROPERTY(int h READ h WRITE setH NOTIFY hChanged)
	Q_PROPERTY(QQmlListProperty<Tile> tiles READ tiles CONSTANT)
public:
	Game(QObject * parent = NULL);
	~Game();

	static const int MAXW = 100;
	static const int MAXH = 100;

	enum GameState{
		READY = 0,		//准备
		PLAYING,	//游戏中
		PAUSE,		//暂停
		WIN,		//胜利
		LOSE		//失败
	};
	Q_DECLARE_FLAGS(GameStates, GameState)
	Q_FLAG(GameStates)

	enum GameDifficulty {
		EASY = 0,		//简单
		MIDDLE,		//中等
		HARD		//大师
	};
	Q_DECLARE_FLAGS(GameDifficultys, GameDifficulty)
	Q_FLAG(GameDifficultys)
public:
	Q_INVOKABLE bool startGame();
	Q_INVOKABLE bool reStart();
	Q_INVOKABLE void pauseGame(bool);

	Q_INVOKABLE bool flip(int index);


	bool link(int startX, int startY, int endX, int endY);
	Q_INVOKABLE bool tip(int &startX, int &startY, int &endX, int &endY);
	Q_INVOKABLE bool isWin();


	Q_INVOKABLE void random();
	Q_INVOKABLE bool needRandom();


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
	void paramsChanged();

private:
	GameState m_state;			//状态
	GameDifficulty m_diffculty;	//游戏难度
	int m_scorePerLink;			//每连一个的得分
	int m_level;				//关卡
	int m_score;				//得分
	int m_tip;					//提示
	int m_w, m_h;			//map大小
	int map[MAXW][MAXH];		//保存地图,  0表示空白， 数字1-25表示图片
	QList<QPoint> pathPoint;
	QList<Tile *> m_tiles;
	//能不能连
	bool canLink(int startX, int startY, int endX, int endY);

	//能水平或者垂直 直连
	bool canVerOrHorLink(int startX, int startY, int endX, int endY);
	bool canVerticalLink(int X, int startY, int endY);
	bool canHorizontalLink(int Y, int startX, int endX);

	//能一个拐弯连
	bool canOneConnerLink(int startX, int startY, int endX, int endY);
	//能两个拐弯连
	bool canDoubleConnerLink(int startX, int startY, int endX, int endY);
	GamePrivate *m_dptr;
};

#endif // GAME_H
