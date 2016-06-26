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
	bool startGame();


	bool link(int startX, int startY, int endX, int endY);

	bool tip(int &startX, int &startY, int &endX, int &endY);

	bool isWin();

	void random();
	bool needRandom();


private:
	GameState m_state;			//״̬
	GameDifficulty m_diffculty;	//��Ϸ�Ѷ�
	int m_scorePerLink;			//ÿ��һ���ĵ÷�
	int m_level;				//�ؿ�
	int m_score;				//�÷�
	int m_tip;					//��ʾ
	int m_w, m_h;			//map��С
	int map[MAXW][MAXH];		//�����ͼ,  0��ʾ�հף� ����1-25��ʾͼƬ
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
};

#endif // GAME_H
