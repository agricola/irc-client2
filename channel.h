#ifndef CHANNEL_H
#define CHANNEL_H

#include <qstring.h>
#include <QObject>


class Channel : public QObject
{
	Q_OBJECT

public:
    Channel(const QString &channelName, QObject *parent);
	const QString getName();
	~Channel();
	const QString getText();
	void addText(const QString &text);

private:
	const QString name;
	QString text;
};

#endif // CHANNEL_H