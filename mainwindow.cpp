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
	servers(new std::list<Server*>()),
	list(new ChannelList(this)),
	lineHandler(new LineHandler(list))
{
    ui->setupUi(this);
    connectToServer("irc.freenode.net", 6667);
	ui->channelCombo->setModel(list);

	//when channellist updated, update combobox index
	connect(list, &ChannelList::setIndex, 
		this, &MainWindow::setChannelIndex);
}

MainWindow::~MainWindow()
{
	servers->remove_if(
		[](Server *element)
	{
		delete element;
		return true;
	}
	);
	delete servers;
    delete ui;
	delete lineHandler;
}

void MainWindow::connectToServer(const QString &server, const int port)
{
    connect(socket, &QIODevice::readyRead,
		this, &MainWindow::readStream);
    socket->connectToHost(server, port);
	//add a wait for connection someday

    socket->write("NICK TEST444999\r\n");
    socket->write("USER TEST444999 0 * :TEST\r\n");
}

void MainWindow::setChannelIndex(int index)
{
	ui->channelCombo->setCurrentIndex(index);
}

void MainWindow::readStream()
{
	while (socket->canReadLine())
	{
		QString line = socket->readLine();
		addText(lineHandler->HandleLine(line));
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

void MainWindow::addServer(const QString &serverAddress,
	const int serverPort)
{
	Server* s = new Server(serverAddress, serverPort);
	servers->push_front(s);
	ui->serverCombo->addItem(s->getAddress());
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
