#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <channel.h>
#include <qstring.h>

class Server
{
public:
    Server(const QString serverAddress, const int serverPort);
	~Server();
    const std::list<Channel*> *channels();
    Channel *getCurrent();
	void setCurrent(Channel *channel);
    void addChannel(const QString name);
	const QString getAddress();
	const int getPort();

private:
	Channel *current;
    std::list<Channel*> *activeChannels;
	const QString address;
	const int *port;
};

#endif // SERVER_H
