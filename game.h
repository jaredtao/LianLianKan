#ifndef GAME_H
#define GAME_H
#include <QString>
#include <QVector>
class Game
{
public:
	Game();
	~Game();
public:
	enum GameState{
		READY,		//׼��
		PLAYING,	//��Ϸ��
		PAUSE,		//��ͣ
		WIN,		//ʤ��
		LOSE		//ʧ��
	};
	enum GameDifficulty {
		EASY,		//��
		MIDDLE,		//�е�
		HARD		//��ʦ
	};
	static const int MAXW = 100;
	static const int MAXH = 100;
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
