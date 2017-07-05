#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

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

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QString totalText;

    void connectToServer();
};

#endif // MAINWINDOW_H
