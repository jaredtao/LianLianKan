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
	m_scorePerLink = 20;
	memset(map, 0, sizeof(map));
	qsrand(time(0));
}
Game::~Game()
{
	delete m_dptr;
}
bool Game::startGame()
{
	if(state() == PLAYING)
		return false;
	setState(PLAYING);

	int index = 1;
	int ref = 0;
	//地图下标从1开始，0 的行和列空出来，方便之后计算的时候做边界检测
	for (int i = 1; i <= m_w; i++) {
		for (int j = 1; j <= m_h; j++) {
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

	for (int i = 1 ; i <= m_w; ++i) {
		for (int j = 1; j <= m_h; ++j) {
			int x = qrand() % m_w;
			int y = qrand() % m_h;
			int t = map[i][j];
			map[i][j] = map[x][y];
			map[x][y] = t;
		}
	}

	return true;
}
bool Game::reStart()
{
	setState(PLAYING);

	int index = 1;
	int ref = 0;
	//地图下标从1开始，0 的行和列空出来，方便之后计算的时候做边界检测
	for (int i = 1; i <= m_w; i++) {
		for (int j = 1; j <= m_h; j++) {
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

	for (int i = 1 ; i <= m_w; ++i) {
		for (int j = 1; j <= m_h; ++j) {
			int x = qrand() % m_w;
			int y = qrand() % m_h;
			int t = map[i][j];
			map[i][j] = map[x][y];
			map[x][y] = t;
		}
	}
	return true;
}
void Game::pauseGame(bool v)
{
	if (v)
		setState(PAUSE);
	else
		setState(PLAYING);
}
bool Game::isWin()
{
	for (int i = 1; i <= m_w; i++) {
		for (int j = 1; j <= m_h; j++) {
			if (map[i][j] != 0)
				return false;
		}
	}
	return true;
}


bool Game::link(int startX, int startY, int endX, int endY)
{
	if (canLink(startX, startY, endX, endY)) {
		map[startX][startY] = 0;
		map[endX][endY] = 0;
		m_score += m_scorePerLink;
		if (isWin()) {
			setState(WIN);
		}
		return true;
	}
	return false;
}
bool Game::tip(int &startX, int &startY, int &endX, int &endY)
{
	for (startX = 1; startX <= m_w; ++startX) {
		for (startY = 1; startY <= m_h; ++startY) {
			for (endX = 1; endX <= m_w; ++endX) {
				for (endY = 1; endY <= m_h; ++endY) {
					if ((map[startX][startY] == 0) || (map[endX][endY] == 0) ||
						(startX == endX && startY == endY) || map[startX][startY] != map[endX][endY]) {
						continue;
					}
					if (map[startX][startY] == map[endX][endY])
						return true;
				}
			}
		}
	}
	return false;
}
bool Game::flip(int index)
{

}
void Game::random()
{
	for (int i = 1 ; i <= m_w; ++i) {
		for (int j = 1; j <= m_h; ++j) {
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

bool Game::canLink(int startX, int startY, int endX, int endY)
{
	pathPoint.clear();
	if (canVerOrHorLink(startX, startY, endX, endY))
		return true;
	if (canOneConnerLink(startX, startY, endX, endY))
		return true;
	if (canDoubleConnerLink(startX, startY, endX, endY))
		return true;
	return false;
}
bool Game::canVerOrHorLink(int startX, int startY, int endX, int endY)
{
	if ( (startX - endX == 0)&& canVerticalLink(startX, startY, endY) ) {
		return true;
	}
	if ((startY - endY == 0) && canHorizontalLink(startY, startX, endX) )
		return true;
	return false;
}
bool Game::canVerticalLink(int X, int startY, int endY)
{
	int start = startY < endY ? startY : endY;
	int end = startY + endY - start;
	bool canLink = true;
	for (int i = start + 1; i < end; i++) {
		if (map[X][i] !=0) {
			canLink = false;
			break;
		}
	}
	return canLink;
}
bool Game::canHorizontalLink(int Y, int startX, int endX)
{
	int start = startX < endX ? startX : endX;
	int end = startX + endX - start;
	bool canLink = true;
	for (int i = start + 1; i < end; ++i) {
		if ( map[i][Y] !=0) {
			canLink = false;
			break;
		}
	}
	return canLink;
}

bool Game::canOneConnerLink(int startX, int startY, int endX, int endY)
{
	int x = startX;
	int y = endY;
	if (map[x][y] == 0 && canVerOrHorLink(x, y, startX, startY) && canVerOrHorLink(x, y, endX, endY)) {
		pathPoint.append(QPoint(x, y));
		return true;
	}
	x = endX;
	y = startY;
	if (map[x][y] == 0 && canVerOrHorLink(x, y, startX, startY) && canVerOrHorLink(x, y, endX, endY)) {
		pathPoint.append(QPoint(x, y));
		return true;
	}
	return false;
}

bool Game::canDoubleConnerLink(int startX, int startY, int endX, int endY)
{
	int x, y;
	for (int i = 0; i <= m_w + 1; i++) {
		if (i == startX)
			continue;
		x = i;
		y = startY;
		if (map[x][y] == 0 && canVerOrHorLink(x, y, startX, startY) && canOneConnerLink(x, y, endX, endY)) {
			pathPoint.append(QPoint(x, y));
			return true;
		}
	}
	for (int i = 0; i <= m_h + 1; i++) {
		if (i == startY)
			continue;
		x = startX;
		y = i;
		if (map[x][y] == 0 && canVerOrHorLink(x, y, startX, startY) && canOneConnerLink(x, y, endX, endY)) {
			pathPoint.append(QPoint(x, y));
			return true;
		}
	}
	return false;
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

QQmlListProperty<Tile> Game::tiles()
{
	return QQmlListProperty<Tile>(this, m_tiles);
}
