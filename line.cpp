#include "line.h"
#include <qstring.h>
#include <qstringlist.h>

Line::Line(const QString prefix, const QString command,
	const QStringList middle, const QString trailing) :
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
