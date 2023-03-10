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
    QString Client = "Client : "+QString::number(socket->socketDescriptor())+" connected with The Server.";
    ui-> textEdit ->append(Client);
    QString query = "SELECT dong_name FROM daegu_dong";
    int command = 1;
    read_db(command, query, *socket);
}

void MainWindow::Read_Data_From_Socket()
{
    QString query;
    QTcpSocket *socket =reinterpret_cast<QTcpSocket*>(sender());
    QByteArray Message_From_Server = socket -> readAll();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(Message_From_Server, &error);

    QJsonObject obj = doc.object();
    int command = obj.value("command").toInt();
    QString Message = obj.value("message").toString();
    ui->textEdit->append(QString::number(socket->socketDescriptor())+":"+QString::number(command)+":"+Message);
    if(command == 2)
        query = "select * from daegu_real_estate where type = '매매'";
    else if(command == 3)
        query = "select * from daegu_real_estate where type = '월세'";
    read_db(command, query, *socket);
}

void MainWindow::read_db(const int& command,const QString& message, QTcpSocket& socket)
{
    QList<QString> send_message;
    QString queryStr;
    QSqlQuery query;

    queryStr = message;
    query.prepare(queryStr);
    query.exec();
    query.next();
    QSqlRecord record = query.record();
    int column = record.count();

    query.prepare(message);
    query.exec();
    while (query.next()) {
        for(int i=0; i<column; i++){
            QString message = query.value(i).toString();
            send_message.append(message);
        }
    }
    QString msg = send_message.join(",");
    Send_Data_From_Socket(command, column, msg, &socket);
}

void MainWindow::Send_Data_From_Socket(const int& command,const int& column, const QString& msg, QTcpSocket* socket)
{
    QJsonObject json;
    json.insert("command", command);
    json.insert("column", column);
    json.insert("message", msg);
    QJsonDocument doc(json);
    QByteArray send = doc.toJson();
    qDebug()<<"내용"<<send.size()<<"byte";
    qDebug()<<send.size()<<"byte";
    socket->write(send);
}
