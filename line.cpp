#include "line.h"
#include <qstring.h>
#include <qstringlist.h>

Line::Line(const QString &message) :
	fullMessage(message),
	trailing(NULL),
	middle(NULL)
{
	parseLine(message);
}

/*Line::Line(const QString &prefix, const QString &command,
	const QStringList &middle, const QString &trailing) :
	prefix(prefix),
	command(command),
	middle(middle),
	trailing(trailing)
{
}*/

Line::~Line()
{
	delete middle;
	delete trailing;
}

const QString Line::getPrefix()
{
	return prefix;
}

const QString Line::getCommand()
{
	return command;
}

const QStringList *Line::getMiddle()
{
	return middle;
}

const QString *Line::getTrailing()
{
	return trailing;
}

const QString Line::getFullMessage()
{
	return fullMessage;
}

const QString Line::getNickname()
{
	return nickname;
}

bool Line::sentFrom(const QString source)
{
	//size_t length = source.size();
	//QStringRef subString(&prefix, 0, length);
	//return subString == source;
	return nickname == source;
}

void Line::parseLine(QString message)
{
	if (message.left(4) == "PING")
	{
		command = "PING";
	}
	else
	{
		QString prefixEnd = message.section(':', 1);
		QString prefixMiddle = prefixEnd.split(" :").first();
		prefix = prefixMiddle.section(' ', 0, 0);
		QStringRef nick(&prefix, 0, prefix.indexOf("!"));
		nickname = nick.toString();
		command = prefixMiddle.section(' ', 1, 1);
		QString middleParams = prefixMiddle.section(' ', 2);
		middle = new QStringList(middleParams.split(QRegExp("\\s+"),
			QString::SkipEmptyParts));
	}
	int trailStart = message.indexOf(" :");
	if (trailStart >= 0)
	{
		trailing = new QString(
			message.right(message.size() - trailStart - 2)
			.remove(QRegExp("[\r\n]{2}$")));
		//qDebug() << *trailing;
	}

}

void Line::parseLine2(QString message)
{
}
