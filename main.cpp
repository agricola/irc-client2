#include "mainwindow.h"
#include "connectwindow.h"
#include <QApplication>
#include <vld.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
	ConnectWindow c;
	c.show();

    return a.exec();
}
