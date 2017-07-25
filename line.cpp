#include "line.h"
#include <qstring.h>
#include <qstringlist.h>

Line::Line(const QString &message) :
	fullMessage(message),
	params(new QStringList())
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
	delete params;
}

const QString Line::getPrefix()
{
	return prefix;
}

const QString Line::getCommand()
{
	return command;
}

const QStringList *Line::getParams()
{
	return params;
}

const QString Line::getFullMessage()
{
	return fullMessage;
}

const QString Line::last()
{
	return params->last();
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
	QStringList prefixTrail = message.split(" :");
	QString *trailing = NULL;
	if (prefixTrail.size() == 2)
	{
		trailing = new QString(prefixTrail.last()
			.remove(QRegExp("[\r\n]{2}$")));
	}

	if (message.left(4) == "PING")
	{
		command = "PING";
	}
	else
	{
		QString prefixMiddle = prefixTrail.first().section(':', 1);
		
		prefix = prefixMiddle.section(' ', 0, 0);

		QStringRef nick(&prefix, 0, prefix.indexOf("!"));
		nickname = nick.toString();

		command = prefixMiddle.section(' ', 1, 1);

		QString middleParams = prefixMiddle.section(' ', 2);
		QStringList *mid = new QStringList(middleParams.split(QRegExp("\\s+"),
			QString::SkipEmptyParts));
		delete params;
		params = mid;
	}

	if (trailing != NULL)
	{
		params->append(*trailing);
	}
	delete trailing;

}