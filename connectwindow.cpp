#include "connectwindow.h"
#include "ui_connectwindow.h"
#include <qdebug.h>

ConnectWindow::ConnectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectWindow)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Window);
}

ConnectWindow::~ConnectWindow()
{
    delete ui;
}

void ConnectWindow::on_pushButton_clicked()
{
	ConnectionDetails c;
	c.server = ui->ServerLine->text();
	c.nickname = ui->NickLine->text();
	c.realName = ui->RealLine->text();
	c.userName = ui->UserLine->text();
	setConnectionDetails(c);
	// TODO: check details
	close();
}
