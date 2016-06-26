#ifndef GAME_H
#define GAME_H
#include <QObject>
#include <QString>
#include <QVector>
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
public:
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
	Q_DECLARE_FLAGS(GameStates, GameState)
	Q_FLAG(GameStates)

	enum GameDifficulty {
		EASY = 0,		//Œòµ¥
		MIDDLE,		//ÖÐµÈ
		HARD		//ŽóÊŠ
	};

	Q_DECLARE_FLAGS(GameDifficultys, GameDifficulty)
	Q_FLAG(GameDifficultys)


	Q_INVOKABLE bool startGame();
	Q_INVOKABLE bool link(int startX, int startY, int endX, int endY);
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
	GameState m_state;			//×ŽÌ¬
	GameDifficulty m_diffculty;	//ÓÎÏ·ÄÑ¶È
	int m_level;				//¹Ø¿š
	int m_score;				//µÃ·Ö
	int m_tip;					//ÌáÊŸ
	int m_w, m_h;			//mapŽóÐ¡
	int map[MAXW][MAXH];		//±£ŽæµØÍŒ,  0±íÊŸ¿Õ°×£¬ Êý×Ö1-25±íÊŸÍŒÆ¬
	bool canLink(int startX, int startY, int endX, int endY, int step, int dir);
	GamePrivate *m_dptr;
};

#endif // GAME_H
