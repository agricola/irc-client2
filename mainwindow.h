#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <channel.h>
#include <server.h>
#include <vector>
#include <list>
#include <channellist.h>
#include <linehandler.h>

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
	void setChannelIndex(int index);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QString totalText;
	std::list<Server*> *servers;
	ChannelList *list;
	LineHandler *lineHandler;

	void addServer(const QString &serverAddress, const int serverPort);
    void addText(const QString &text);
    void connectToServer(const QString &server, const int port);
	const QString parsedLine(const QString &line);
};

#endif // MAINWINDOW_H
