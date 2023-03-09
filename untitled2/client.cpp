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
        QByteArray Data;
        Data = TCPSocket->readAll();
        if(data_size==0)
        {
            data_size = Data.left(20).toInt();
            qDebug()<<"1: "<<data_size;
            qDebug()<<"2: "<<Data.size();
            qDebug()<<"3: "<<Data.mid(20).size();
            Data_from_Server.append(Data.mid(20));
        }
        else{
            Data_from_Server.append(Data);
        }
        Data.clear();
        qDebug()<<"4: "<<Data_from_Server.size()<<"byte";
        QJsonDocument doc = QJsonDocument::fromJson(Data_from_Server);

        QJsonObject obj = doc.object();
        int command = obj.value("command").toInt();
        int column = obj.value("column").toInt();
        QString Message = obj.value("message").toString();
        QList<QString> msg_list = Message.split(",");
        if (command == 1)
        {
            for(int i=0; i<msg_list.size(); i++)
            {
                ui->comboBox_4->addItem(msg_list[i]);
                ui->comboBox_6->addItem(msg_list[i]);
            }
        }
        else if(command == 2 || command == 3)
        {
            add_tableWidget(column,msg_list);
            QString center = "%1,%2";
            center = center.arg(msg_list[column-2],msg_list[column-1]);
            QJsonObject json;
            QList<QString> po_list;
            QString latlng = "new kakao.maps.LatLng(%1, %2)";
            QString title = "'%1'";
            for(int i=0; i<msg_list.size()/column; i++)
            {
                json.insert("title",title.arg(msg_list[i*column+1]));
                json.insert("latlng", latlng.arg(msg_list[i*column+column-2],msg_list[i*column+column-1]));
                QJsonDocument jsonDoc(json);
                QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
                po_list.append(jsonString);
            }
            QString positions = po_list.join(",");
            positions = positions.remove("\"");

            QString html = make_html(center, positions);
            veiw_map(html);
        }
        if(command){
            Data_from_Server.clear();
            data_size=0;
        }
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
        command = 2;
        message = "매매";
    }
    else
    {
        command = 3;
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

QString MainWindow::make_html(const QString &center, const QString &positions)
{
    QString html =
        R"(<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>여러개 마커 표시하기</title>

</head>
<body>
<div id="map" style="width:100%;height:350px;"></div>

<script type="text/javascript" src="//dapi.kakao.com/v2/maps/sdk.js?appkey=4f3a518b54cab788d598a9971a7d6c09"></script>
<script>
var mapContainer = document.getElementById('map'), // 지도를 표시할 div
    mapOption = {
        center: new kakao.maps.LatLng(%1), // 지도의 중심좌표
        level: 8 // 지도의 확대 레벨
    };

var map = new kakao.maps.Map(mapContainer, mapOption); // 지도를 생성합니다

// 마커를 표시할 위치와 title 객체 배열입니다
var positions = [%2];
// 마커 이미지의 이미지 주소입니다
var imageSrc = "https://t1.daumcdn.net/localimg/localimages/07/mapapidoc/markerStar.png";

for (var i = 0; i < positions.length; i ++) {

    // 마커 이미지의 이미지 크기 입니다
    var imageSize = new kakao.maps.Size(24, 35);

    // 마커 이미지를 생성합니다
    var markerImage = new kakao.maps.MarkerImage(imageSrc, imageSize);

    // 마커를 생성합니다
    var marker = new kakao.maps.Marker({
        map: map, // 마커를 표시할 지도
        position: positions[i].latlng, // 마커를 표시할 위치
        title : positions[i].title, // 마커의 타이틀, 마커에 마우스를 올리면 타이틀이 표시됩니다
        image : markerImage // 마커 이미지
    });
}
</script>
</body>
</html>)";
    return html.arg(center, positions);
}


void MainWindow::write_html(const QString &filename, const QString &html)
{
    QFile file(filename);
    // Trying to open in WriteOnly and Text mode
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << " Could not open file for writing";
        return;
    }
    QTextStream out(&file);
    out << html;
    file.flush();
    file.close();
}

void MainWindow::veiw_map(const QString &html){
    QLayoutItem* item;
    QString filename = "C:/Qt/marker.html";
    write_html(filename, html);
    QWebEngineView *view = new QWebEngineView();
    view->setUrl(QUrl("http://localhost/Qt/marker.html"));
    while((item = ui->verticalLayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
    ui->verticalLayout->addWidget(view);
}
