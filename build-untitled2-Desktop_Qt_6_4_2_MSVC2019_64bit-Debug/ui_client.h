/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *pushButton;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *comboBox_4;
    QLabel *label_8;
    QWidget *page_2;
    QComboBox *comboBox_5;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QComboBox *comboBox_6;
    QComboBox *comboBox_1;
    QStackedWidget *stackedWidget_2;
    QWidget *page_6;
    QWidget *page_5;
    QTableWidget *tableWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(768, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 20, 241, 51));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(20, 110, 61, 21));
        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(90, 110, 71, 21));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(670, 110, 75, 24));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(150, 80, 501, 61));
        page = new QWidget();
        page->setObjectName("page");
        comboBox_2 = new QComboBox(page);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(140, 30, 111, 21));
        comboBox_3 = new QComboBox(page);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(275, 30, 111, 21));
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 10, 48, 16));
        label_3 = new QLabel(page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(275, 10, 48, 16));
        label_4 = new QLabel(page);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 48, 16));
        comboBox_4 = new QComboBox(page);
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName("comboBox_4");
        comboBox_4->setGeometry(QRect(410, 30, 81, 21));
        label_8 = new QLabel(page);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(410, 10, 48, 16));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        comboBox_5 = new QComboBox(page_2);
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->setObjectName("comboBox_5");
        comboBox_5->setGeometry(QRect(150, 30, 131, 21));
        label_9 = new QLabel(page_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(310, 10, 48, 16));
        label_10 = new QLabel(page_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 10, 48, 16));
        label_11 = new QLabel(page_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(150, 10, 48, 16));
        comboBox_6 = new QComboBox(page_2);
        comboBox_6->addItem(QString());
        comboBox_6->setObjectName("comboBox_6");
        comboBox_6->setGeometry(QRect(310, 30, 81, 21));
        stackedWidget->addWidget(page_2);
        comboBox_1 = new QComboBox(centralwidget);
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->setObjectName("comboBox_1");
        comboBox_1->setGeometry(QRect(160, 110, 111, 21));
        stackedWidget_2 = new QStackedWidget(centralwidget);
        stackedWidget_2->setObjectName("stackedWidget_2");
        stackedWidget_2->setGeometry(QRect(10, 170, 741, 331));
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        stackedWidget_2->addWidget(page_6);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        tableWidget = new QTableWidget(page_5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(430, 10, 291, 311));
        verticalLayoutWidget = new QWidget(page_5);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 411, 311));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget_2->addWidget(page_5);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 768, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        stackedWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\353\214\200\352\265\254\353\247\244\353\254\274\354\260\276\352\270\260", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "\353\247\244\353\247\244", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "\354\233\224\354\204\270", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\353\247\244\353\254\274\354\241\260\355\232\214", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "\354\240\204\354\262\264", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "5000\354\262\234\353\247\214 \354\235\264\355\225\230", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "5000\354\262\234\353\247\214~1\354\226\265", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "1\354\226\265~2\354\226\265", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("MainWindow", "2\354\226\265~", nullptr));

        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "\354\240\204\354\262\264", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "50\353\247\214\354\233\220 \353\257\270\353\247\214", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "50~100\353\247\214\354\233\220", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("MainWindow", "100~200\353\247\214\354\233\220", nullptr));
        comboBox_3->setItemText(4, QCoreApplication::translate("MainWindow", "200\353\247\214\354\233\220~", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "\353\263\264\354\246\235\352\270\210", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\354\233\224\354\204\270", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\355\217\211\355\230\225\353\214\200", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("MainWindow", "\354\240\204\354\247\200\354\227\255", nullptr));

        label_8->setText(QCoreApplication::translate("MainWindow", "\353\217\231\354\204\240\355\203\235", nullptr));
        comboBox_5->setItemText(0, QCoreApplication::translate("MainWindow", "\354\240\204\354\262\264", nullptr));
        comboBox_5->setItemText(1, QCoreApplication::translate("MainWindow", "1\354\226\265\354\235\264\355\225\230", nullptr));
        comboBox_5->setItemText(2, QCoreApplication::translate("MainWindow", "1\354\226\265 ~ 5\354\226\265", nullptr));
        comboBox_5->setItemText(3, QCoreApplication::translate("MainWindow", "5\354\226\265 \354\235\264\354\203\201", nullptr));
        comboBox_5->setItemText(4, QString());

        label_9->setText(QCoreApplication::translate("MainWindow", "\353\217\231\354\204\240\355\203\235", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\355\217\211\355\230\225\353\214\200", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\353\247\244\353\247\244\352\260\200", nullptr));
        comboBox_6->setItemText(0, QCoreApplication::translate("MainWindow", "\354\240\204\354\247\200\354\227\255", nullptr));

        comboBox_1->setItemText(0, QCoreApplication::translate("MainWindow", "\354\240\204\354\262\264", nullptr));
        comboBox_1->setItemText(1, QCoreApplication::translate("MainWindow", "10\355\217\211\353\257\270\353\247\214", nullptr));
        comboBox_1->setItemText(2, QCoreApplication::translate("MainWindow", "10~20\355\217\211", nullptr));
        comboBox_1->setItemText(3, QCoreApplication::translate("MainWindow", "21\355\217\211~", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
