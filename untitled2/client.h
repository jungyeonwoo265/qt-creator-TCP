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
#include <QApplication>
#include <QWebEngineView>
#include <fstream>
#include <QFile>

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

    void Read_Data_From_Socket();

    void add_tableWidget(const int& columm , QList<QString>& msg_list);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void send_message(int& command, QString& message);

    QString make_html();

    void write_html(QString filename);

    void veiw_map();

private:
    Ui::MainWindow *ui;
    QTcpSocket *TCPSocket;
};
#endif // CLIENT_H
