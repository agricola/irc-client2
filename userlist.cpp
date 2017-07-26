#include "userlist.h"

UserList::UserList(QObject *parent)
	: QAbstractListModel(parent),
	initialized(false)
{
}

/*QVariant UserList::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}*/

void UserList::addUser(const QString &nick)
{
	// should this match by full or just nick?
	if (!containsNick(nick))
	{
		User *u = new User(this);
		u->setNick(nick);
		users.push_back(u);
		QModelIndex top = index(0);
		int end = users.size() - 1;
		QModelIndex bottom = index(end);
		dataChanged(top, bottom);
		qDebug() << "user added : " + nick;
	}
}

void UserList::removeUser(const QString &nick)
{
	users.erase(std::remove_if(users.begin(), users.end(),
		[nick](User *u) {
		return u->getNick() == nick; }));
	QModelIndex top = index(0);
	int end = users.size() - 1;
	QModelIndex bottom = index(end);
	dataChanged(top, bottom);
	qDebug() << "user removed : " + nick;
}

int UserList::rowCount(const QModelIndex &parent) const
{
	return users.count();
}

QVariant UserList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

	if (index.row() >= users.count())
		return QVariant();

	if (role == Qt::DisplayRole)
	{
		return users.at(index.row())->getNick();
	}
	else if (role == Qt::ToolTipRole)
	{
		return users.at(index.row())->getFull();
	}
	else
	{
		return QVariant();
	}
}

void UserList::setIsInitialized(bool initialized)
{
	this->initialized = initialized;
}

void UserList::addUsers(const QString &users)
{
	QStringList usersList = users.split(' ');
	for each (const QString &user in usersList)
	{
		addUser(user);
	}
}

const bool UserList::isInitialized()
{
	return initialized;
}

bool UserList::containsFull(const QString &full)
{
	QList<User*>::iterator found = std::find_if(
		users.begin(), users.end(), [full](User *u) {
		return u->getFull() == full; });

	return found != users.end();
}

bool UserList::containsNick(const QString &nick)
{
	QList<User*>::iterator found = std::find_if(
		users.begin(), users.end(), [nick](User *u) {
		return u->getNick() == nick; });

	return found != users.end();
}
/*
bool UserList::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool UserList::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}
*/
