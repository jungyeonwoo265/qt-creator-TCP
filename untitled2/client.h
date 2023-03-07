#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <QDataStream>
#include <QByteArray>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QList>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void Read_Data_From_Socket();

    void add_textedit(const int& size, QList<QString>& msg_list);

    void add_tableWidget(const int& size,const int& columm , QList<QString>& msg_list);

private:
    Ui::MainWindow *ui;
    QTcpSocket *TCPSocket;
};
#endif // CLIENT_H
