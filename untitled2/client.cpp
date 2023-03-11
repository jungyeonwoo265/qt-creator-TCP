#include "client.h"
#include "ui_client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->radioButton->click();
    ui->stackedWidget_2->setCurrentIndex(1);

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
    QLayoutItem* item;
    while((item = ui->verticalLayout->takeAt(0)) != nullptr)
    {
        qDebug()<<"delete widget: "<<item->widget();
        delete item->widget();
        delete item;
    }
    delete ui;
}

void MainWindow::Read_Data_From_Socket()
{
    if(TCPSocket&&TCPSocket->isOpen())
    {
        QByteArray Data;
        Data = TCPSocket->readAll();
        Data_from_Server.append(Data);
        qDebug()<<Data_from_Server.size()<<"byte";
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
        else if(command == 4){
            ui->tableWidget_2->setRowCount(0);
            ui->tableWidget_2->setRowCount(msg_list.size()-1);
            QStringList column_name = {"카페", "아파트", "주차장", "병원", "장례식장", "공공기관", "대학교", "지하철", "회사", "버스정류장", "신호등", "주소"};
            for(int i = 0; i<msg_list.size()-1;i++){
                ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(column_name[i]));
                ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(msg_list[i]));
            }
            ui->label_21->setText(ui->tableWidget->item(tablewidget_row,2)->text());
            ui->label_22->setText(ui->tableWidget->item(tablewidget_row,1)->text());
            ui->label_24->setText(ui->tableWidget->item(tablewidget_row,3)->text());
            if(ui->tableWidget->item(tablewidget_row,2)->text() == "매매"){
                ui->label_23->setText(ui->tableWidget->item(tablewidget_row,4)->text());
                ui->label_25->setText("");
                ui->label_26->setText("");
            }
            else{
                ui->label_23->setText("");
                ui->label_25->setText(ui->tableWidget->item(tablewidget_row,4)->text());
                ui->label_26->setText(ui->tableWidget->item(tablewidget_row,5)->text());
            }
            show_graph(tablewidget_row,ui->tableWidget->item(tablewidget_row,1)->text());
        }
        else if(command == 5)
        {
            qDebug()<<msg_list;
            QBarSeries *series1 = new QBarSeries();
            QBarSet *set1 = new QBarSet("개수");
            *set1 << msg_list[9].toInt() << msg_list[0].toInt()<< msg_list[1].toInt()<< msg_list[19].toInt()<< msg_list[2].toInt()<< msg_list[3].toInt()<< msg_list[4].toInt()<< msg_list[5].toInt()<< msg_list[6].toInt()<< msg_list[7].toInt()<< msg_list[8].toInt();
            series1->append(set1);

            QBarSeries *series2 = new QBarSeries();
            QBarSet *set2 = new QBarSet("평균 개수");
            for(int i=11; i<msg_list.size(); i++)
            {
                qreal value = msg_list[i].toDouble();
                *set2 << value;
            }
            series2->append(set2);

            // 차트 객체 생성
            QChart *chart = new QChart();
            chart->addSeries(series1);
            chart->addSeries(series2);
            chart->setTitle("대구광역시 매물지역 주변 요소수");
            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            chart->addAxis(axisX, Qt::AlignBottom);
            QStringList categories;
            categories << "버스" << "카페" << "아파트" << "신호등" << "주차장"<< "병원"<< "장례식장"<< "공공기관"<< "대학교"<< "지하철"<< "회사";
            axisX->append(categories);

            // 축을 차트에 추가
            axisX->setLabelsAngle(-90);
            chart->addAxis(axisX, Qt::AlignLeft);

            // 시리즈와 축 연결
            series1->attachAxis(axisX);
            series2->attachAxis(axisX);

            // Y축 설정
            QValueAxis *axisY = new QValueAxis();
            axisY->setTitleText("개수");
            chart->addAxis(axisY, Qt::AlignLeft);
            series1->attachAxis(axisY);
            series2->attachAxis(axisY);

            // 차트 뷰 생성
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            ui->verticalLayout->addWidget(chartView);

            // 차트 뷰 보이기
            chartView->show();

            ui->stackedWidget_2->setCurrentIndex(0);
        }

        if(command){
            Data_from_Server.clear();
        }
    }
}

void MainWindow::add_tableWidget(const int& column , QList<QString>& msg_list){
    QStringList column_name;
    if(column == 8)
        column_name = {"랭킹", "지번", "유형", "평수", "매매가", "점수"};
    else
        column_name = {"랭킹", "지번", "유형", "평수", "보증금", "월세", "점수"};
    int row = msg_list.size()/column;
    ui->tableWidget->setColumnCount(column-2);
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->setHorizontalHeaderLabels(column_name);
    for(int i=0; i<row; i++)
        for(int j=0; j<column-2;j++)
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(msg_list[column*i+j]));
    for(int i=0; i<column-2;i++)
        ui->tableWidget->resizeColumnToContents(i);
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
    QLayoutItem* item;
    while((item = ui->verticalLayout->takeAt(0)) != nullptr)
    {
        qDebug()<<"delete widget: "<<item->widget();
        delete item->widget();
        delete item;
    }
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    int command;
    QString message;

    int com1 = ui->comboBox_1->currentIndex();
    if(ui->radioButton->isChecked())
    {
        int com5 = ui->comboBox_5->currentIndex();
        QString com6 = ui->comboBox_6->currentText();
        command = 2;
        message = QString::number(com1)+","+QString::number(com5)+","+com6;
    }
    else
    {
        int com2 = ui->comboBox_2->currentIndex();
        int com3 = ui->comboBox_3->currentIndex();
        QString com4 = ui->comboBox_4->currentText();
        command = 3;
        message = QString::number(com1)+","+QString::number(com2)+","+QString::number(com3)+","+com4;
    }
    send_message(command, message);
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_radioButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_radioButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
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
    QString filename = "C:/Qt/marker.html";
    write_html(filename, html);
    QWebEngineView *view = new QWebEngineView();
    view->setUrl(QUrl("http://localhost/Qt/marker.html"));
    ui->verticalLayout->addWidget(view);
    qDebug()<<"view: "<<view;
}


void MainWindow::on_tableWidget_cellDoubleClicked(int row)
{
    tablewidget_row = row;
    QString message = ui->tableWidget->item(row,1)->text();
    int command = 4;
    send_message(command, message);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::show_graph(int row, QString addr){
    QLayoutItem* item;
    while((item = ui->verticalLayout->takeAt(0)) != nullptr)
    {
        qDebug()<<"delete widget: "<<item->widget();
        delete item->widget();
        delete item;
    }
    int command = 5;
    send_message(command, addr);
}
