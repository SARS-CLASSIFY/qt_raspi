/********************************************************************************
** Form generated from reading UI file 'camera.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_H
#define UI_CAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_camera
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QLabel *word;
    QLabel *label;
    QLabel *bar;

    void setupUi(QWidget *camera)
    {
        if (camera->objectName().isEmpty())
            camera->setObjectName(QStringLiteral("camera"));
        camera->resize(603, 427);
        gridLayout = new QGridLayout(camera);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_2 = new QGroupBox(camera);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox = new QGroupBox(groupBox_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(820, 300, 71, 191));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        pushButton_2->setFont(font);
        pushButton_2->setCheckable(true);
        pushButton_2->setAutoRepeat(true);
        pushButton_2->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setFont(font);
        pushButton_3->setCheckable(true);
        pushButton_3->setAutoRepeat(true);
        pushButton_3->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_3);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font);
        pushButton->setCheckable(true);
        pushButton->setAutoRepeat(true);
        pushButton->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton);

        word = new QLabel(groupBox_2);
        word->setObjectName(QStringLiteral("word"));
        word->setGeometry(QRect(120, 10, 331, 71));
        word->setFrameShadow(QFrame::Raised);
        word->setAlignment(Qt::AlignCenter);
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(160, 160, 241, 201));
        bar = new QLabel(groupBox_2);
        bar->setObjectName(QStringLiteral("bar"));
        bar->setGeometry(QRect(0, 100, 594, 15));

        gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);


        retranslateUi(camera);

        QMetaObject::connectSlotsByName(camera);
    } // setupUi

    void retranslateUi(QWidget *camera)
    {
        camera->setWindowTitle(QApplication::translate("camera", "Form", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        groupBox->setTitle(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton->setText(QString());
        word->setText(QApplication::translate("camera", "CAMERA", Q_NULLPTR));
        label->setText(QApplication::translate("camera", "http", Q_NULLPTR));
        bar->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class camera: public Ui_camera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_H
