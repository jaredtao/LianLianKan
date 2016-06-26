#ifndef TILE_H
#define TILE_H
#include <QObject>
class Tile: public QObject
{
	Q_OBJECT
public:
	Tile(QObject*parent = 0): QObject(parent), m_value(0)
	{}
	Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)

	int value() const
	{
		return m_value;
	}
	void setValue(int v)
	{
		if ( v == m_value) return;
		m_value = v;
		emit valueChanged();
	}
signals:
	void valueChanged();
private:
	  int m_value;
};
#endif // TILE_H
