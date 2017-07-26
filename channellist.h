#ifndef CHANNELLIST_H
#define CHANNELLIST_H

#include <QObject>
#include <QStringListModel>
#include <channel.h>
#include <qdebug.h>
#include <algorithm>
#include <functional>

class ChannelList : public QStringListModel
{
	Q_OBJECT

public:
	ChannelList(QObject *parent);
	~ChannelList();
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
	int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	Channel *addChannel(const QString &name);
	void removeChannel(const QString name);
	const size_t getIndex(const QString &name);
	std::vector<Channel*> getChannels();
	Channel *getChannel(const QString &name);
	Channel *getChannelAt(const unsigned int index);
	void forEach(std::function<void(Channel*)> func);

signals:
	void setIndex(int index);

private:
	std::vector<Channel*> channels;
	bool containsName(const QString &name);
	

};

#endif