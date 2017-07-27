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

Channel *ChannelList::addChannel(const QString &name)
{
	if (containsName(name))
	{
		qDebug() << "already contains " + name;
		return NULL;
	}
	Channel *c = new Channel(name, this);
	connect(c, &Channel::setText, this, &ChannelList::channelTextChanged);
	channels.push_back(c);
	QModelIndex top = index(0);
	int end = channels.size() - 1;
	QModelIndex bottom = index(end);
	dataChanged(top, bottom);
	emit setIndex(end);
	return c;
}

const size_t ChannelList::getIndex(const QString &name)
{
	QList<Channel*>::iterator iter = std::find_if(
		channels.begin(), channels.end(), [name](Channel *s) {
		return s->getName() == name; });
	size_t index = std::distance(channels.begin(), iter);
	return index < channels.size() ? index : -1;
}

QList<Channel*> ChannelList::getChannels()
{
	return channels;
}

Channel *ChannelList::getChannel(const QString &name)
{
	QList<Channel*>::iterator found = getIter(name);
	return found != channels.end() ? *found : NULL;
}

Channel *ChannelList::getChannelAt(const unsigned int index)
{
	return channels[index];
}

void ChannelList::forEach(std::function<void(Channel*)> func)
{
	if (channels.size() > 1)
	{
		for (size_t i = 1; i < channels.size(); i++)
		{
			Channel *c = channels[i];
			func(c);
		}
	}
}

void ChannelList::removeChannel(const QString &name)
{
	/*channels.erase(std::remove_if(channels.begin(), channels.end(),
		[name](Channel *c) { return c->getName() == name; }));*/
	Channel *c = getChannel(name);
	disconnect(c);
	channels.erase(getIter(name));
}
QList<Channel*>::iterator ChannelList::getIter(const QString & name)
{
	return std::find_if(channels.begin(), channels.end(),
		[name](Channel *c) { return c->getName() == name; });
}

bool ChannelList::containsName(const QString &name)
{
	return getChannel(name) != NULL;
}
void ChannelList::channelTextChanged(QString &text, const QString &name)
{
	const int index = getIter(name) - channels.begin();
	emit setChanText(text, index);
}
/*
void ChannelList::setIndex(int index)
{
	//connected to mainwindow
	//rework this at some point
	qDebug() << "SET INDEX";
}
*/
