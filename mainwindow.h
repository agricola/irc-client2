#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <channel.h>
#include <server.h>
#include <vector>
#include <list>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void readStream();
    void on_lineEdit_returnPressed();
    void on_channelCombo_activated(int index);
    void on_serverCombo_activated(int index);
    void on_channelCombo_editTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QString totalText;
	std::list<Server*> *servers;

	QStringList splitLine(QString line);
    void addText(QString text);
    void connectToServer(QString server, int port);
	QString parsedLine(QString line);
};

#endif // MAINWINDOW_H
