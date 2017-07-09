#include "channel.h"

Channel::Channel(const QString &channelName, QObject *parent) :
	QObject(parent),
	name(channelName)
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

const QString Channel::getName()
{
	return name;
}
