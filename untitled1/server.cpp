#include "server.h"
#include "ui_server.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TCP_Server = new QTcpServer(this);
    if(TCP_Server->listen(QHostAddress::Any,5001))
    {
        connect(TCP_Server, SIGNAL(newConnection()),this,SLOT(newConnection()));
        QDateTime currentDateTiem = QDateTime::currentDateTime();
        qDebug()<<"Server Open: "+currentDateTiem.toString("yyyy-MM-dd")+" " + currentDateTiem.toString("hh:mm:ss");
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("10.10.21.105");
    db.setDatabaseName("franchise");
    db.setUserName("network");
    db.setPassword("aaaa");
    if(!db.open())
        QMessageBox::information(this,"Error", "데이터베이스 연결 실패");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test_db()
{
    QString object_qstr = QString::fromStdString("달서구");
    QString queryStr;
    queryStr = QString("select cafe_name from cafe where address1 like '%%1%'").arg(object_qstr);
    QSqlQuery query;
    query.prepare(queryStr);
    query.exec();
    while(query.next())
        qDebug()<<query.value(0).toString();
}

void MainWindow::newConnection()
{
    while (TCP_Server->hasPendingConnections())
    {
        Add_New_Client_Connection(TCP_Server->nextPendingConnection());
    }
}

void MainWindow::Add_New_Client_Connection(QTcpSocket *socket)
{
    Client_Connection_List.append(socket);
    connect(socket,SIGNAL(readyRead()),this,SLOT(Read_Data_From_Socket()));
    ui-> comboBox ->addItem(QString::number(socket->socketDescriptor()));
    QString Client = "Client : "+QString::number(socket->socketDescriptor())+" connected with The Server.";
    ui -> textEdit ->append(Client);
}

void MainWindow::Read_Data_From_Socket()
{
    QTcpSocket *socket =reinterpret_cast<QTcpSocket*>(sender());
    QByteArray Message_From_Server = socket -> readAll();
    QString Message = QString::number(socket->socketDescriptor())+"::"+ QString::fromStdString(Message_From_Server.toStdString());
    qDebug()<<sizeof socket->socketDescriptor();
    string str_message = Message_From_Server.toStdString();
    if(str_message == "DB")
    {
        test_db();
    }
    ui -> textEdit -> append(Message);
}

void MainWindow::on_pushButton_clicked()
{
    QString Message_For_Client = ui->lineEdit->text();
    QString Receiver = ui->comboBox->currentText();
    if(ui->comboBox_2->currentText()=="ALL")
    {
        foreach(QTcpSocket *socket, Client_Connection_List)
        {
            socket->write(Message_For_Client.toStdString().c_str());
        }
    }
    else
    {
        foreach(QTcpSocket *socket, Client_Connection_List)
        {
            if(socket->socketDescriptor() == Receiver.toLongLong())
            {
                socket->write(Message_For_Client.toStdString().c_str());
            }
        }
    }
    ui->lineEdit->clear();
}

void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

void MainWindow::on_pushButton_2_clicked()
{
    test_db();
}

