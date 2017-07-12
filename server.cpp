#include "server.h"
#include <windows.h>

Server::Server(
	const QString &serverAddress,
	const int serverPort,
	QObject *parent) :
	QObject(parent),
	address(serverAddress),
	port(serverPort),
	channels(new ChannelList(this))
{
	channels->addChannel(address + " (Server)");
}

Server::~Server()
{
	
}

ChannelList *Server::getChannelList()
{
	return channels;
}

const QString Server::getAddress()
{
	return address;
}

const int Server::getPort()
{
	return port;
}
