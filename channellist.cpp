#include "channellist.h"

ChannelList::ChannelList(QObject *parent)
	: QStringListModel(parent)
{
}

ChannelList::~ChannelList()
{
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

const size_t ChannelList::getIndex(const QString &name)
{
	std::vector<Channel*>::iterator iter = std::find_if(
		channels.begin(), channels.end(), [name](Channel *s) {
		return s->getName() == name; });
	size_t index = std::distance(channels.begin(), iter);
	return index < channels.size() ? index : -1;
}

std::vector<Channel*> ChannelList::getChannels()
{
	return channels;
}

Channel *ChannelList::getChannel(const QString &name)
{
	std::vector<Channel*>::iterator found =
		std::find_if(channels.begin(), channels.end(),
			[name](Channel *c) { return c->getName() == name; });
	return found != channels.end() ? *found : NULL;
}

Channel *ChannelList::getChannelAt(const unsigned int index)
{
	return channels[index];
}

void ChannelList::removeChannel(const QString name)
{
	channels.erase(std::remove_if(channels.begin(), channels.end(),
		[name](Channel *c) { return c->getName() == name; }));
}

bool ChannelList::containsName(const QString &name)
{
	return getChannel(name) != NULL;
}
/*
void ChannelList::setIndex(int index)
{
	//connected to mainwindow
	//rework this at some point
	qDebug() << "SET INDEX";
}
*/
