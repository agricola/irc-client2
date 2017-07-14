#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <qstring.h>
#include <qstringlist.h>
#include <line.h>
#include <qdebug.h>
#include <channellist.h>
#include <server.h>

struct LineResult
{
	QString text;
	size_t channelIndex;
};

class LineHandler : public QObject
{
	Q_OBJECT

public:
	LineHandler(QObject *parent);
	~LineHandler();
	LineResult HandleLine(QString message,
		Server *server,
		const QString &name);
private:
	LineResult processCommand(Line &line,
		Server *server,
		const QString &name);
};

#endif