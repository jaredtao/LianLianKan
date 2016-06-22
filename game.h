#ifndef GAME_H
#define GAME_H
#include <QString>
#include "enum.h"

class Game
{
public:
	Game();
	~Game();
public:
	enum GameState{
		READY,		//׼��
		PLAYING,	//��Ϸ��
		PAUSE		//��ͣ
	};
	enum GameResult {
		WIN,		//ʤ��
		LOSE		//ʧ��
	};
	enum GameDifficulty {
		EASY,		//��
		MIDDLE,		//�е�
		HARD		//��ʦ
	};
public:
	bool startGame();
	void reset();
private:
	GameState m_state;
	GameResult m_result;
	GameDifficulty m_diffculty;
	int m_level;
	int m_score;
	int m_tip;
	int m_mapwidth, m_mapheight;
	QVector2D map;
};

#endif // GAME_H
