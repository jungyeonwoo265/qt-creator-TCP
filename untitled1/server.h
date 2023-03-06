#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <iostream>
#include <QList>
#include <QByteArray>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <Qthread>

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
    void newConnection();

    void Read_Data_From_Socket();

    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void test_db();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    void Add_New_Client_Connection(QTcpSocket *socket);

    QTcpServer *TCP_Server;

    QList<QTcpSocket*> Client_Connection_List;
};
#endif // SERVER_H
