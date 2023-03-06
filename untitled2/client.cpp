#include "client.h"
#include "ui_client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TCPSocket = new QTcpSocket();
    TCPSocket->connectToHost(QHostAddress::LocalHost,5001);
    TCPSocket->open(QIODevice::ReadWrite);
    connect(TCPSocket,SIGNAL(readyRead()),this,SLOT(Read_Data_From_Socket()));
    if (TCPSocket->isOpen())
        QMessageBox::information(this, "Qt With Ketan", "서버 연결");
    else
        QMessageBox::information(this, "Qt With Ketan", "서버 열결 실패");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Read_Data_From_Socket()
{
    if(TCPSocket)
    {
       if(TCPSocket->isOpen())
        {
            qDebug()<<"메시지 받음";
            QByteArray Data_from_Server = TCPSocket->readAll();
            qDebug()<< Data_from_Server;
            QString MessageString = QString::fromUtf8(Data_from_Server);
            ui->textEdit->append(MessageString);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(TCPSocket)
    {
        if(TCPSocket->isOpen())
        {
            QString qmsg = ui->lineEdit->text();
            TCPSocket->write(qmsg.toStdString().c_str());
            qDebug()<<qmsg;
        }
        else
            QMessageBox::information(this,"Qr With Keten","error: "+TCPSocket->errorString());
    }
    else
        QMessageBox::information(this,"Qr With Keten","error: "+TCPSocket->errorString());
    ui->lineEdit->clear();
}


void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

