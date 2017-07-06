#ifndef CHANNEL_H
#define CHANNEL_H

#include <qstring.h>

class Channel
{
public:
    Channel(const QString channelName);
	const QString getName();
	~Channel();

private:
	const QString name;
};

#endif // CHANNEL_H