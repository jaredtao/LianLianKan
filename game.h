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
		READY = 0,		//׼��
		PLAYING,	//��Ϸ��
		PAUSE,		//��ͣ
		WIN,		//ʤ��
		LOSE		//ʧ��
	};
	Q_DECLARE_FLAGS(GameStates, GameState)
	Q_FLAG(GameStates)

	enum GameDifficulty {
		EASY = 0,		//��
		MIDDLE,		//�е�
		HARD		//��ʦ
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
	GameState m_state;			//״̬
	GameDifficulty m_diffculty;	//��Ϸ�Ѷ�
	int m_scorePerLink;			//ÿ��һ���ĵ÷�
	int m_level;				//�ؿ�
	int m_score;				//�÷�
	int m_tip;					//��ʾ
	int m_w, m_h;			//map��С
	int map[MAXW][MAXH];		//�����ͼ,  0��ʾ�հף� ����1-25��ʾͼƬ
	QList<QPoint> pathPoint;
	QList<Tile *> m_tiles;
	//�ܲ�����
	bool canLink(int startX, int startY, int endX, int endY);

	//��ˮƽ���ߴ�ֱ ֱ��
	bool canVerOrHorLink(int startX, int startY, int endX, int endY);
	bool canVerticalLink(int X, int startY, int endY);
	bool canHorizontalLink(int Y, int startX, int endX);

	//��һ��������
	bool canOneConnerLink(int startX, int startY, int endX, int endY);
	//������������
	bool canDoubleConnerLink(int startX, int startY, int endX, int endY);
	GamePrivate *m_dptr;
};

#endif // GAME_H
