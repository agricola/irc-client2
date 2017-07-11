#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <channel.h>
#include <qstring.h>
#include <channellist.h>

class Server : public QObject
{
	Q_OBJECT

public:
    Server(
		const QString &serverAddress,
		const int serverPort,
		QObject *parent);
	~Server();
    ChannelList *getChannels();
	const QString getAddress();
	const int getPort();

private:
	ChannelList *channels;
	const QString address;
	const int port;
};

#endif // SERVER_H
