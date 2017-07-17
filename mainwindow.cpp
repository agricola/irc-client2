#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QScrollBar>
#include <channel.h>
#include <server.h>
#include <qdebug.h>
#include <line.h>
#include <vector>
#include <chrono>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow()),
    socket(new QTcpSocket(this)),
	servers(new ServerList(this)),
	lineHandler(new LineHandler(this)),
	connectWindow(new ConnectWindow(this))
{
    ui->setupUi(this);
	ui->textBrowser->setContextMenuPolicy(Qt::CustomContextMenu);
	//socket->write("QUIT");
	connect(connectWindow, &ConnectWindow::setConnectionDetails,
		this, &MainWindow::onSetConnection);
}

MainWindow::~MainWindow()
{
	delete lineHandler;
    delete ui;
}

void MainWindow::connectToServer(const QString &server, const int port)
{
    connect(socket, &QIODevice::readyRead, this, &MainWindow::readStream);
    socket->connectToHost(server, port);
}

void MainWindow::changeServer(Server *server)
{
	ui->channelCombo->setModel(server->getChannelList());
	connect(server->getChannelList(), &ChannelList::setIndex,
		this, &MainWindow::setChannelIndex);
}

Channel *MainWindow::getChannel(const int index)
{
	ChannelList *list = servers->getServers()[0]->getChannelList();
	Channel *c = list->getChannels()[index];
	return c;
}

void MainWindow::setChannelIndex(int index)
{
	ui->channelCombo->setCurrentIndex(index);
}

void MainWindow::readStream()
{
	//QFuture<void> future = QtConcurrent::run(readAll);
	while (socket->canReadLine())
	{
		QString line = socket->readLine();
		Server *s = servers->getServers()[0];
		handleLineResult(lineHandler->HandleLine(line, s, nickname));
		qApp->processEvents();
	}
}

void MainWindow::on_lineEdit_returnPressed()
{
	QString text = ui->lineEdit->text();
	QString result;
	if (text.length() <= 0) return;
	int index = ui->channelCombo->currentIndex();
	if (text.at(0) == "/")
	{
		result = text.remove(0, 1);
	}
	else if (index > 0)
	{
		result = "PRIVMSG " + getChannel(index)->getName() + " :" + text;
		addText(nickname + " | " + text + "\r\n");
	}
	else
	{
		addText("Nothing sent! Try /HELP\r\n");
	}
    socket->write(result.toUtf8() + "\r\n");
    ui->lineEdit->clear();
}

void MainWindow::addServer(const QString &address,
	const int port)
{
	servers->addServer(address, port);
	changeServer(servers->getServers()[0]);
}

void MainWindow::addText(const QString &text, const int index)
{
	Channel *channel = getChannel(index);
	channel->addText(text);
	if (index == ui->channelCombo->currentIndex())
	{
		QScrollBar *scrollBar = ui->textBrowser->verticalScrollBar();
		bool isMax = scrollBar->value() == scrollBar->maximum();

		ui->textBrowser->setText(channel->getText());

		if (isMax)
		{
			scrollBar->setValue(scrollBar->maximum());
		}
	}
}

void MainWindow::addText(const QString &text)
{
	addText(text, ui->channelCombo->currentIndex());
}

void MainWindow::handleLineResult(LineResult result)
{
	if (result.response != "")
	{
		socket->write(result.response.toUtf8() + "\r\n");
	}
	else
	{
		addText(result.text, result.channelIndex);
	}
	
}

void MainWindow::on_channelCombo_activated(int index)
{
	ui->textBrowser->setText(getChannel(index)->getText());
	QScrollBar *scrollBar = ui->textBrowser->verticalScrollBar();
	scrollBar->setValue(scrollBar->maximum());
}

void MainWindow::on_serverCombo_activated(int index)
{
	//qDebug() << "server act";
}

void MainWindow::on_textBrowser_customContextMenuRequested(
	const QPoint &pos)
{
	displayContextMenu(pos);
}

void MainWindow::onSetConnection(ConnectionDetails c)
{
	if (connecting) return;
	connecting = true;
	resetServer();
	const QString user = "USER " + c.userName
		+ " 0 * :" + c.realName + "\r\n";
	const QString nick = "NICK " + c.nickname
		+ "\r\n";
	const QString server = c.server;
	const int port = 6667;
	nickname = c.nickname;
	connectToServer(server, 6667);
	connect(socket, &QTcpSocket::connected, this,
		[server, port, user, nick, this]() {
			onConnect(server, port, user, nick);});
}

void MainWindow::onConnect(const QString &server, const int port,
	const QString &nickLine, const QString &userLine)
{
	connecting = false;
	addServer(server, port);
	ui->serverCombo->setModel(servers);
	socket->write(nickLine.toUtf8());
	socket->write(userLine.toUtf8());
}

void MainWindow::resetServer()
{
	delete servers;
	servers = new ServerList(this);

	// probably not all of this is needed
	socket->disconnect();
	socket->disconnectFromHost();
	delete socket;
	socket = new QTcpSocket(this);
}

void MainWindow::displayContextMenu(const QPoint &pos)
{
	QMenu contextMenu("Context menu", this);

	QAction action0("Connect", this);
	connect(&action0, &QAction::triggered,
		connectWindow, &ConnectWindow::show);
	contextMenu.addAction(&action0);

	QAction action1("Quit", this);
	connect(&action1, &QAction::triggered, this, &MainWindow::close);
	contextMenu.addAction(&action1);

	contextMenu.exec(mapToGlobal(pos));
}
