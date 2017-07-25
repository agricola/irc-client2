#include "channel.h"

Channel::Channel(const QString &channelName, QObject *parent) :
	QObject(parent),
	name(channelName),
	userList(new UserList(this))
{

}

Channel::~Channel()
{

}

const QString Channel::getText()
{
	return text;
}

void Channel::addText(const QString &text)
{
	this->text += text;
}

UserList *Channel::getUserList()
{
	return &userList;
}

const QString Channel::getName()
{
	return name;
}
