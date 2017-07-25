#ifndef LINE_H
#define LINE_H

#include <vector>
#include <qstring.h>
#include <qstringlist.h>
#include <qdebug.h>
#include <qobject.h>

class Line
{
public:
	Line(const QString &message);
	//Line(const QString &prefix, const QString &command,
	//	const QStringList &middle, const QString &trailing=NULL);
	~Line();
	const QString getPrefix();
	const QString getCommand();
	const QString getFullMessage();
	const QString last();
	const QString getNickname();
	const QStringList *getParams();
	bool sentFrom(const QString source);

private:
	QString prefix;
	QString command;
	QString fullMessage;
	QString nickname;
	QStringList *params;
	void parseLine(QString message);
};

#endif LINE_H