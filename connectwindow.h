#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QWidget>
#include <qstring.h>

struct ConnectionDetails
{
	QString server;
	QString nickname;
	QString realName;
	QString userName;
};

namespace Ui {
class ConnectWindow;
}

class ConnectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectWindow(QWidget *parent = 0);
    ~ConnectWindow();

private slots:
    void on_pushButton_clicked();

signals:
	void setConnectionDetails(ConnectionDetails c);

private:
    Ui::ConnectWindow *ui;
};

#endif // CONNECTWINDOW_H
