#ifndef LINE_H
#define LINE_H

#include <vector>
#include <qstring.h>
#include <qstringlist.h>

class Line
{
public:
	Line(const QString prefix, const QString command,
		const QStringList middle, const QString trailing);
	~Line();
	const QString getPrefix();
	const QString getCommand();
	const QStringList getMiddle();
	const QString getTrailing();

private:
	const QString prefix;
	const QString command;
	const QStringList middle;
	const QString trailing;
};

#endif LINE_H