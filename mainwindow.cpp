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
    ui(new Ui::MainWindow),
    socket(new QTcpSocket(this)),
	servers(new ServerList(this)),
	lineHandler(new LineHandler(this)),
	userName("TESTAGRI")
{
    ui->setupUi(this);
    connectToServer("irc.freenode.net", 6667);
	ui->serverCombo->setModel(servers);

	// code to benchmark
	/*const QString line = ":verne.freenode.net 372 TEST444999 : -By connecting to freenode you indicate that you have read and";
	//const QString *line2 = new QString(line);
	auto begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < 10000; i++)
	{
	}
	auto end = std::chrono::high_resolution_clock::now();
	qDebug() << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
	//delete line2;*/
}

MainWindow::~MainWindow()
{
	delete lineHandler;
    delete ui;
}

void MainWindow::connectToServer(const QString &server, const int port)
{
    connect(socket, &QIODevice::readyRead,
		this, &MainWindow::readStream);
    socket->connectToHost(server, port);
	addServer(server, port);
	//add a wait for connection someday
	QString data = "NICK " + userName + "\r\n";
    socket->write(data.toUtf8().data());
    socket->write("USER TEST444999 0 * :TEST\r\n");
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
		handleLineResult(lineHandler->HandleLine(line, s, userName));
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
		addText(userName + " | " + text + "\r\n");
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
