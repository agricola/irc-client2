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
	server(new Server("irc.freenode.net", 6667))
{
    ui->setupUi(this);
    connectToServer();
}

MainWindow::~MainWindow()
{
	delete server;
    delete ui;
}

void MainWindow::connectToServer()
{
    connect(socket, &QIODevice::readyRead, this, &MainWindow::readStream);
    socket->connectToHost(server->getAddress(), server->getPort());
    socket->write("NICK TEST444999\r\n");
    socket->write("USER TEST444999 0 * :TEST\r\n");
}

QString MainWindow::parsedLine(QString line)
{
	QString prefixMiddle = line.section(':', 1, -2);
	//qDebug() << line;
	QString prefix = prefixMiddle.section(' ', 0, 0);
	QString command = prefixMiddle.section(' ', 1, 1);
	QString middle = prefixMiddle.section(' ', 2);
	QStringList middleParams = middle.split(QRegExp("\\s+"),
		QString::SkipEmptyParts);
	//qDebug() << middleParams.count();
	//QString trailing = line.section(' :', -1, -1);
	QString trailing = line.split(" :").last();
	Line l(prefix, command, middleParams, trailing); //not needed atm
	return trailing;
}

void MainWindow::readStream()
{
	while (socket->canReadLine())
	{
		QString line = socket->readLine();
		addText(parsedLine(line));
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

QStringList MainWindow::splitLine(QString line)
{
	return	line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
}

void MainWindow::addText(QString text)
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
