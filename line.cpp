#include "line.h"
#include <qstring.h>
#include <qstringlist.h>

Line::Line(const QString &message) :
	fullMessage(message)
{
	parseLine(message);
}

Line::Line(const QString &prefix, const QString &command,
	const QStringList &middle, const QString &trailing) :
	prefix(prefix),
	command(command),
	middle(middle),
	trailing(trailing)
{
}

Line::~Line()
{
}

const QString Line::getPrefix()
{
	return prefix;
}

const QString Line::getCommand()
{
	return command;
}

const QStringList Line::getMiddle()
{
	return middle;
}

const QString Line::getTrailing()
{
	return trailing;
}

const QString Line::getFullMessage()
{
	return fullMessage;
}

bool Line::sentFrom(const QString source)
{
	size_t length = source.size();
	QStringRef subString(&prefix, 0, length);
	return subString == source;
}

void Line::parseLine(QString message)
{
	QString prefixEnd = message.section(':', 1);
	QString prefixMiddle = prefixEnd.split(" :").first();
	prefix = prefixMiddle.section(' ', 0, 0);
	command = prefixMiddle.section(' ', 1, 1);
	QString middleParams = prefixMiddle.section(' ', 2);
	middle = middleParams.split(QRegExp("\\s+"),
		QString::SkipEmptyParts);
	if (message.contains(" :"))
	{
		trailing = prefixEnd.split(" :").last();
	}

}
