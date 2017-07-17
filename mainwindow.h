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
#include <qfuture.h>
#include <QtConcurrent\qtconcurrentrun.h>
#include <serverlist.h>
#include <connectwindow.h>

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
    void on_textBrowser_customContextMenuRequested(const QPoint &pos);
	//void customContextMenuRequested(const QPoint &pos);
	void onSetConnection(ConnectionDetails c);
	
private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QString totalText;
	ServerList *servers;
	LineHandler *lineHandler;
	QString nickname;
	ConnectWindow *connectWindow;
	bool connecting = false;

	void addServer(const QString &serverAddress, const int serverPort);
    void addText(const QString &text, const int index);
	void addText(const QString &text);
	void handleLineResult(LineResult result);
    void connectToServer(const QString &server, const int port);
	void changeServer(Server *server);
	void displayContextMenu(const QPoint &pos);
	Channel *getChannel(const int index);
	void onConnect(const QString &server, const int port,
		const QString &nickLine, const QString &userLine);
	void resetServer();
};

#endif // MAINWINDOW_H
