#pragma once

#include <QObject>

template<typename T>
class AbstractList : public QStringListModel
{
	Q_OBJECT

public:
	AbsstractList(QObject *parent);
	~AbsstractList();
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
	int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	void addItem(const QString name);
	void removeItem(const QString name);

signals:
	void setIndex(int index);

private:
	std::vector<T*> items;
	bool containsName(const QString name);


};

template<typename T>
inline AbstractList<T>::~AbsstractList()
{
	items.clear();
}

template<typename T>
inline QVariant AbstractList<T>::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= channels.size())
		return QVariant();

	if (role == Qt::DisplayRole)
	{
		return items.at(index.row())->getName();
	}
	else
		return QVariant();
}

template<typename T>
int AbstractList<T>::rowCount(const QModelIndex & parent) const
{
	return items.size();
}

template<typename T>
void AbstractList<T>::addItem(const QString name)
{
	if (containsName(name))
	{
		qDebug() << "already contains " + name;
		return;
	}
	T *c = new T(name, this);
	channels.push_back(c);
	QModelIndex top = index(0);
	int end = channels.size() - 1;
	QModelIndex bottom = index(end);
	dataChanged(top, bottom);
	emit setIndex(end);
}

template<typename T>
void AbstractList<T>::removeItem(const QString name)
{
	items.erase(std::remove_if(items.begin(), items.end(),
		[name](Channel *c) { return c->getName() == name; }));
}

template<typename T>
bool AbstractList<T>::containsName(const QString name)
{
	std::vector<T*>::iterator found =
		std::find_if(items.begin(), items.end(),
			[name](T *c) { return c->getName() == name; });
	if (found != T.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
