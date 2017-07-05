#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    connectToServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToServer()
{
    connect(socket, &QIODevice::readyRead, this, &MainWindow::readStream);

    socket->connectToHost("irc.freenode.net", 6667);
    socket->write("NICK TEST444999\r\n");
    socket->write("USER TEST444999 TEST4449 TEST :TEST\r\n");
}

void MainWindow::readStream()
{
    QString text;
    text = socket->readAll();
    totalText += text;

    QScrollBar *scrollBar = ui->textBrowser->verticalScrollBar();
    bool isMax = scrollBar->value() == scrollBar->maximum();

    ui->textBrowser->setText(totalText);

    if (isMax)
    {
        scrollBar->setValue(scrollBar->maximum());
        qDebug("YAY");
    }
}
