#include "channel.h"

Channel::Channel(const QString channelName) :
	name(channelName)
{

}

Channel::~Channel()
{
}

const QString Channel::getName()
{
	return name;
}
