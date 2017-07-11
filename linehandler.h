#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <qstring.h>
#include <qstringlist.h>
#include <line.h>
#include <qdebug.h>
#include <channellist.h>
#include <server.h>

class LineHandler
{
public:
	LineHandler();
	~LineHandler();
	QString HandleLine(QString message, Server *server);
private:
	QString processCommand(Line &line, Server *server);
};

#endif