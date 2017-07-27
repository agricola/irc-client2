#ifndef CHANNELLIST_H
#define CHANNELLIST_H

#include <QObject>
#include <QStringListModel>
#include <channel.h>
#include <qdebug.h>
#include <algorithm>
#include <functional>
#include <qlist.h>

class ChannelList : public QStringListModel
{
	Q_OBJECT

public:
	ChannelList(QObject *parent);
	~ChannelList();
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
	int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	Channel *addChannel(const QString &name);
	void removeChannel(const QString &name);
	const size_t getIndex(const QString &name);
	QList<Channel*> getChannels();
	Channel *getChannel(const QString &name);
	Channel *getChannelAt(const unsigned int index);
	void forEach(std::function<void(Channel*)> func);

signals:
	void setIndex(const int index);
	void setChanText(const QString &text, const int index);

private:
	QList<Channel*>::iterator getIter(const QString &name);
	QList<Channel *> channels;
	bool containsName(const QString &name);
	void channelTextChanged(QString &text, const QString &name);
	
};

#endif