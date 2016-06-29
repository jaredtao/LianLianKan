#ifndef TILE_H
#define TILE_H
#include <QObject>
#include <QDebug>
class Tile: public QObject
{
	Q_OBJECT
public:
	Tile(QObject*parent = 0): QObject(parent), m_value(0), m_selected(false), m_tiped(false)
	{}
	Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
	Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
	Q_PROPERTY(bool tiped READ tiped WRITE setTiped NOTIFY tipedChanged)

	void init()
	{
		m_value = 0;
		m_selected = false;
		m_tiped = false;
		emit valueChanged();
		emit selectedChanged();
		emit tipedChanged();
	}
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
	bool selected() const
	{
		return m_selected;
	}
	void setSelected(bool v)
	{
		if (v == m_selected) return;
		m_selected = v;
		emit selectedChanged();
	}

	bool tiped() const
	{
		return m_tiped;
	}
	void setTiped(bool v)
	{
		qDebug()<<__FUNCTION__;
		if (v == m_tiped) return ;
		m_tiped = v;
		qDebug()<<__FUNCTION__<<v;
		emit tipedChanged();
	}
signals:
	void valueChanged();
	void selectedChanged();
	void tipedChanged();
private:
	  int m_value;
	  bool m_selected;
	  bool m_tiped;
};
#endif // TILE_H
