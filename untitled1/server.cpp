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
    ui-> textEdit ->append(Client);
}

void MainWindow::Read_Data_From_Socket()
{
    QTcpSocket *socket =reinterpret_cast<QTcpSocket*>(sender());
    QByteArray Message_From_Server = socket -> readAll();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(Message_From_Server, &error);

    QJsonObject obj = doc.object();
    int command = obj.value("command").toInt();
    QString Message = obj.value("message").toString();
    qDebug()<<"command: "<<command<<","<<"Message: "<<Message;
    ui->textEdit->append(Message);
}

void MainWindow::on_pushButton_2_clicked()
{
    QList<QString> send_message;
    QString queryStr;
    QSqlQuery query;

    queryStr = QString("SELECT COUNT(*) FROM information_schema.columns WHERE table_name='daegu_element';");
    query.prepare(queryStr);
    query.exec();
    query.next();
    int columm = query.value(0).toInt();

    queryStr = QString("SELECT * FROM daegu_element where category = '관공서'");
    query.prepare(queryStr);
    query.exec();
    while (query.next()) {
        for(int i=0; i< columm; i++){
            QString message = query.value(i).toString();
            qDebug()<<message;
            send_message.append(message);
        }
    }
    QString msg = send_message.join(",");
    int command = 1;
    Send_Data_From_Socket(command, columm, msg);
}

void MainWindow::Send_Data_From_Socket(const int& command,const int& columm, const QString& msg)
{
    if (ui->comboBox_2->currentText() == "ALL")
    {
        foreach (QTcpSocket *socket, Client_Connection_List)
        {
            QJsonObject json;
            json.insert("command", command);
            json.insert("columm", columm);
            json.insert("message", msg);
            QJsonDocument doc(json);
            QByteArray send = doc.toJson();
            qDebug()<<send.size()<<"byte";
            socket->write(send);
        }
    }
    else
    {
        qDebug() << "test all";
    }
}
