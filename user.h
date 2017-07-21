#ifndef USER_H
#define USER_H

#include <QObject>
#include <qstring.h>
#include <qdebug.h>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(const QString &full, QObject *parent = nullptr);
	const QString getNick();
	const QString getUser();
	const QString getHost();
	const QString getFull();

signals:

public slots:

private:
	QString nick;
	QString user;
	QString host;
	const QString full;

	void parseFull(const QString &full);

};

#endif // USER_H