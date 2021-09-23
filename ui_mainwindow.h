/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QLabel *c_time;
    QGroupBox *groupBox_3;
    QLabel *main_theam;
    QGroupBox *groupBox_2;
    QLabel *whether;
    QLabel *fengli;
    QLabel *type;
    QLabel *temperature;
    QWidget *page1;
    QLabel *labelGif;
    QLabel *labelGif2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 600);
        MainWindow->setMouseTracking(false);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        c_time = new QLabel(groupBox);
        c_time->setObjectName(QStringLiteral("c_time"));
        c_time->setGeometry(QRect(20, 20, 121, 181));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        c_time->setFont(font);
        c_time->setWordWrap(true);
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(150, 10, 811, 511));
        main_theam = new QLabel(groupBox_3);
        main_theam->setObjectName(QStringLiteral("main_theam"));
        main_theam->setGeometry(QRect(20, 0, 421, 111));
        main_theam->setAlignment(Qt::AlignCenter);
        groupBox_2 = new QGroupBox(groupBox_3);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(490, 10, 261, 151));
        whether = new QLabel(groupBox_2);
        whether->setObjectName(QStringLiteral("whether"));
        whether->setGeometry(QRect(160, 30, 71, 61));
        whether->setPixmap(QPixmap(QString::fromUtf8("icon/cloud.png")));
        whether->setScaledContents(true);
        whether->setWordWrap(true);
        whether->setOpenExternalLinks(true);
        fengli = new QLabel(groupBox_2);
        fengli->setObjectName(QStringLiteral("fengli"));
        fengli->setGeometry(QRect(20, 20, 131, 22));
        fengli->setFont(font);
        type = new QLabel(groupBox_2);
        type->setObjectName(QStringLiteral("type"));
        type->setGeometry(QRect(20, 100, 131, 22));
        type->setFont(font);
        temperature = new QLabel(groupBox_2);
        temperature->setObjectName(QStringLiteral("temperature"));
        temperature->setGeometry(QRect(20, 60, 111, 22));
        temperature->setFont(font);
        page1 = new QWidget(groupBox_3);
        page1->setObjectName(QStringLiteral("page1"));
        page1->setGeometry(QRect(70, 200, 691, 271));
        labelGif = new QLabel(page1);
        labelGif->setObjectName(QStringLiteral("labelGif"));
        labelGif->setGeometry(QRect(30, 10, 300, 251));
        labelGif->setPixmap(QPixmap(QString::fromUtf8("gif1.gif")));
        labelGif->setScaledContents(true);
        labelGif->setWordWrap(true);
        labelGif2 = new QLabel(page1);
        labelGif2->setObjectName(QStringLiteral("labelGif2"));
        labelGif2->setGeometry(QRect(420, 40, 200, 200));
        labelGif2->setAutoFillBackground(true);
        labelGif2->setScaledContents(true);
        labelGif2->setWordWrap(true);

        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBox->setTitle(QString());
        c_time->setText(QApplication::translate("MainWindow", "8:22", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        main_theam->setText(QApplication::translate("MainWindow", "\346\231\272\350\203\275\351\225\234\351\235\242\345\212\251\346\211\213", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        whether->setText(QString());
        fengli->setText(QApplication::translate("MainWindow", "fengli", Q_NULLPTR));
        type->setText(QApplication::translate("MainWindow", "type", Q_NULLPTR));
        temperature->setText(QApplication::translate("MainWindow", "temp", Q_NULLPTR));
        labelGif->setText(QString());
        labelGif2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
