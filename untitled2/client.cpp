#include "client.h"
#include "ui_client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->radioButton->click();

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
    if(TCPSocket&&TCPSocket->isOpen())
    {
        QByteArray Data_from_Server = TCPSocket->readAll();
        qDebug()<<Data_from_Server.size()<<"byte";
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(Data_from_Server, &error);

        QJsonObject obj = doc.object();
        int command = obj.value("command").toInt();
        int column = obj.value("column").toInt();
        QString Message = obj.value("message").toString();
        QList<QString> msg_list = Message.split(",");
        qDebug()<<command;
        if (command == 0){
            for(int i=0; i<msg_list.size(); i++){
                ui->comboBox_4->addItem(msg_list[i]);
                ui->comboBox_6->addItem(msg_list[i]);
            }
        }
        else if(command == 1 || command ==2)
            add_tableWidget(column,msg_list);
    }
}

void MainWindow::add_tableWidget(const int& column , QList<QString>& msg_list){
    int row = msg_list.size()/column;
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(column);
    ui->tableWidget->setRowCount(row);
    for(int i=0; i<row; i++)
        for(int j=0; j<column;j++)
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(msg_list[column*i+j]));
    }

void MainWindow::send_message(int& command, QString& message){
    if (TCPSocket && TCPSocket->isOpen())
    {
        QJsonObject json;
        json.insert("command", command);
        json.insert("message", message);
        QJsonDocument doc(json);
        QByteArray send = doc.toJson();
        TCPSocket->write(send);
    }
    else
        QMessageBox::information(this,"ERROR",TCPSocket->errorString());
}

void MainWindow::on_pushButton_clicked()
{
    int command;
    QString message;
    if(ui->radioButton->isChecked())
    {
        command = 1;
        message = "매매";
    }
    else
    {
        command = 2;
        message = "월세";
    }
    send_message(command, message);
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_radioButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_radioButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

