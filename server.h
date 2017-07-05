#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <channel.h>

class Server
{
public:
    Server(const char *serverAddress, const int serverPort);
	~Server();
    const std::list<Channel*> *channels();
    Channel *getCurrent();
	void setCurrent(Channel *channel);
    void addChannel(const char *name);
	const char *getAddress();
	const int getPort();

private:
	Channel *current;
    std::list<Channel*> *activeChannels;
	const char *address;
	const int *port;
};

#endif // SERVER_H
