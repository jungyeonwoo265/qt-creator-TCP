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
    veiw_map();
}

void MainWindow::on_radioButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_radioButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

QString MainWindow::make_html()
{   QString positions = R"([
    {
        title: '더리터 송현점',
        latlng: new kakao.maps.LatLng(35.8388522201036, 128.564870126813)
    },
    {
        title: '컴포즈커피 대구죽전아이위시점',
        latlng: new kakao.maps.LatLng(35.8348974104546, 128.5561430456)
    },
    {
        title: '더벤티 대명계대점',
        latlng: new kakao.maps.LatLng(35.855698603935, 128.583204514986)
    },
    {
        title: '더리터 진천역점',
        latlng: new kakao.maps.LatLng(35.8380630509341, 128.604210146328)
    }
])";
    QString center = "35.8388522201036,128.564870126813";
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
var positions = %2;
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


void MainWindow::write_html(QString filename)
{
    QFile file(filename);
    // Trying to open in WriteOnly and Text mode
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << " Could not open file for writing";
        return;
    }
    QTextStream out(&file);
    out << make_html();
    file.flush();
    file.close();
}

void MainWindow::veiw_map(){
    QLayoutItem* item;
    QString filename = "C:/Qt/marker.html";
    write_html(filename);
    QWebEngineView *view = new QWebEngineView();
    view->setUrl(QUrl("http://localhost/Qt/marker.html"));
    while((item = ui->verticalLayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
    ui->verticalLayout->addWidget(view);
}
