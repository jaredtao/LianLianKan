#include "game.h"
#include <time.h>
#include <QQmlEngine>
#include <QDebug>
#define MAX_IMAGE (25)
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
		defaultTime = 90;
		gametime = defaultTime;
		scorePerLink = 10;
	}
	Game::GameState state;
	Game::GameDifficulty difficulty;
	int level;
	int score;
	int tip;
	int w;
	int h;
	int gametime;
	QTimer timer;
	int defaultTime;
	int scorePerLink;			//Ã¿Á¬Ò»žöµÄµÃ·Ö
};

Game::Game(QObject *parent): QObject(parent), m_dptr(new GamePrivate)
{
	qmlRegisterType<Tile>("GameCore", 1, 0, "Tile");
	setState(READY);
	setDifficulty(EASY);
	setLevel(1);
	setScore(0);
	setTip(3);
	setW(6);
	setH(6);
	setGametime(90);

	memset(map, 0, sizeof(map));
	qsrand(time(0));
	m_dptr->timer.setInterval(1000);
	connect(&m_dptr->timer, SIGNAL(timeout()),this, SLOT(timeout()));
}

Game::~Game()
{
	delete m_dptr;
	m_tiles.clear();
}
void Game::timeout()
{
	setGametime(gametime() - 1);
	if (gametime() == 0) {
		if (!isWin())
			setState(LOSE);
	}

}
bool Game::startGame()
{
	if (state() == PLAYING)
		return false;
	if (state() == WIN) {
		setW((w() + 2) > MAXW ? w() + 2 : MAXW);
		setH((h() + 2) % MAXH ? h() + 2 : MAXH);
		setLevel(level() + 1);
		m_dptr->defaultTime -= 5;
		if (m_dptr->defaultTime <30)
			m_dptr->defaultTime = 30;
		setGametime(m_dptr->defaultTime);
	}
	start = end =  QPoint(0, 0);
	clicked = 0;
	setState(PLAYING);
	m_tiles.clear();
	for (int i = 0; i < w() * h(); ++i) {
		m_tiles << new Tile;
	}

	int index = 1;
	int ref = 0;
	//µØÍŒÏÂ±êŽÓ1¿ªÊŒ£¬0 µÄÐÐºÍÁÐ¿Õ³öÀŽ£¬·œ±ãÖ®ºóŒÆËãµÄÊ±ºò×ö±ßœçŒì²â
	for (int i = 1; i <= w(); i++) {
		for (int j = 1; j <= h(); j++) {
			map[i][j] = index;
			ref++;
			if(ref>=2) {
				ref = 0;
				++index;
				if(index > MAX_IMAGE)
					index = index % (MAX_IMAGE);
			}
		}
	}

	for (int i = 1 ; i <= w(); ++i) {
		for (int j = 1; j <= h(); ++j) {
			int x = qrand() % w();
			int y = qrand() % h();
			int t = map[i][j];
			map[i][j] = map[x][y];
			m_tiles[ (i -1) * h() + j -1]->setValue(map[x][y]);
			map[x][y] = t; 
		}
	}
	pauseGame(false);
	return true;
}
bool Game::reStart()
{
	start = end =  QPoint(0, 0);
	clicked = 0;

	setDifficulty(EASY);
	setLevel(1);
	setScore(0);
	setTip(3);
	setW(6);
	setH(6);
	m_dptr->defaultTime = 90;
	setGametime(m_dptr->defaultTime);
	setState(PLAYING);
	m_tiles.clear();
	for (int i = 0; i < w() * h(); ++i) {
		m_tiles << new Tile;
	}
	int index = 1;
	int ref = 0;
	//µØÍŒÏÂ±êŽÓ1¿ªÊŒ£¬0 µÄÐÐºÍÁÐ¿Õ³öÀŽ£¬·œ±ãÖ®ºóŒÆËãµÄÊ±ºò×ö±ßœçŒì²â
	for (int i = 1; i <= w(); i++) {
		for (int j = 1; j <= h(); j++) {
			map[i][j] = index;
			ref++;
			if(ref>=2) {
				ref = 0;
				++index;
				if(index > MAX_IMAGE)
					index = index % (MAX_IMAGE);
			}
		}
	}

	for (int i = 1 ; i <= w(); ++i) {
		for (int j = 1; j <= h(); ++j) {
			int x = qrand() % w();
			int y = qrand() % h();
			int t = map[i][j];
			map[i][j] = map[x][y];
			m_tiles[ (i -1) * w() + j -1]->setValue(map[x][y]);
			map[x][y] = t;
		}
	}

	pauseGame(false);
	return true;
}
void Game::pauseGame(bool v)
{
	if (v) {
		setState(PAUSE);
		m_dptr->timer.stop();
	} else {
		setState(PLAYING);
		m_dptr->timer.start();
	}
}
bool Game::isWin()
{
	for (int i = 1; i <= w(); i++) {
		for (int j = 1; j <= h(); j++) {
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
		m_tiles[(startX - 1) * h() + startY - 1 ]->setValue(0);
		m_tiles[(endX -1) * h() + endY - 1]->setValue(0);
		setScore(score() + m_dptr->scorePerLink);
		if (isWin()) {
			setState(WIN);
			pauseGame(true);

		} else {
			if (needRandom())
				random();
		}
		return true;
	}
	return false;
}
bool Game::getTip()
{
	int x1, y1, x2, y2;
	if (tip(x1, y1, x2, y2))
	{
		m_tiles[ (x1 + 1) * h() + y1 + 1 ]->setTiped(true);
		m_tiles[ (x2 + 1) * h() + y2 + 1 ]->setTiped(true);
		return true;
	}
	return false;
}
bool Game::tip(int &startX, int &startY, int &endX, int &endY)
{
	for (startX = 1; startX <= w(); ++startX) {
		for (startY = 1; startY <= h(); ++startY) {
			for (endX = 1; endX <= w(); ++endX) {
				for (endY = 1; endY <= h(); ++endY) {
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
/*!
 * \brief Game::flip
 * \param index
 * \return -1 不可点
 *         0 Linked
 *         1  clicked
 */
int Game::flip(int index)
{
	if (state() != PLAYING)
		return -1;
	Tile *t = tile(index);
	if (!t || t->value() == 0 ||  t->selected() || t->tiped())
		return -1;
	++clicked;
	t->setSelected(true);
	if (clicked == 1) {
		start.setX (index / h() + 1);
		start.setY (index % h() + 1);
		return 1;
	} else {
		end.setX (index / h() + 1);
		end.setY (index % h() + 1);
		link(start.x(), start.y(), end.x(), end.y());
		clicked = 0;
		start = end =  QPoint(0, 0);
		return 0;
	}
}
void Game::random()
{
	foreach(Tile *tile, m_tiles) {
		tile->setSelected(false);
		tile->setTiped(false);
	}
	for (int i = 1 ; i <= w(); ++i) {
		for (int j = 1; j <= h(); ++j) {
			int x = qrand() % w();
			int y = qrand() % h();
			int t = map[i][j];
			map[i][j] = map[x][y];
			m_tiles[ (i -1) * w() + j -1]->setValue(map[x][y]);
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
	for (int i = 0; i <= w() + 1; i++) {
		if (i == startX)
			continue;
		x = i;
		y = startY;
		if (map[x][y] == 0 && canVerOrHorLink(x, y, startX, startY) && canOneConnerLink(x, y, endX, endY)) {
			pathPoint.append(QPoint(x, y));
			return true;
		}
	}
	for (int i = 0; i <= h() + 1; i++) {
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
	for (int i = 0; i != m_tiles.size(); i++) {
		qDebug()<< __FILE__<<__LINE__<<i <<m_tiles[i]->value();
	}
	return QQmlListProperty<Tile>(this, m_tiles);
}

int Game::gametime() const
{
	return m_dptr->gametime;
}
void Game::setGametime(int value)
{
	if (value == m_dptr->gametime) return;
	m_dptr->gametime = value;
	emit gametimeChanged();

}
Tile * Game::tile(int index) const
{
	return (index >= 0 && index < m_tiles.count()) ? m_tiles.at(index) : 0;
}