#include "user.h"

User::User(const QString &full, QObject *parent) :
	QObject(parent),
	full(full)
{
	parseFull(full);
}


User::User(QObject *parent) : QObject(parent)
{
}

const QString User::getNick()
{
	return nick;
}

const QString User::getUser()
{
	return user;
}

const QString User::getHost()
{
	return host;
}

const QString User::getFull()
{
	return full;
}

void User::setNick(const QString &nick)
{
	this->nick = nick;
}

void User::parseFull(const QString &full)
{
	QStringList split(full.split(QRegExp("!|@")));
	nick = split[0];
	user = split[1];
	host = split[2];
}
