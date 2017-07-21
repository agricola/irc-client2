#ifndef USERLIST_H
#define USERLIST_H

#include <QAbstractListModel>
#include <QList>
#include <user.h>

class UserList : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit UserList(QObject *parent = nullptr);

	void addUser(const QString &full);
	void removeUser(const QString &full);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
	QList<User*> users;
	bool containsFull(const QString &full);
	bool containsNick(const QString &nick);
};

#endif // USERLIST_H