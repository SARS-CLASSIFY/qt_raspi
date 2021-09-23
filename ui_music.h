/********************************************************************************
** Form generated from reading UI file 'music.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSIC_H
#define UI_MUSIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_music
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QLabel *bar1;
    QLabel *word2;
    QLabel *icon;
    QLabel *picture;
    QLabel *icon2;
    QLabel *gif;

    void setupUi(QWidget *music)
    {
        if (music->objectName().isEmpty())
            music->setObjectName(QStringLiteral("music"));
        music->resize(603, 427);
        gridLayout = new QGridLayout(music);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(music);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        bar1 = new QLabel(groupBox);
        bar1->setObjectName(QStringLiteral("bar1"));
        bar1->setGeometry(QRect(3, 94, 581, 15));
        word2 = new QLabel(groupBox);
        word2->setObjectName(QStringLiteral("word2"));
        word2->setGeometry(QRect(200, 10, 171, 51));
        word2->setAlignment(Qt::AlignCenter);
        icon = new QLabel(groupBox);
        icon->setObjectName(QStringLiteral("icon"));
        icon->setGeometry(QRect(420, 130, 61, 61));
        icon->setAutoFillBackground(false);
        icon->setPixmap(QPixmap(QString::fromUtf8(":/resourses/music/m1.svg")));
        icon->setScaledContents(true);
        icon->setWordWrap(true);
        icon->setOpenExternalLinks(true);
        picture = new QLabel(groupBox);
        picture->setObjectName(QStringLiteral("picture"));
        picture->setGeometry(QRect(90, 130, 261, 201));
        icon2 = new QLabel(groupBox);
        icon2->setObjectName(QStringLiteral("icon2"));
        icon2->setGeometry(QRect(420, 130, 61, 61));
        icon2->setPixmap(QPixmap(QString::fromUtf8(":/resourses/music/m2.svg")));
        icon2->setScaledContents(true);
        icon2->setWordWrap(true);
        icon2->setOpenExternalLinks(true);
        gif = new QLabel(groupBox);
        gif->setObjectName(QStringLiteral("gif"));
        gif->setGeometry(QRect(400, 230, 111, 101));

        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(music);

        QMetaObject::connectSlotsByName(music);
    } // setupUi

    void retranslateUi(QWidget *music)
    {
        music->setWindowTitle(QApplication::translate("music", "Form", Q_NULLPTR));
        groupBox->setTitle(QString());
        bar1->setText(QString());
        word2->setText(QApplication::translate("music", "music", Q_NULLPTR));
        icon->setText(QString());
        picture->setText(QString());
        icon2->setText(QString());
        gif->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class music: public Ui_music {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSIC_H
