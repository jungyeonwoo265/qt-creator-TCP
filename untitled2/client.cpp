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
            QByteArray Data_from_Server = TCPSocket->readAll();
            qDebug()<<Data_from_Server.size()<<"byte";
            QJsonParseError error;
            QJsonDocument doc = QJsonDocument::fromJson(Data_from_Server, &error);

            QJsonObject obj = doc.object();
            int command = obj.value("command").toInt();
            int columm = obj.value("columm").toInt();
            QString Message = obj.value("message").toString();
            QList<QString> msg_list = Message.split(",");
            qDebug()<<command;
            int size = msg_list.size();
            add_textedit(size, msg_list);
            add_tableWidget(size,columm,msg_list);
        }
    }
}

void MainWindow::add_tableWidget(const int& size,const int& columm , QList<QString>& msg_list){
    ui->tableWidget->setColumnCount(columm);
    ui->tableWidget->setRowCount(int(msg_list.size()/columm));
}

void MainWindow::add_textedit(const int& size, QList<QString>& msg_list)
{
    for(int i=0; i< size;i++)
        ui->textEdit->append(msg_list[i]);
}

void MainWindow::on_pushButton_clicked()
{
    if(TCPSocket)
    {
        if(TCPSocket->isOpen())
        {
            QJsonObject json;
            QString Message = ui->lineEdit->text();
            int command = 1;
            json.insert("command", command);
            json.insert("message", Message);
            QJsonDocument doc(json);
            QByteArray send = doc.toJson();
            TCPSocket->write(send);
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

