#include "channel.h"

Channel::Channel(const char *channelName) :
	name(channelName)
{

}

Channel::~Channel()
{
}

const char *Channel::getName()
{
	return name;
}
