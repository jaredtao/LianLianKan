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
		READY,		//准备
		PLAYING,	//游戏中
		PAUSE		//暂停
	};
	enum GameResult {
		WIN,		//胜利
		LOSE		//失败
	};
	enum GameDifficulty {
		EASY,		//简单
		MIDDLE,		//中等
		HARD		//大师
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
