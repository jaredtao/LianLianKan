#include "game.h"
#include <time.h>
class GamePrivate {
public:
	void init()
	{
		state = Game::READY;
		difficulty = Game::EASY;
		level = 1;
		score = 0;
		tip = 3;
		w = 6;
		h = 6;
	}
	Game::GameState state;
	Game::GameDifficulty difficulty;
	int level;
	int score;
	int tip;
	int w;
	int h;
};

Game::Game(QObject *parent): QObject(parent), m_dptr(new GamePrivate)
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
{
	delete m_dptr;
}
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


enum Game::GameState Game::state () const
{
	return m_dptr->state;
}
void Game::setState (GameState value)
{
	if ( m_dptr->state != value) {
		m_dptr->state = value;
		emit stateChanged();
		emit paramsChanged();
	}
}
enum Game::GameDifficulty Game::difficulty () const
{
	return m_dptr->difficulty;
}
void Game::setDifficulty (GameDifficulty value)
{
	if ( m_dptr->difficulty != value) {
		m_dptr->difficulty = value;
		emit difficultyChanged();
		emit paramsChanged();
	}
}
int Game::level () const
{
	return m_dptr->level;
}
void Game::setLevel (int value)
{
	if ( m_dptr->level != value) {
		m_dptr->level = value;
		emit levelChanged();
		emit paramsChanged();
	}
}
int Game::score () const
{
	return m_dptr->score;
}
void Game::setScore (int value)
{
	if ( m_dptr->score != value) {
		m_dptr->score = value;
		emit scoreChanged();
		emit paramsChanged();
	}
}
int Game::tip () const
{
	return m_dptr->tip;
}
void Game::setTip (int value)
{
	if ( m_dptr->tip != value) {
		m_dptr->tip = value;
		emit tipChanged();
		emit paramsChanged();
	}
}
int Game::w () const
{
	return m_dptr->w;
}
void Game::setW (int value)
{
	if ( m_dptr->w != value) {
		m_dptr->w = value;
		emit wChanged();
		emit paramsChanged();
	}
}
int Game::h () const
{
	return m_dptr->h;
}
void Game::setH (int value)
{
	if ( m_dptr->h != value) {
		m_dptr->h = value;
		emit hChanged();
		emit paramsChanged();
	}
}

