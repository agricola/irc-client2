#ifndef CHANNEL_H
#define CHANNEL_H

#include <qstring.h>
#include <QObject>
#include <userlist.h>

class Channel : public QObject
{
	Q_OBJECT

public:
    Channel(const QString &channelName, QObject *parent);
	const QString getName();
	~Channel();
	const QString getText();
	void addText(const QString &text);
	UserList *getUserList();

signals:
	void setText(QString &text, const QString &name);

private:
	const QString name;
	UserList userList;
	QString text;
};

#endif // CHANNEL_H