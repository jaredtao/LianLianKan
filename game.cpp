#include "game.h"
#include <time.h>
Game::Game()
{
	m_state = READY;
	m_diffculty = EASY;
	m_level = 1;
	m_score = 0;
	m_tip = 3;
	m_mapW = 6;
	m_mapH = 6;
	memset(map, 0, sizeof(map));
	memset(used, false, sizeof(used));
	qsrand(time(0));
}
Game::~Game()
{}
bool Game::startGame()
{
	if(m_state == PLAYING)
		return false;
	int index = 1;
	int ref = 0;
	for (int i = 0; i < m_mapW; i++) {
		for (int j = 0; j < m_mapH; j++) {
			map[i][j] = index;
			ref++;
			if (ref >= 2) {
				index++;
				ref = 0;
			}
		}
	}
	for (int i = 0; i < m_mapW; ++i) {
		for (int j = 0; j < m_mapH; ++j) {
			int x = qrand() % m_mapW;
			int y = qrand() & m_mapH;
			int t = map[x][y];
			map[x][y]= map[i][j];
			map[i][j]= t;
		}
	}

	return true;
}
void Game::reset()
{

}
