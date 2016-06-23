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
		READY,		//准备
		PLAYING,	//游戏中
		PAUSE,		//暂停
		WIN,		//胜利
		LOSE		//失败
	};
	enum GameDifficulty {
		EASY,		//简单
		MIDDLE,		//中等
		HARD		//大师
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
	GameState m_state;			//状态
	GameDifficulty m_diffculty;	//游戏难度
	int m_level;				//关卡
	int m_score;				//得分
	int m_tip;					//提示
	int m_w, m_h;			//map大小
	int map[MAXW][MAXH];		//保存地图,  0表示空白， 数字1-25表示图片
	bool canLink(int startX, int startY, int endX, int endY, int step, int dir);
};

#endif // GAME_H
