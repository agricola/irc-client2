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
	const QStringList *getMiddle();
	const QString *getTrailing();
	const QString getFullMessage();
	const QString getNickname();
	bool sentFrom(const QString source);

private:
	QString prefix;
	QString command;
	QStringList *middle;
	QString *trailing;
	QString fullMessage;
	QString nickname;
	void parseLine(QString message);
	void parseLine2(QString message);
};

#endif LINE_H