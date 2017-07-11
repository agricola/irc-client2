#include "serverlist.h"

ServerList::ServerList(QObject *parent)
	: QStringListModel(parent)
{
}

ServerList::~ServerList()
{
}

QVariant ServerList::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= servers.size())
		return QVariant();

	if (role == Qt::DisplayRole)
	{
		return servers.at(index.row())->getAddress();
	}
	else
		return QVariant();
}

int ServerList::rowCount(const QModelIndex & parent) const
{
	return servers.size();
}

void ServerList::addServer(const QString &name, const int port)
{
	if (contains(name, port))
	{
		qDebug() << "already contains " + name;
		return;
	}
	Server *c = new Server(name, port, this);
	servers.push_back(c);
	QModelIndex top = index(0);
	int end = servers.size() - 1;
	QModelIndex bottom = index(end);
	dataChanged(top, bottom);
	emit setIndex(end);
}

void ServerList::removeServer(const QString &name, const int port)
{
	servers.erase(std::remove_if(servers.begin(), servers.end(),
		[name, port](Server *s) {
			return s->getAddress() == name && s->getPort() == port;}));
}

const size_t ServerList::getIndex(const QString & name, const int port)
{
	std::vector<Server*>::iterator iter = std::find_if(
		servers.begin(), servers.end(), [name, port](Server *s) {
		return s->getAddress() == name && s->getPort() == port; });
	size_t index = std::distance(servers.begin(), iter);
	return index;
}

std::vector<Server*> ServerList::getServers()
{
	return servers;
}

bool ServerList::contains(const QString &name, const int port)
{
	std::vector<Server*>::iterator found = std::find_if(
		servers.begin(), servers.end(), [name, port](Server *s) {
			return s->getAddress() == name && s->getPort() == port; });
	if (found != servers.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}


