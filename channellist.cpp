#include "channellist.h"

ChannelList::ChannelList(QObject *parent)
	: QStringListModel(parent)
{
}

ChannelList::~ChannelList()
{
	channels.clear();
}

QVariant ChannelList::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= channels.size())
		return QVariant();

	if (role == Qt::DisplayRole)
	{
		return channels.at(index.row())->getName();
	}
	else
		return QVariant();
}

int ChannelList::rowCount(const QModelIndex & parent) const
{
	return channels.size();
}

void ChannelList::addChannel(const QString name)
{
	if (containsName(name))
	{
		qDebug() << "already contains " + name;
		return;
	}
	Channel *c = new Channel(name, this);
	channels.push_back(c);
	QModelIndex top = index(0);
	int end = channels.size() - 1;
	QModelIndex bottom = index(end);
	dataChanged(top, bottom);
	emit setIndex(end);
}

void ChannelList::removeChannel(const QString name)
{
	channels.erase(std::remove_if(channels.begin(), channels.end(),
		[name](Channel *c) { return c->getName() == name; }));
}

bool ChannelList::containsName(const QString name)
{
	std::vector<Channel*>::iterator found =
		std::find_if(channels.begin(), channels.end(),
			[name](Channel *c) { return c->getName() == name; });
	if (found != channels.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*
void ChannelList::setIndex(int index)
{
	//connected to mainwindow
	//rework this at some point
	qDebug() << "SET INDEX";
}
*/
