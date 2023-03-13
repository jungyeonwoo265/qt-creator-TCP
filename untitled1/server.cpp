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
    QList<QString> msg_list=Message.split(",");
    qDebug()<<"command: "<<command;
    if(command == 2){
        query = "call proc_if(%1,%2,'%3')";
        query = query.arg(msg_list[0],msg_list[1],msg_list[2]);
    }
    else if(command == 3){
        query = "call proc_wolse(%1,%2,%3,'%4');";
        query = query.arg(msg_list[0],msg_list[1],msg_list[2],msg_list[3]);
    }
    else if(command == 4){
        query = "select * from count_element_estate where ji_addr = '%1'";
        query = query.arg(Message);
    }
    else if(command == 5)
        query=(QString("SELECT cafe_num, apt_num, parking_num, hospital_num, funeral_num, public_num, university_num, subway_num, company_num, bus_num, light_num FROM count_element_estate WHERE ji_addr = '%1'").arg(Message) +" UNION " +"SELECT avg(bus_num), avg(cafe_num), avg(apt_num), avg(light_num), avg(parking_num), avg(hospital_num), avg(funeral_num), avg(public_num), avg(university_num), avg(subway_num), avg(company_num) FROM count_average_estate");

    qDebug()<<"query: "<<query;
    read_db(command, query, *socket);
}

void MainWindow::read_db(int& command,const QString& message, QTcpSocket& socket)
{
    QList<QString> send_message;
    QSqlQuery query;
    if(command==2||command==3){
        query.exec(message);
    }
    else{
        query.prepare(message);
        query.exec();
    }
    query.next();
    QSqlRecord record = query.record();
    int column = record.count();

    if(command==2||command==3){
        query.exec(message);
    }
    else{
        query.prepare(message);
        query.exec();
    }
    while (query.next()) {
        for(int i=0; i<column; i++){
            QString message = query.value(i).toString();
            send_message.append(message);
        }
    }
    if(send_message.isEmpty()){
        qDebug()<<"DB데이터 없음";
        if(command==2||command==3){
            command = 100;
            Send_Data_From_Socket(command, column, message, &socket);
        }
        return;
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
    qDebug()<<send.size()<<"byte";
    socket->write(send);
}
