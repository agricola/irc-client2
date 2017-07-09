#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <qstring.h>
#include <qstringlist.h>
#include <line.h>
#include <qdebug.h>
#include <channellist.h>

class LineHandler
{
public:
	LineHandler(ChannelList *channels);
	~LineHandler();
	QString HandleLine(QString message);
private:
	ChannelList *channelList;
	QString processCommand(Line &line);
};

#endif