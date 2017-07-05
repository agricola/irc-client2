#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QScrollBar>
#include <channel.h>
#include <server.h>
#include <qdebug.h>

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

void MainWindow::readStream()
{
    QString text;
    text = socket->readAll();
    AddText(text);
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString text = ui->lineEdit->text() + "\r\n";
    if (text.length() > 0)
    {
        socket->write(text.toUtf8());
        AddText(text);
        ui->lineEdit->clear();
    }
}

void MainWindow::AddText(QString text)
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
