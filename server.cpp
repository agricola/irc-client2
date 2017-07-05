#include "server.h"
#include <windows.h>

Server::Server(const char *serverAddress, const int serverPort) :
	address(serverAddress),
	port(new int(serverPort)),
	activeChannels(new std::list<Channel*>()),
	current()
{

}

const std::list<Channel*> *Server::channels()
{
	return activeChannels;
}

Channel *Server::getCurrent()
{
	return current;
}

void Server::setCurrent(Channel *channel)
{
	bool contains = (std::find(activeChannels->begin(),
		activeChannels->end(), channel) != activeChannels->end());
	if (contains)
	{
		current = channel;
	}
}

void Server::addChannel(const char *name)
{
	Channel *c = new Channel(name);
	activeChannels->push_back(c);
}

const char *Server::getAddress()
{
	return address;
}

const int Server::getPort()
{
	return *port;
}

Server::~Server()
{
	activeChannels->remove_if(
		[](Channel* element)
		{
			delete element;
			return true;
		}
	);
	delete port;
	delete activeChannels;
}
