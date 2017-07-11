#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QScrollBar>
#include <channel.h>
#include <server.h>
#include <qdebug.h>
#include <line.h>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    socket(new QTcpSocket(this)),
	servers(new ServerList(this)),
	lineHandler(new LineHandler())
{
    ui->setupUi(this);
    connectToServer("irc.freenode.net", 6667);
	
	//ui->channelCombo->setModel(channels);
	ui->serverCombo->setModel(servers);
	//when channellist updated, update combobox index
	//
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

    socket->write("NICK TEST444999\r\n");
    socket->write("USER TEST444999 0 * :TEST\r\n");
}

void MainWindow::changeServer(Server *server)
{
	ui->channelCombo->setModel(server->getChannels());
	connect(server->getChannels(), &ChannelList::setIndex,
		this, &MainWindow::setChannelIndex);
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
		addText(lineHandler->HandleLine(line, servers->getServers()[0]));
		qApp->processEvents();
	}
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString text = ui->lineEdit->text() + "\r\n";
    if (text.length() > 0)
    {
        socket->write(text.toUtf8());
        addText(text);
        ui->lineEdit->clear();
    }
}

void MainWindow::addServer(const QString &address,
	const int port)
{
	servers->addServer(address, port);
	changeServer(servers->getServers()[0]);
	//ui->serverCombo->addItem(address);
	//ui->serverCombo->setCurrentIndex(servers->getIndex(address, 5555));

	//connect()
}

void MainWindow::addText(const QString &text)
{
    totalText += text;
    QScrollBar *scrollBar = ui->textBrowser->verticalScrollBar();
    bool isMax = scrollBar->value() == scrollBar->maximum();

    ui->textBrowser->setText(totalText);

    if (isMax)
    {
        scrollBar->setValue(scrollBar->maximum());
    }
}

void MainWindow::on_channelCombo_activated(int index)
{
	//qDebug() << "channel act";
}

void MainWindow::on_serverCombo_activated(int index)
{
	//qDebug() << "server act";
}
