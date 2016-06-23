#include "game.h"
#include <time.h>
Game::Game()
{
	m_state = READY;
	m_diffculty = EASY;
	m_level = 1;
	m_score = 0;
	m_tip = 3;
	m_w = 6;
	m_h = 6;
	memset(map, 0, sizeof(map));
	qsrand(time(0));
}
Game::~Game()
{}
bool Game::startGame()
{
	if(m_state == PLAYING)
		return false;
	m_state = PLAYING;
	int index = 1;
	int ref = 0;

	for (int i = 0; i < m_w; i++) {
		for (int j = 0; j < m_h; j++) {
			map[i][j] = index;
			ref++;
			if(ref>=2) {
				ref = 0;
				++index;
				if(index > m_w * m_h)
					index = index % (m_w * m_h);
			}
		}
	}

	for (int i = 0 ; i < m_w; ++i) {
		for (int j = 0; j < m_h; ++j) {
			int x = qrand() % m_w;
			int y = qrand() % m_h;
			int t = map[i][j];
			map[i][j] = map[x][y];
			map[x][y] = t;
		}
	}

	return true;
}
bool Game::isWin()
{
	for (int i = 0; i < m_w; i++) {
		for (int j = 0; j < m_h; j++) {
			if (map[i][j] != 0)
				return false;
		}
	}
	m_state = WIN;
	return true;
}


bool Game::link(int startX, int startY, int endX, int endY)
{

}
bool Game::tip(int &startX, int &startY, int &endX, int &endY)
{

}

void Game::random()
{
	for (int i = 0 ; i < m_w; ++i) {
		for (int j = 0; j < m_h; ++j) {
			int x = qrand() % m_w;
			int y = qrand() % m_h;
			int t = map[i][j];
			map[i][j] = map[x][y];
			map[x][y] = t;
		}
	}
}
bool Game::needRandom()
{
	int ax, ay, bx, by;
	if(tip(ax, ay, bx, by)) {
		return false;
	}
	return true;
}

const int recX[] = {0, 0, 1, -1};
const int recY[] = {1, -1, 0, 0};
bool Game::canLink(int startX, int startY, int endX, int endY, int step, int dir)
{

}
