#ifndef SERVERLIST_H
#define SERVERLIST_H

#include <QObject>
#include <QStringListModel>
#include <server.h>
#include <qdebug.h>
#include <algorithm>

// template class doesn't work with Q_OBJECT so this looks
// very similar to ChannelList atm
class ServerList : public QStringListModel
{
	Q_OBJECT

public:
	ServerList(QObject *parent);
	~ServerList();
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
	int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	void addServer(const QString &name, const int port);
	void removeServer(const QString &name, const int port);
	const size_t getIndex(const QString &name, const int port);
	std::vector<Server*> getServers();

signals:
	void setIndex(int index);

private:
	std::vector<Server*> servers;
	bool contains(const QString &name, const int port);

};

#endif